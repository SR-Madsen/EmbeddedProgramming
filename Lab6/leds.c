#include "leds.h"
#include "rtcs.h"
#include "tmodel.h"

void green_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data)
{
    GPIO_PORTF_DATA_R ^= 0x08;
    wait_sem(LED_ON_SEM,0);
}

void yellow_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data)
{
    if (my_state)
    {
        GPIO_PORTF_DATA_R ^= 0x04;
        set_state(0);
        wait_sem(SW1_SEM,600);
    }
    else
    {
        GPIO_PORTF_DATA_R ^= 0x04;
        signal(LED_ON_SEM);
        set_state(1);
        wait(100);
    }

}

void red_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data)
{
    if (my_state)
    {
        GPIO_PORTF_DATA_R ^= 0x02;
        set_state(0);
        wait(1000);
    }
    else
    {
        GPIO_PORTF_DATA_R ^= 0x02;
        signal(LED_ON_SEM);
        set_state(1);
        wait(1000);
    }
}
