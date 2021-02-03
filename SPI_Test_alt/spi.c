#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "spi.h"

void init_spi()
{
    // SSI INITIALISERES
    SYSCTL_RCGCSSI_R |= SYSCTL_RCGCSSI_R0; // AKTIVER SSI MODUL 0
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; // AKTIVER CLOCK P� PORT A

    GPIO_PORTA_AFSEL_R |= 0x3C; // AKTIVER ALTERNATIV FUNKTION P� PA2-PA5
    GPIO_PORTA_PCTL_R |= 0x222200; // SSI V�LGES SOM ALTERNATIV FUNKTION P� PA2-PA5

    GPIO_PORTA_PUR_R |= 0x3C; // PULL-UP-RESISTOR AKTIVERES FOR ALLE SSI-PINS
    GPIO_PORTA_DEN_R |= 0x3C; // AKTIVER DIGITAL FUNKTION P� PA2-PA5

    // SPI KONFIGURERES
    SSI0_CR1_R &= 0x00; // REGISTER NULSTILLES (OG INDSTILLES TIL MASTER)
    SSI0_CR1_R |= 0x10; // EOT-BIT S�TTES
    SSI0_CC_R &= 0x00; // CLOCK = SYSTEM CLOCK

    // DER �NSKES SSI0Clk = SysClk / (CPSDVSR * (1+SCR)) = 421 kHz (Fs = 25 kHz � 16 bit p� ADC og 1315 Hz � 16 bit p� DAC)
    // SysClk = 16 MHz   -->   CPSDVSR = 2, SCR = 18
    SSI0_CPSR_R |= 0x02; // CPSDVSR = 2
    SSI0_CR0_R |= 0x124F; // SCR = 18, SPH = 0 (DATA TAGES VED F�RSTE CLOCK EDGE), SPO = 1 (STEADY STATE P� CLOCK ER HIGH), FREESCALE SPI, 16-BIT DATA
    // ERSTAT 4 MED 8 ^ IDET SPH SKAL V�RE H�J OG SPO LAV
    SSI0_CR1_R |= 0x02; // SSI SL�S TIL

    // INITIALISERING AF PORT A TIL SLAVE SELECT
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;
    GPIO_PORTA_DIR_R |= 0xC0;
    GPIO_PORTA_DEN_R |= 0xC0;

    while(SSI0_SR_R & 0x10); // VENT P� AT MODUL ER KLAR

    // KLARG�R DAC OG ADC'ER TIL BRUG
    send_data(0, SSI_SLAVE_DAC);
    send_data(0, SSI_SLAVE_ADCV);

    GPIO_PORTA_DATA_R |= 0x40;
    clear_buffer();

    for (INT8U n=0; n<7; n++)
    {
        SSI0_DR_R = 0x00;
    }

    NVIC_EN0_R |= 0x80; // AKTIVER INTERRUPT P� SSI0
    SSI0_IM_R |= 0x08; // AKTIVER INTERRUPT N�R TRANSMIT-REGISTER ER TOMT
}


/**********************************************************************************************************/
/********************************  ALT OVER DENNE LINJE ER SETUP  *****************************************/
/**********************************************************************************************************/
/**********************************************************************************************************/


// DENNE FUNKTION ER EN INTERRUPT, DER SKER, N�R TRANSMITTERINGEN ER F�RDIG
void transmit_handler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xSemaphoreGiveFromISR(xSempahoreSPIINT,&xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

// UDGAVE MED 25 K-SAMPLES P� ADC OG 1315 SAMPLES P� DAC PR. SEKUND
// DENNE FUNKTION ER TASKEN, DER ANVENDES TIL AT STYRE SPI I FREERTOS
void spi_task(void * pvParameters)
{
    static INT8U Tx_state = 1;
    INT16U SPI_data;
    INT16U *temp_clear;

    while (1)
    {
        xSemaphoreTake(xSemaphoreSPIINT, portMAX_DELAY);
        GPIO_PORTA_DATA_R |= 0x40;

        switch (Tx_state)
        {
        case 0:
        {
            *temp_clear = SSI0_DR_R;
            for (INT8U n = 0; n<7; n++)
            {
                SSI0_DR_R = 0x00;
            }
            Tx_state = 1;
            break;
        }

        case 1:
        {
            for (INT8U n = 0; n<7; n++)
            {
                SPI_data = SSI0_DR_R;
                xQueueSend(xQueueFILTERDATA, void *SPI_data, NULL);
            }
            for (INT8U n = 0; n<7; n++)
            {
                SSI0_DR_R = 0x00;
            }
            Tx_state = 2;
            break;
        }

        case 2:
        {
            for (INT8U n = 0; n<7; n++)
            {
                SPI_data = SSI0_DR_R;
                xQueueSend(xQueueFILTERDATA, void *SPI_data, NULL);
            }
            for (INT8U n = 0; n<5; n++)
            {
                SSI0_DR_R = 0x00;
            }
            Tx_state = 3;
            break;
        }

        case 3:
        {
            GPIO_PORTA_DATA_R &= 0xBF; // DAC V�LGES MED MUX

            for (INT8U n = 0; n<5; n++)
            {
                SPI_data = SSI0_DR_R;
                xQueueSend(xQueueFILTERDATA, void *SPI_data, NULL);
            }

            queue_placeholder = 0x0000; // <---- ERSTAT MED VOC-V�RDI I FREERTOS
            SSI0_DR_R = ((queue_placeholder<<2) & 0x3FFF); // F�RSTE TO BIT (00) S�TTER NORMAL POWER-MODE, 12 N�STE ER DATA, SIDSTE TO ER UBRUGTE

            Tx_state = 0;
            break;
        }

        default:
            break;
        }
    }
}

// DENNE FUNKTION ER KUN TIL TESTFORM�L OG SKAL IKKE ANVENDES I TASKEN
void send_data(INT16U data, INT8U slave)
{
    switch (slave)
    {
    case SSI_SLAVE_DAC:
    {
        // TJEK OM DEN VIRKER MED DEN MAPPEDE FLOATNG-POINT
        write_data((data<<2) & 0x3FFF);

        while (SSI0_SR_R & 0x10); // VENT P� AT MODUL ER F�RDIGT

        break;
    }

    case SSI_SLAVE_ADCV:
    {
        GPIO_PORTA_DATA_R |= 0x40; // SLAVE 1 V�LGES

        for (INT8U i = 0; i < 42; i++)
        {
            // VENT P� AT SS N�R GENNEM ISOLATOR (MAKS. 2,6 MIKROSEKUNDER)
        }

        write_data(data);

        while (SSI0_SR_R & 0x10); // VENT P� AT MODUL ER F�RDIGT

        GPIO_PORTA_DATA_R &= 0xBF;
        break;
    }

    case SSI_SLAVE_ADCI:
    {
        GPIO_PORTA_DATA_R |= 0x80; // SLAVE 2 V�LGES

        for (INT8U i = 0; i < 42; i++)
        {
            // VENT P� AT SS N�R GENNEM ISOLATOR (MAKS. 2,6 MIKROSEKUNDER)
        }

        write_data(data);

        while (SSI0_SR_R & 0x10); // VENT P� AT MODUL ER F�RDIGT

        GPIO_PORTA_DATA_R &= 0x7F;
        break;
    }

    default:
        break;
    }
}

// DENNE FUNKTION ER KUN TIL TESTFORM�L OG SKAL IKKE ANVENDES I TASKEN
void write_data(INT16U data)
{
    SSI0_DR_R = data;
}

// DENNE FUNKTION ER KUN TIL TESTFORM�L OG SKAL IKKE ANVENDES I TASKEN
INT16U get_data()
{
    return SSI0_DR_R;
}

// DENNE FUNKTION ER KUN TIL TESTFORM�L OG SKAL IKKE ANVENDES I TASKEN
void clear_buffer()
{
    while (SSI0_SR_R & 0x04)
    {
        INT16U *temp_clear = 0;
        *temp_clear = get_data();
    }
}
