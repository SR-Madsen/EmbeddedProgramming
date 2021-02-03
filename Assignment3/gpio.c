/************************************************************************************************
* UNIVERSITY OF SOUTHERN DENMARK
* EMBEDDED PROGRAMMING (EMP)
*
* MODULE NAME: gpio.c
*
* PROJECT: ASSIGNMENT 3
*
*
* CHANGE LOG:
*************************************************************************************************
* DATE      ID      CHANGE
* YYMMDD
* ---------------------------------
* 19-03-19  SM      MODULE CREATED
*************************************************************************************************/


/**************************************** INCLUDE FILES ****************************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "gpio.h"
#include "systick.h"
#include "lcd.h"

/******************************************* DEFINES *******************************************/

/****************************************** CONSTANTS ******************************************/

/****************************************** VARIABLES ******************************************/

/****************************************** FUNCTIONS ******************************************/

/*****************************************************************************
*   ALL FUNCTIONS: See module specification (.h-file).
*****************************************************************************/

void gpio_init()
{
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOD | SYSCTL_RCGC2_GPIOF | SYSCTL_RCGC2_GPIOC; // ENABLE GPIO-PORT C, D, AND F

    GPIO_PORTF_DIR_R |= 0x0E; // LED PORTS SET TO OUTPUT
    GPIO_PORTD_DIR_R |= 0x4C; // PD2, PD3, AND PD6 SET AS OUTPUT
    GPIO_PORTC_DIR_R |= 0xF0; // PC4, PC5, PC6, PC7 SET AS OUTPUT

    GPIO_PORTF_DEN_R |= 0x1E; // GPIO-PINS IN F SET TO DIGITAL
    GPIO_PORTD_DEN_R |= 0x4C; // GPIO-PIN IN D SET TO DIGITAL
    GPIO_PORTC_DEN_R |= 0xF0; // GPIO-PINS IN C SET TO DIGITAL

    GPIO_PORTF_PUR_R |= 0x10; // INTERNAL PULL-UP ENABLED FOR SWITCH 1

    // SETUP OF LCD DISPLAY
    delay(10);
    SendCommand(0x30);

    delay(1);
    SendCommand(0x30);

    SendCommand(0x30);

    SendCommand(0x20); // SET 4-BIT MODE

    SendCommand(0x20); // 4-BIT MODE, 1/16 DUTY, 5x8 FONT
    SendCommand(0x80);

    SendCommand(0x00); // DISPLAY OFF
    SendCommand(0x80);

    SendCommand(0x00); // DISPLAY ON, BLINK CURSOR ON
    SendCommand(0xF0);

    SendCommand(0x00); // ENTRY MODE
    SendCommand(0x60);

    SendCommand(0x00); // HOME (CLEAR AND GO TO START)
    SendCommand(0x10);

    // SET DISPLAY = 00:00
    WriteChar('0');
    WriteChar('0');
    WriteChar(':');
    WriteChar('0');
    WriteChar('0');

    // REMOVE CURSOR BLINK
    SendCommand(0x00);
    SendCommand(0xC0);
}

/****************************** END OF MODULE *******************************/
