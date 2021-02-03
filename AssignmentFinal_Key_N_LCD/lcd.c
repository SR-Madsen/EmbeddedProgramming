/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: lcd.c
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


/**************************************** INCLUDE FILES ****************************************/
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "lcd.h"
#include "tmodel.h"
#include "message_buffer.h"

/******************************************* DEFINES *******************************************/

/****************************************** CONSTANTS ******************************************/

/****************************************** VARIABLES ******************************************/

/****************************************** FUNCTIONS ******************************************/

/*****************************************************************************
*   ALL FUNCTIONS: See module specification (.h-file).
*****************************************************************************/
void init_lcd()
{
    // SETUP OF LCD DISPLAY
    for (INT16U i = 0; i < 25000; i++); // DELAY PÅ LIDT OVER 15 MS

    SendCommand(0x30);

    for (INT16U i = 0; i < 8000; i++); // DELAY PÅ 5 MS

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

    // REMOVE CURSOR BLINK
    SendCommand(0x00);
    SendCommand(0xC0);
}

// BRUG KUN DEN HER FUNKTION UNDER SETUP
void SendCommand(INT8U command)
{
    GPIO_PORTD_DATA_R |= 0x08;
    GPIO_PORTC_DATA_R = command;
    GPIO_PORTD_DATA_R &= 0xF7;

    for (INT8U i = 0; i<200; i++); // DELAY PÅ 120 MIKROSEKUNDER
}

// FUNKTIONER HERUNDER MÅ KUN BRUGES EKSTERNT, IKKE INTERNT
INT8U Write_Char(INT8U Ch)
{
  INT8U temp = Ch;
  return (xQueueSendToBack(Q_LED_DISP, &temp, portMAX_DELAY));
}

void Write_String(INT8U *pStr)
{
  while (*pStr)
  {
    Write_Char(*pStr);
    pStr++;
  }
}

void Move_Cursor(INT8U x, INT8U y)
{
  INT8U Pos;

  Pos = y*0x40 + x;
  Pos |= 0x80;
  Write_Char(ESC);
  Write_Char(Pos);
}

// FUNKTIONER HERUNDER MÅ KUN BRUGES INTERNT
void Write_Ctrl(INT8U Ch)
{
  INT16U i;

  Write_Ctrl_Low((Ch & 0xF0) >> 4); // WRITE CTRL HIGH
  for(i=0; i<1000; i++);
  Write_Ctrl_Low(Ch);
}

void Write_Ctrl_Low(INT8U Ch)
{
  INT8U temp;
  volatile int i;

  temp = GPIO_PORTC_DATA_R & 0x0F;
  temp  = temp | ((Ch & 0x0F) << 4);
  GPIO_PORTC_DATA_R  = temp;
  for (i=0; i<1000; i)
      i++;
  GPIO_PORTD_DATA_R &= 0xFB;        // Select Control mode, write
  for (i=0; i<1000; i)
      i++;
  GPIO_PORTD_DATA_R |= 0x08;        // Set E High

  for (i=0; i<1000; i)
      i++;

  GPIO_PORTD_DATA_R &= 0xF7;        // Set E Low

  for (i=0; i<1000; i)
      i++;
}

void Clear_Display()
{
  Write_Ctrl(0x01);
}


void Cursor_Home()
{
  Write_Ctrl(0x02);
}

void Set_Cursor(INT8U Ch)
{
  Write_Ctrl(Ch);
}


void Out_LCD(INT8U Ch)
{
  INT16U i;

  Out_LCD_Low((Ch & 0xF0) >> 4); // WRITE OUT HIGH
  for(i=0; i<1000; i++);
  Out_LCD_Low(Ch);
}

void Out_LCD_Low(INT8U Ch)
{
  INT8U temp;

  temp = GPIO_PORTC_DATA_R & 0x0F;
  GPIO_PORTC_DATA_R  = temp | ((Ch & 0x0F) << 4);
  GPIO_PORTD_DATA_R |= 0x04;        // Select data mode
  GPIO_PORTD_DATA_R |= 0x08;        // Set E High
  GPIO_PORTD_DATA_R &= 0xF7;        // Set E Low
}


void LCD_task(void * pvParameters)
{
    INT8U LCD_state = 0;
    INT8U in_char;

    while (1)
    {
        switch (LCD_state)
        {
        case LCD_R:
            if (xMessageBufferReceive(KEY_EVENT, &in_char, 1, 0))
            {
                switch (in_char)
                {
                case CLR:
                    Clear_Display();
                    break;

                case ESC:
                    LCD_state = 1;
                    break;

                default:
                    Out_LCD(in_char);
                }
            }
            break;

        case LCD_ESC:
            if (xMessageBufferReceive(KEY_EVENT, &in_char, 1, 0))
            {
              if (in_char & 0x80)
              {
                  Set_Cursor(in_char);
              }
              else
              {
                  switch (in_char)
                  {
                  case '@':
                      Cursor_Home();
                      break;
                  }
              }
              LCD_state = 0;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

/****************************** END OF MODULE *******************************/
