/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: key.h
*
* PROJECT....: Final assignment
*
* DESCRIPTION: FreeRTOS keyboard module for final assignment
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190516  SRM   Module created.
*
*****************************************************************************/

#ifndef _KEY_H
  #define _KEY_H

void keyboard_task(void * pvParameters);
/*****************************************************************************
*   Input    : Task parameters
*   Output   :
*   Function : Primary task for keyboard
******************************************************************************/

INT8U get_row(INT8U y_port);
/*****************************************************************************
*   Input    : Port E pin value
*   Output   : Corresponding row number
*   Function : Converts a pin value into actual row number
******************************************************************************/

INT8U get_key_val(INT8U x_num, INT8U y_num);
/*****************************************************************************
*   Input    : Column and row numbers
*   Output   : Corresponding key value for column x, row y
*   Function : Converts column and row values into actual key value
******************************************************************************/

#endif
