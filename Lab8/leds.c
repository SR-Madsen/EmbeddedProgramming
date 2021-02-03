#include <stdint.h>
#include "FreeRTOS.h"
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "adc.h"

void redled_task(void * pvParameters) // FLASH WITH BETWEEN 1 AND 10 HZ DEPENDING ON POTMETER (ADC INPUT)
// ADC IS 12-BIT; NUMBER BETWEEN 0 AND 4095
{
    while(1)
    {
        INT16U adc_val = get_adc();
        INT16U xDelay_ms = adc_val/4.095;
        if (xDelay_ms > 1000)
        {
            xDelay_ms = 1000;
        }
        if (xDelay_ms < 100)
        {
            xDelay_ms = 100;
        }
        xDelay_ms = xDelay_ms - (xDelay_ms % 5);

        vTaskDelay(xDelay_ms/portTICK_RATE_MS);
        GPIO_PORTF_DATA_R ^= 0x02;
    }
}

void yellowled_task(void * pvParameters) // FLASH EVERY OTHER SECOND
{
    while(1)
    {
        vTaskDelay(2000/portTICK_RATE_MS);
        GPIO_PORTF_DATA_R ^= 0x04;
    }
}

void greenled_task(void * pvParameters) // FLASH EVERY THIRD SECOND
{
    while(1)
    {
        vTaskDelay(3000/portTICK_RATE_MS);
        GPIO_PORTF_DATA_R ^= 0x08;
    }
}
