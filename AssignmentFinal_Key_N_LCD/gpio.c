/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: gpio.c
*
* PROJECT....: EMP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150215  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
#include "task.h"
#include "emp_type.h"
#include "gpio.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void init_gpio(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : Initializes GPIO
******************************************************************************/
{

    // Enable all used GPIO ports.
    SYSCTL_RCGC2_R  =  SYSCTL_RCGC2_GPIOA | SYSCTL_RCGC2_GPIOC | SYSCTL_RCGC2_GPIOD | SYSCTL_RCGC2_GPIOE |SYSCTL_RCGC2_GPIOF;

    // Set direction of all outputs.
    GPIO_PORTA_DIR_R = 0x1C;
    GPIO_PORTC_DIR_R = 0xF0;
    GPIO_PORTD_DIR_R = 0x4C;
    GPIO_PORTF_DIR_R = 0x0E;

    // Enable the GPIO pins for digital function
    GPIO_PORTA_DEN_R = 0x1C;
    GPIO_PORTC_DEN_R = 0xF0;
    GPIO_PORTD_DEN_R = 0x4C;
    GPIO_PORTE_DEN_R = 0x0F;
    GPIO_PORTF_DEN_R = 0x1F;

    // Enable internal pull-ups of switches
    GPIO_PORTF_PUR_R = 0x11;
}

/****************************** End Of Module *******************************/
