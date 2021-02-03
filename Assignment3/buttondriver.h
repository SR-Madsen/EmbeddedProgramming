/************************************************************************************************
* UNIVERSITY OF SOUTHERN DENMARK
* EMBEDDED PROGRAMMING (EMP)
*
* MODULE NAME: buttondriver.h
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

#ifndef BUTTONDRIVER_H_
#define BUTTONDRIVER_H_

/***************************** Include files *******************************/
#include "emp_type.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

INT8U button_pushed();
/*****************************************************************************
*   Input    : -
*   Output   : 0 if button not pushed, 1 if button is pushed.
*   Function : Checks current state of switch 1.
******************************************************************************/

INT8U button_event_determine();
/*****************************************************************************
*   Input    : -
*   Output   : Number depending on which event has happened.
*   Function : Determines which event has happened; single-press, double-press or long-press.
******************************************************************************/

/****************************** End Of Module *******************************/
#endif /* BUTTONDRIVER_H_ */
