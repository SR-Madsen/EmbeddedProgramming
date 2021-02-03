/*
 * functions.c
 *
 *  Created on: 6. mar. 2019
 *      Author: Sebastian
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "functions.h"

//STATE 0 = LÅST
//STATE 1 = FØRSTE RIGTIG
//STATE 2 = ANDEN RIGTIG
//STATE 3 = TREDJE RIGTIG
//STATE 4 = FJERDE RIGTIG
//STATE 5 = FØRSTE FORKERT
//STATE 6 = ANDEN FORKERT
//STATE 7 = TREDJE FORKERT
//STATE 8 = FJERDE FORKERT
//STATE 9 = LÅST OP

void Check(INT8U Button)
{
    static INT8U State = 0;
    switch (State)
    {
    case 0:
        if (Button == 1)
        {
            State = 1;
        }
        else
        {
            State = 5;
        }
        break;

    case 1:
        if (Button == 2)
        {
            State = 2;
        }
        else
        {
            State = 6;
        }
        break;

    case 2:
        if (Button == 2)
        {
            State = 3;
        }
        else
        {
            State = 7;
        }
        break;

    case 3:
        if (Button == 1)
        {
            State = 4;
        }
        else
        {
            State = 8;
        }
        break;

    case 4:
        if (Button == 2)
        {
            State = 9;
            GPIO_PORTF_DATA_R = 0x08;
        }
        else
        {
            State = 0;
        }
        break;

    case 5:
        if (Button)
        {
            State = 6;
        }
        break;

    case 6:
        if (Button)
        {
            State = 7;
        }
        break;

    case 7:
        if (Button)
        {
            State = 8;
        }
        break;

    case 8:
        if (Button)
        {
            State = 0;
        }
        break;

    case 9:
        if (Button)
        {
            State = 0;
            GPIO_PORTF_DATA_R = 0x02;
        }
    }
}
