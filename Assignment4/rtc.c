/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: rtc.c
*
* PROJECT....: ECP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 090926  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "emp_type.h"
#include "tmodel.h"
//#include "devices.h"
#include "swtimers.h"
#include "events.h"
#include "messages.h"
#include "tmodel.h"
#include "lcd.h"
#include "sem.h"


/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/


void rtc_task( INT8U task_no )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Disable global interrupt
******************************************************************************/
{
  static INT8U rtc_state = 0;
  INT8U sec, min, hour;

  switch( rtc_state )
  {
    case 0:
      //turn_led( LED_YELLOW, TURN_LED_OFF );
      start_swtimer( ST_RTC, SEB_TO_RTC, MILLISEC(1000) );
      rtc_state = 1;
      break;
    case 1:
      if( get_msg_event( SEB_TO_RTC )) // time out
      {
        //turn_led( LED_YELLOW, TOGGLE_LED );
        sec = get_msg_state( SSM_RTC_SEC );
        sec++;
        if( sec >= 60 )
        {
          min = get_msg_state( SSM_RTC_MIN );
          min++;
          if( min >= 60 )
          {
            hour = get_msg_state( SSM_RTC_HOUR );
        	hour++;
        	if( hour >= 24 )
        	  hour = 0;
            put_msg_state( SSM_RTC_HOUR, hour );
        	min = 0;
          }
          put_msg_state( SSM_RTC_MIN, min );
          sec = 0;
        }
        put_msg_state( SSM_RTC_SEC, sec );
        start_swtimer( ST_RTC, SEB_TO_RTC, MILLISEC(1000) );
        signal( SEM_RTC_UPDATED );
      }
      break;
  }
}

void display_rtc_task( INT8U task_no )
{
  INT8U sec;
  INT8U min;
  INT8U hour;
  
  if( wait( SEM_RTC_UPDATED ))
  {
    if( wait( MUTEX_LCD_DISPLAY ))
    {
      if( wait( MUTEX_SYSTEM_RTC ))
      {
        sec  = get_msg_state( SSM_RTC_SEC  );
        min  = get_msg_state( SSM_RTC_MIN  );
        hour = get_msg_state( SSM_RTC_HOUR );
        
        move_LCD( 4, 0 );
        wr_ch_LCD( (INT8U)(hour/10+'0') );
        wr_ch_LCD( (INT8U)(hour%10+'0') );
        if( sec & 0x01 )
          wr_ch_LCD( ':' );
        else
          wr_ch_LCD( ' ' );
        wr_ch_LCD( (INT8U)(min/10+'0') );
        wr_ch_LCD( (INT8U)(min%10+'0') );
        if( sec & 0x01 )
          wr_ch_LCD( ' ' );
        else
          wr_ch_LCD( ':' );
        wr_ch_LCD( (INT8U)(sec/10+'0') );
        wr_ch_LCD( (INT8U)(sec%10+'0') );
      
        signal( MUTEX_SYSTEM_RTC );
      }
      signal( MUTEX_LCD_DISPLAY );
    }
  }
}

void ajust_rtc_task( INT8U task_no )
{
  static INT8U state = 0;
  static INT8U sec;
  static INT8U min;
  static INT8U hour;
  
  switch( state )
  {
    case 0:
      if( get_msg_event( SEB_BUTTON_EVENT ) == BE_LONG_PUSH )
      {
        if( wait( MUTEX_LCD_DISPLAY ))
        {
          if( wait( MUTEX_SYSTEM_RTC ))
          {
            min = get_msg_state( SSM_RTC_MIN );
            move_LCD( 0, 0 );
            wr_ch_LCD( 0xFF );
            wr_str_LCD( "Min: ");
            wr_ch_LCD( (INT8U)(min/10+'0') );
            wr_ch_LCD( (INT8U)(min%10+'0') );
          }
          signal( MUTEX_SYSTEM_RTC );
        }
        state = 1;
      }
      break;
    case 1:
      switch( get_msg_event( SEB_BUTTON_EVENT ))
      {
        case BE_SINGLE_PUSH:
          min++;
          if( min >= 60 )
            min = 0;
          move_LCD( 5, 0 );
          wr_ch_LCD( (INT8U)(min/10+'0') );
          wr_ch_LCD( (INT8U)(min%10+'0') );
          break;
        case BE_LONG_PUSH:
          put_msg_state( SSM_RTC_MIN, min );
          move_LCD( 0, 0 );
          wr_ch_LCD( 0xFF );
          signal( MUTEX_LCD_DISPLAY );
          state = 0;
          break;
          
      }
      break;
  }
}

/****************************** End Of Module *******************************/












