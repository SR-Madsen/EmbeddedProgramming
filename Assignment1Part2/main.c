/************************************************************************************************
* UNIVERSITY OF SOUTHERN DENMARK
* EMBEDDED PROGRAMMING (EMP)
*
* MODULE NAME: main.c
*
* PROJECT: ASSIGNMENT 1
*
* DESCRIPTION:
*    -IMPLEMENT A BINARY COUNTER (0-7) WITH A CORRESPONDING RGB-COLOR
*    -THE COUNTER MUST BE ABLE TO COUNT UP OR DOWN
*    -THE COUNTER MUST ADVANCE ONE STEP WHENEVER THE SWITCH 1 IS PRESSED
*    -THE DIRECTION OF COUNTING MUST BE TOGGLED WHEN SWITCH 1 IS DOUBLE-CLICKED
*    -A CONTINOUS PRESS OF SWITCH 1 FOR MORE THAN 2 SECONDS MUST SET THE COUNTER IN AUTO-MODE
*    -AUTO-MODE AUTOMATICALLY ADVANCES ONE STEP UP OR DOWN EVERY 200 MS
*
* CHANGE LOG:
*************************************************************************************************
* DATE      ID      CHANGE
* YYMMDD
* ---------------------------------
* 19-02-20  SM      MODULE CREATED
*************************************************************************************************/


/**************************************** INCLUDE FILES ****************************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systick.h"
#include "emp_type.h"

/******************************************* DEFINES *******************************************/

/****************************************** CONSTANTS ******************************************/

/****************************************** VARIABLES ******************************************/

/****************************************** FUNCTIONS ******************************************/

int main(void)
{
    disable_global_int(); // TEMPORARILY DISABLE GLOBAL INTERRUPTS WHILE INITIALIZING SYSTICK
    init_systick(); // INITIALIZE SYSTICK
    enable_global_int(); // RE-ENABLE GLOBAL INTERRUPTS

    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF; // ENABLE GPIO-PORT F
    GPIO_PORTF_DIR_R |= 0X0E; // LED PORTS SET TO OUTPUT
    GPIO_PORTF_DEN_R |= 0X1E; // GPIO-PINS SET TO DIGITAL
    GPIO_PORTF_PUR_R |= 0X10; // INTERNAL PULL-UP ENABLED FOR SWITCH 1

    while(GPIO_PORTF_DATA_R & 0x00)
    {// I DON'T KNOW WHY THIS WORKS, BUT WITHOUT THIS THE SWITCH WILL DEFAULT TO GREEN INSTEAD OF OFF
    }

    while(1)
    {
        if (GPIO_PORTF_DATA_R & 0x10) // IF SW1 NOT PRESSED
        {
            // DO NOTHING
        }
        else
        {
            on_press();
            while ((GPIO_PORTF_DATA_R & 0x10) == 0) // WAIT FOR BUTTON TO BE RELEASED
            {
            }
        }

    }

    return 0;
}
