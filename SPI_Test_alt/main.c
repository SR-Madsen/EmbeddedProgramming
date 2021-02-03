#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "spi.h"
#include "systick.h"

int main(void)
{
    static INT8U alive_timer = 100;
    //INT16U ret_data;

    disable_global_int();
    init_systick(); // SYSTICK INITIALISERES
    enable_global_int();
    init_spi(); // SPI INITIALISERES

    // INITIALISERING AF LED'ER OG SWITCH 1 TIL TESTFORMÅL
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
    GPIO_PORTF_DIR_R |= 0x0E;
    GPIO_PORTF_DEN_R |= 0x1E;
    GPIO_PORTF_PUR_R |= 0x10;

    while(1)
    {
        while (!ticks);

        ticks--;

        /*if (GPIO_PORTF_DATA_R & 0x10)
        {
        }

        else
        {
            clear_buffer();

            send_data(0x0000, SSI_SLAVE_ADCV);
            ret_data = get_data();
            send_data(ret_data, SSI_SLAVE_DAC);
            ret_data = get_data();
        }*/

         if (!alive_timer--)
        {
            alive_timer = 100;
            GPIO_PORTF_DATA_R ^= 0x02;
        }
    }

	return 0;
}
