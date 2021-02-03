/************************************************************************************************
* UNIVERSITY OF SOUTHERN DENMARK
* EMBEDDED PROGRAMMING (EMP)
*
* MODULE NAME: buttondriver.c
*
* PROJECT: ASSIGNMENT 3
*
*
* CHANGE LOG:
*************************************************************************************************
* DATE      ID      CHANGE
* YYMMDD
* ---------------------------------
* 19-03-09  SM      MODULE CREATED
*************************************************************************************************/


/**************************************** INCLUDE FILES ****************************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "systick.h"
#include "buttondriver.h"

/******************************************* DEFINES *******************************************/

/****************************************** CONSTANTS ******************************************/

/****************************************** VARIABLES ******************************************/

/****************************************** FUNCTIONS ******************************************/

/*****************************************************************************
*   ALL FUNCTIONS: See module specification (.h-file).
*****************************************************************************/

/* EVENTS:
 * 0 = IDLE/NOTHING
 * 1 = SINGLE PRESS
 * 2 = DOUBLE PRESS
 * 3 = LONG PUSH
 *
 */

INT8U button_pushed()
{
  return( !(GPIO_PORTF_DATA_R & 0x10) );
}

INT8U button_event_determine(void)
{
  static INT8U  button_state = 0;
  static INT16U button_timer;
         INT8U  button_event = 0;

  switch (button_state)
  {
    case 0:
        if (button_pushed()) // IF SW1 PUSHED
        {
            button_state = 1; // FIRST PRESS STATE
            button_timer = 400; // START TIMER = 2 SEC
        }
        break;

    case 1:
        if (!--button_timer) // IF TIMED OUT
        {
            button_state = 4; // LONG PUSH STATE
            button_event = 3; // LONG PUSH EVENT
        }
        else
        {
        if (!button_pushed()) // IF BUTTON RELEASED
        {
            button_state = 2; // FIRST RELEASE STATE
            button_timer = 20; // START TIMER = 100 MSEC
        }
        }
        break;

    case 2:
        if (!--button_timer) // IF TIMED OUT
        {
            button_state = 0; // IDLE STATE
            button_event = 1; // SINGLE PUSH EVENT
        }
        else
        {
        if (button_pushed()) // IF BUTTON PRESSED
        {
            button_state = 3; // SECOND PRESS STATE
            button_timer = 400; // START TIMER = 2 SEC
        }
        }
        break;

    case 3:
        if (!--button_timer) // IF TIMED OUT
        {
            button_state = 4; // LONG PUSH STATE
            button_event = 3; // LONG PUSH EVENT
        }
        else
        {
        if (!button_pushed()) // IF BUTTON RELEASED
        {
            button_state = 0; // IDLE STATE
            button_event = 2; // DOUBLE PRESS EVENT
        }
        }
        break;

    case 4:
        if (!button_pushed()) // IF BUTTON RELEASED
        {
            button_state = 0; // IDLE STATE
        }
        break;

    default:
        break;
  }

  return (button_event);
}

/****************************** END OF MODULE *******************************/
