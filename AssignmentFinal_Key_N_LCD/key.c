/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: key.c
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
* 150321  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
#include "emp_type.h"
#include "key.h"
#include "tmodel.h"
#include "message_buffer.h"

void keyboard_task(void * pvParameters)
{
  INT8U y_port;
  INT8U key_val;
  INT8U key_state = 0;
  INT8U x_num = 1;

  while (1)
  {
      switch (key_state)
      {
          case 0:
          {
              GPIO_PORTA_DATA_R |= 0x04;
              GPIO_PORTF_DATA_R |= 0x0E;
              key_state = 1;
              break;
          }

          case 1:
          {
              y_port = GPIO_PORTE_DATA_R & 0x0F;
              if (y_port)
              {
                  GPIO_PORTF_DATA_R &= 0xFD;
                  key_val = get_key_val (x_num, get_row(y_port));
                  xMessageBufferSend(KEY_EVENT, &key_val, 1, portMAX_DELAY);
                  key_state = 2;
              }
              else
              {
                  x_num++;
                  if (x_num > 3)
                  {
                      x_num = 1;
                  }

                  GPIO_PORTA_DATA_R &= 0xE3;
                  GPIO_PORTA_DATA_R |= (0x01 << (x_num+1));
                  y_port = GPIO_PORTA_DATA_R;
              }
              break;
          }

          case 2:
          {
              if (!(GPIO_PORTE_DATA_R & 0x0F))
              {
                  x_num = 1;
                  GPIO_PORTA_DATA_R |= 0x04;
                  key_state = 1;
              }
              break;
          }
      }
      vTaskDelay(pdMS_TO_TICKS(5));
  }
}

INT8U get_row(INT8U y_port)
{
  INT8U result;

  switch (y_port)
  {
    case 0x01:
        {
            result = 1;
            break;
        }

    case 0x02:
        {
            result = 2;
            break;
        }

    case 0x04:
        {
            result = 3;
            break;
        }

    case 0x08:
        {
            result = 4;
            break;
        }
    default:
        {
            result = 0;
            break;
        }
  }

  return result;
}

INT8U get_key_val(INT8U x_num, INT8U y_num)
{
  const INT8U matrix[3][4] = {{'#','9','6','3'},
                              {'0','8','5','2'},
                              {'*','7','4','1'}};

  return (matrix[x_num-1][y_num-1]);
}
