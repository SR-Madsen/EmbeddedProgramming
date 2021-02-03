/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: tmodel.h
*
* PROJECT....: ECP
*
* DESCRIPTION: Defines the elemtn of the task model..
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 101004  MoH   Module created.
*
*****************************************************************************/

#ifndef _TMODEL_H_
#define _TMODEL_H_

#include "rtcs.h"

// Tasks.
// ------
#define TASK_SW1         USER_TASK
#define TASK_YELLOW_LED  USER_TASK+1
#define TASK_GREEN_LED   USER_TASK+2
#define TASK_RED_LED     USER_TASK+3

// Semaphores
// ---------
#define SW1_SEM         USER_SEM
#define LED_ON_SEM      USER_SEM+1

// Interrupt Service Routines.
// ---------------------------
#define ISR_TIMER 21


#endif /* _TMODEL_H_ */
