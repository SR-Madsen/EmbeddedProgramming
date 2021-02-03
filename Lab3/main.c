#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "functions.h"


int main(void)
{
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF; // ENABLE GPIO-PORT F
    GPIO_PORTF_DIR_R = 0x0E; // LED PORTS SET TO OUTPUT
    GPIO_PORTF_DEN_R = 0x1F; // GPIO-PINS SET TO DIGITAL

    GPIO_PORTF_LOCK_R = 0x4C4F434B; // UNLOCK FOR SWITCH 2
    GPIO_PORTF_CR_R = 0xFF; // ENABLE OVERWRITE FOR SWITCH 2

    GPIO_PORTF_PUR_R = 0x11; // INTERNAL PULL-UP ENABLED FOR SWITCH 1 AND 2

    GPIO_PORTF_DATA_R = 0x02; // ENABLE RED LED

    while (1)
    {
        if (GPIO_PORTF_DATA_R & 0x10)
        {
        }
        else
        {
            Check(1);
        }

        if (GPIO_PORTF_DATA_R & 0x01)
        {
        }
        else
        {
            Check(2);
        }
    }

    return 0;
}
