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
#include "systick.h"

/******************************************* DEFINES *******************************************/

/****************************************** CONSTANTS ******************************************/

/****************************************** VARIABLES ******************************************/

/****************************************** FUNCTIONS ******************************************/

/*****************************************************************************
*   ALL FUNCTIONS: See module specification (.h-file).
*****************************************************************************/
void SendCommand(INT8U command)
{
    GPIO_PORTD_DATA_R |= 0x08;
    GPIO_PORTC_DATA_R = command;
    GPIO_PORTD_DATA_R &= 0xF7;
    delay(1);
}

void ClearDisplay()
{
    SendCommand(0x00);
    SendCommand(0x01);
}

void ShiftCursorLeft()
{
    SendCommand(0x10);
    SendCommand(0x00);
}

void ShiftCursorRight()
{
    SendCommand(0x10);
    SendCommand(0x40);
}

void WriteChar(INT8U character)
{
    GPIO_PORTD_DATA_R |= 0x04;
    SendCommand(character);
    character = character << 4;
    SendCommand(character);
    GPIO_PORTD_DATA_R &= 0xFB;
}

void PrintString(INT64U string)
{

}

void ToggleColon()
{
    static INT8U Colon=1;

    SendCommand(0x80);
    SendCommand(0x20);
    GPIO_PORTD_DATA_R |= 0x04;

    if (Colon)
    {
        WriteChar(' ');
    }
    else
    {
        WriteChar(':');
    }

    GPIO_PORTD_DATA_R &= 0xFB;
    Colon ^= 1;
}

/****************************** END OF MODULE *******************************/
