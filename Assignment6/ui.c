/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: ui.c
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
* 050128  KA    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "gpio.h"
#include "systick.h"
#include "tmodel.h"
#include "systick.h"
#include "ui.h"
#include "rtc.h"
#include "string.h"
#include "rtcs.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
INT8U i;
INT8U  InBuf[128];

/*****************************   Functions   *******************************/


void ui_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
  INT8U ch;

  if( get_file( COM1, &ch ))
  {
    if( i < 128 )
      InBuf[i++] = ch;
    put_file( COM1, ch );
    if( ch == '\r' )
    {
      if(( InBuf[0] == '1' ) && ( i >= 7 ))
      {
          set_hour( (InBuf[1]-'0')*10+InBuf[2]-'0');
          set_min( (InBuf[3]-'0')*10+InBuf[4]-'0');
          set_sec( (InBuf[5]-'0')*10+InBuf[6]-'0');
      }
      gfprintf( COM1, "%c%02d%02d%02d\r\n", InBuf[0], get_hour(), get_min(), get_sec() );
      i = 0;

      if((( InBuf[0] == 'p') && (InBuf[1] == 's')) || ((InBuf[0] == 'P') && (InBuf[1] == 'S')))
      {
          signal(SEM_PS);
      }
    }
  }

}

void ui_key_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
  INT8U ch;

  if( get_file( COM3, &ch ))
  {
    switch( my_state )
    {
    case 0:
      gfprintf( COM2, "%c%c%c", 0x1B, 0xC4, ch );
      set_state( 1 );
      break;
    case 1:
      gfprintf( COM2, "%c%c%c:", 0x1B, 0xC5, ch );
      set_state( 2 );
      break;
    case 2:
      gfprintf( COM2, "%c%c%c", 0x1B, 0xC7, ch );
      set_state( 3 );
      break;
    case 3:
      gfprintf( COM2, "%c%c%c:", 0x1B, 0xC8, ch );
      set_state( 4 );
      break;
    case 4:
      gfprintf( COM2, "%c%c%c", 0x1B, 0xCA, ch );
      set_state( 5 );
      break;
    case 5:
      gfprintf( COM2, "%c%c        ", 0x1B, 0xC4 );
      set_state( 0 );
      break;
    }
  }
}


/****************************** End Of Module *******************************/












