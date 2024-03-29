/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: lcd.h
*
* PROJECT....: Final assignment
*
* DESCRIPTION: FreeRTOS LCD module for final assignment
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190516  SRM   Module created.
*
*****************************************************************************/

#ifndef LCD_H_
#define LCD_H_

/**************************************** INCLUDE FILES ****************************************/
#include "emp_type.h"

/******************************************* DEFINES *******************************************/
#define ESC     0x1B
#define CLR     0xFF

#define LCD_R   0
#define LCD_ESC 1

/****************************************** CONSTANTS ******************************************/

/****************************************** VARIABLES ******************************************/

/****************************************** FUNCTIONS ******************************************/

/*****************************************************************************
*   ALL FUNCTIONS: See module specification (.h-file).
*****************************************************************************/

void init_lcd();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Initializes LCD display.
******************************************************************************/

void SendCommand(INT8U command);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Sends a 4-bit command to the LCD display.
******************************************************************************/

INT8U Write_Char(INT8U Ch);
/*****************************************************************************
*   Input    : 8-bit character to be sent to the LCD.
*   Output   : If character was put into queue, returns TRUE.
*   Function : Puts an 8-bit character into the LCD queue.
******************************************************************************/

void Write_String(INT8U *pStr);
/*****************************************************************************
*   Input    : Pointer to start of string.
*   Output   : -
*   Function : Puts entire string into LCD queue.
******************************************************************************/

void Move_Cursor(INT8U x, INT8U y);
/*****************************************************************************
*   Input    : Coordinates on LCD display
*   Output   : -
*   Function : Moves cursor on LCD display
******************************************************************************/

void Write_Ctrl(INT8U Ch);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Write control data to LCD.
******************************************************************************/

void Write_Ctrl_Low(INT8U Ch);
/*****************************************************************************
*   Input    : 8-bit character to be sent to the LCD.
*   Output   : -
*   Function : Write low part of control data to LCD.
******************************************************************************/


void Clear_Display();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Clear LCD.
******************************************************************************/

void Cursor_Home();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Return cursor to the home position.
******************************************************************************/

void Set_Cursor(INT8U Ch);
/*****************************************************************************
*   Input    : New Cursor position
*   Output   : -
*   Function : Place cursor at given position.
******************************************************************************/

void Out_LCD(INT8U Ch);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Write control data to LCD.
******************************************************************************/

void Out_LCD_Low(INT8U Ch);
/*****************************************************************************
*   Input    : Mask
*   Output   : -
*   Function : Send low part of character to LCD.
******************************************************************************/

void LCD_task(void * pvParameters);
/*****************************************************************************
*   Input    : Task parameters.
*   Output   : -
*   Function : LCD task for FreeRTOS.
******************************************************************************/

/****************************** END OF MODULE *******************************/

#endif /* LCD_H_ */
