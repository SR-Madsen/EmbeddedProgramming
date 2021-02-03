/************************************************************************************************
* UNIVERSITY OF SOUTHERN DENMARK
* EMBEDDED PROGRAMMING (EMP)
*
* MODULE NAME: gpio.c
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
#include "gpio.h"

/******************************************* DEFINES *******************************************/

/****************************************** CONSTANTS ******************************************/

/****************************************** VARIABLES ******************************************/

/****************************************** FUNCTIONS ******************************************/

/*****************************************************************************
*   ALL FUNCTIONS: See module specification (.h-file).
*****************************************************************************/

void gpio_init()
{
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOD | SYSCTL_RCGC2_GPIOF; // ENABLE GPIO-PORT D AND F

    GPIO_PORTF_DIR_R |= 0x0E; // LED PORTS SET TO OUTPUT
    GPIO_PORTD_DIR_R |= 0x40; // PD6 SET AS OUTPUT

    GPIO_PORTF_DEN_R |= 0x1E; // GPIO-PINS SET TO DIGITAL
    GPIO_PORTD_DEN_R |= 0x40; // GPIO-PIN SET TO DIGITAL

    GPIO_PORTF_PUR_R |= 0x10; // INTERNAL PULL-UP ENABLED FOR SWITCH 1
}

/****************************** End Of Module *******************************/
