/************************************************************************************************
* UNIVERSITY OF SOUTHERN DENMARK
* EMBEDDED PROGRAMMING (EMP)
*
* MODULE NAME: systick.c
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


/**************************************** INCLUDE FILES ****************************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "systick.h"

/******************************************* DEFINES *******************************************/
#define SYSTICK_RELOAD_VALUE 80000 // 5 MS
#define SYSTICK_PRIORITY 0x7E

/****************************************** CONSTANTS ******************************************/

/****************************************** VARIABLES ******************************************/
volatile INT32U ticks = 0;

/****************************************** FUNCTIONS ******************************************/

/*****************************************************************************
*   ALL FUNCTIONS: See module specification (.h-file).
*****************************************************************************/

void systick_handler(void)
{
  ticks++;
}

void enable_global_int()
{
  // Enable interrupts
  __asm("cpsie i");
}

void disable_global_int()
{
  // Disable interrupts
  __asm("cpsid i");
}

void init_systick()
{
  // Disable systick timer
  NVIC_ST_CTRL_R &= ~(NVIC_ST_CTRL_ENABLE);

  // Set current systick counter to reload value
  NVIC_ST_CURRENT_R = SYSTICK_RELOAD_VALUE;
  // Set Reload value, Systick reload register
  NVIC_ST_RELOAD_R = SYSTICK_RELOAD_VALUE;

  // NVIC systick setup, vector number 15
  // Clear pending systick interrupt request
  NVIC_INT_CTRL_R |= NVIC_INT_CTRL_UNPEND_SYST;

  // Set systick priority to 0x10, first clear then set.
  NVIC_SYS_PRI3_R &= ~(NVIC_SYS_PRI3_TICK_M);
  NVIC_SYS_PRI3_R |= (NVIC_SYS_PRI3_TICK_M & (SYSTICK_PRIORITY<<NVIC_SYS_PRI3_TICK_S));

  // Select systick clock source, Use core clock
  NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC;

  // Enable systick interrupt
  NVIC_ST_CTRL_R |= NVIC_ST_CTRL_INTEN;

  // Enable and start timer
  NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;
}

void delay(INT8U delay_time)
{
    INT16U temp = ticks;
    while (ticks-temp < delay_time)
    {
        // DO NOTHING
    }
}

/****************************** END OF MODULE *******************************/
