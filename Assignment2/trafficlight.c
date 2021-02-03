/************************************************************************************************
* UNIVERSITY OF SOUTHERN DENMARK
* EMBEDDED PROGRAMMING (EMP)
*
* MODULE NAME: trafficlight.c
*
* PROJECT: ASSIGNMENT 2
*
*
* CHANGE LOG:
*************************************************************************************************
* DATE      ID      CHANGE
* YYMMDD
* ---------------------------------
* 19-03-10  SM      MODULE CREATED
*************************************************************************************************/


/**************************************** INCLUDE FILES ****************************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "trafficlight.h"
#include "emp_type.h"

/******************************************* DEFINES *******************************************/

/****************************************** CONSTANTS ******************************************/

/****************************************** VARIABLES ******************************************/

/****************************************** FUNCTIONS ******************************************/

/*****************************************************************************
*   ALL FUNCTIONS: See module specification (.h-file).
*****************************************************************************/

/* STATES:
 * 0 = RED
 * 1 = RED AND YELLOW
 * 2 = GREEN
 * 3 = YELLOW
 * 4 = YELLOW (ON FOR 200 MS)
 * 5 = YELLOW (OFF FOR 800 MS)
 * 6 = RED (PERMANENT)
 */

void light_event_react(INT8U event)
{
    static INT8U light_state = 0;
    static INT16U timer = 0;

    timer++;

    switch (light_state)
    {
    case 0:
    {
        switch (event)
        {
        case 0:
            GPIO_PORTF_DATA_R = 0x0C;
            if (timer>600)
            {
                timer = 0;
                light_state = 1;
            }
            break;

        case 1:
            timer = 0;
            light_state = 4;
            break;

        case 2:
            timer = 0;
            light_state = 6;
            break;

        case 3:
            GPIO_PORTF_DATA_R = 0x0C;
            if (timer>600)
            {
                timer = 0;
                light_state = 1;
            }
            break;

        default:
            break;
        }
        break;
    }

    case 1:
    {
        switch (event)
        {
        case 0:
            GPIO_PORTF_DATA_R = 0x08;
            if (timer>300)
            {
                timer = 0;
                light_state = 2;
            }
            break;

        case 1:
            timer = 0;
            light_state = 4;
            break;

        case 2:
            timer = 0;
            light_state = 6;
            break;

        case 3:
            GPIO_PORTF_DATA_R = 0x08;
            if (timer>300)
            {
                timer = 0;
                light_state = 2;
            }
            break;

        default:
            break;
        }
        break;
    }

    case 2:
    {
        switch (event)
        {
        case 0:
            GPIO_PORTF_DATA_R = 0x06;
            if (timer>800)
            {
                timer = 0;
                light_state = 3;
            }
            break;

        case 1:
            timer = 0;
            light_state = 4;
            break;

        case 2:
            timer = 0;
            light_state = 6;
            break;

        case 3:
            GPIO_PORTF_DATA_R = 0x06;
            if (timer>800)
            {
                timer = 0;
                light_state = 3;
            }
            break;

        default:
            break;
        }
        break;
    }

    case 3:
    {
        switch (event)
        {
        case 0:
            GPIO_PORTF_DATA_R = 0x0A;
            if (timer>300)
            {
                timer = 0;
                light_state = 0;
            }
            break;

        case 1:
            timer = 0;
            light_state = 4;
            break;

        case 2:
            timer = 0;
            light_state = 6;
            break;

        case 3:
            GPIO_PORTF_DATA_R = 0x0A;
            if (timer>300)
            {
                timer = 0;
                light_state = 0;
            }
            break;

        default:
            break;
        }
        break;
    }

    case 4:
    {
        switch (event)
        {
        case 0:
            GPIO_PORTF_DATA_R = 0x0A;
            if (timer>200)
            {
                timer = 0;
                light_state = 5;
            }
            break;

        case 1:
            GPIO_PORTF_DATA_R = 0x0A;
            if (timer>200)
            {
                timer = 0;
                light_state = 5;
            }
            break;

        case 2:
            timer = 0;
            light_state = 6;
            break;

        case 3:
            timer = 0;
            light_state = 0;
            break;

        default:
            break;
        }
        break;
    }

    case 5:
    {
        switch (event)
        {
        case 0:
            GPIO_PORTF_DATA_R = 0x0E;
            if (timer>200)
            {
                timer = 0;
                light_state = 4;
            }
            break;

        case 1:
            GPIO_PORTF_DATA_R = 0x0E;
            if (timer>200)
            {
                timer = 0;
                light_state = 4;
            }
            break;

        case 2:
            timer = 0;
            light_state = 6;
            break;

        case 3:
            timer = 0;
            light_state = 0;
            break;

        default:
            break;
        }
        break;
    }

    case 6:
    {
        switch (event)
        {
        case 0:
            GPIO_PORTF_DATA_R = 0x0C;
            break;

        case 1:
        {
            timer = 0;
            light_state = 4;
            break;
        }

        case 2:
            GPIO_PORTF_DATA_R = 0x0C;

        case 3:
            timer = 0;
            light_state = 0;
            break;

        default:
            break;
        }
        break;
    }

    default:
        break;
    }
}

/****************************** End Of Module *******************************/
