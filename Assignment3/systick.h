/************************************************************************************************
* UNIVERSITY OF SOUTHERN DENMARK
* EMBEDDED PROGRAMMING (EMP)
*
* MODULE NAME: systick.h
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

#ifndef _EMP_H
  #define _EMP_H

/**************************************** INCLUDE FILES ****************************************/
#include "emp_type.h"

/******************************************* DEFINES *******************************************/

/****************************************** CONSTANTS ******************************************/

/****************************************** VARIABLES ******************************************/

/****************************************** FUNCTIONS ******************************************/

/*****************************************************************************
*   ALL FUNCTIONS: See module specification (.h-file).
*****************************************************************************/

void enable_global_int();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Enable global interrupt.
******************************************************************************/

void disable_global_int();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Disable global interrupt.
******************************************************************************/

void init_systick();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Initialize the systick interrupt.
******************************************************************************/

void delay(INT8U delay_time);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Used for delay during initialization.
******************************************************************************/

/****************************** END OF MODULE *******************************/
#endif /* SYSTICK_H_ */
