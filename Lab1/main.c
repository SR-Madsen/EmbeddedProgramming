#include <stdint.h>
#include "tm4c123gh6pm.h"

int main(void)
{
    //Funktion: LED lyser op, n�r man trykker p� SWITCH-knappen

    int dummy;

    //Sl�r GPIO-porten til, der bruges til LED'er og switches p� boardet
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    //Dummy-read for at have et par cykler efter peripheral sl�s til
    dummy = SYSCTL_RCGC2_R;

    //Indstil som output (PF1 - PF3)
    GPIO_PORTF_DIR_R = 0x0E;

    //Indstil GPIO-pins til digital funktion (PF1 - PF4)
    GPIO_PORTF_DEN_R = 0x1E;

    //Sl� intern pull-up til (PF4)
    GPIO_PORTF_PUR_R = 0x10;

    //LOOP
    while(1)
    {
        if (GPIO_PORTF_DATA_R & 0x10)
        {
            GPIO_PORTF_DATA_R &= ~(0x02);
        }
        else
        {
            GPIO_PORTF_DATA_R |= 0x02;
        }
    }

	return 0;
}
