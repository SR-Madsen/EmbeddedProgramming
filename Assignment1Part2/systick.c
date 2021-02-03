/************************************************************************************************
* UNIVERSITY OF SOUTHERN DENMARK
* EMBEDDED PROGRAMMING (EMP)
*
* MODULE NAME: systick.c
*
* PROJECT: ASSIGNMENT 1
*
*
* CHANGE LOG:
*************************************************************************************************
* DATE      ID      CHANGE
* YYMMDD
* ---------------------------------
* 19-02-20  SM      MODULE CREATED
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
volatile INT8U RGBvalues[] = {0x00, 0x08, 0x04, 0x0C, 0x02, 0x0A, 0x06, 0x0E}; // ARRAY WITH BINARY RGB VALUES

/****************************************** VARIABLES ******************************************/
volatile INT32U ticks = 51; // INITIALIZED TO 51 TO AVOID BUG WHERE CLICKING INSTANTLY AFTER RESET WOULD TOGGLE COUNTING DIRECTION
volatile INT8U counter = 0; // BINARY COUNTER
volatile INT8U toggle = 0; // 0 = COUNT UP, 1 = COUNT DOWN
volatile INT32U tickstart = 0; // USED FOR TIME-MANAGING
volatile INT8U automode = 0; // 0 = OFF, 1 = ON
volatile INT32U dclick_time = 0; // USED FOR TIME-MANAGING

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

void on_press()
{
    if (ticks-dclick_time <= 50)
    {
        toggle ^= 1;
    }
    delay(); // DEBOUNCING FUNCTION

    //double_click();

    tickstart = ticks;
    while ((GPIO_PORTF_DATA_R & 0x10) == 0)
    {
        if (ticks-tickstart >= 400) // IF HELD FOR MORE THAN 2 SECONDS, INITIATE AUTO-MODE
        {
            automode = 1;
            auto_mode();
        }
    }

    if (toggle)
    {
        count_down();
    }
    else
    {
        count_up();
    }

    dclick_time = ticks;

    delay(); // DEBOUNCING
}

void count_up()
{
    if (counter == 7)
    {
        counter = 0;
    }
    else
    {
        counter++;
    }

    GPIO_PORTF_DATA_R = RGBvalues[counter];
}

void count_down()
{
    if (counter == 0)
    {
        counter = 7;
    }
    else
    {
        counter--;
    }

    GPIO_PORTF_DATA_R = RGBvalues[counter];
}

void delay()
{
    tickstart = ticks;
    while (ticks-tickstart <= 5)
    {
        // DO NOTHING TO CREATE DELAY
    }
}

void double_click()
{
}

void auto_mode()
{
    tickstart = ticks;

    while ((GPIO_PORTF_DATA_R & 0x10) == 0) // THIS LOOP TAKES CARE OF AUTO-MODE WHILE BUTTON IS STILL INITIALLY HELD DOWN
    {
        if (ticks-tickstart >= 40)
        {
                if (toggle)
                {
                    count_down();
                }
                else
                {
                    count_up();
                }
                tickstart = ticks;
        }
    }

    delay(); // DEBOUNCING

    while (automode) // THIS LOOP TAKES CARE OF AUTO-MODE AFTER BUTTON IS RELEASED - CLICKING IT AGAIN WILL DISABLE
    {
        if (GPIO_PORTF_DATA_R & 0x10)
        {
            if (ticks-tickstart >= 40)
            {
                if (toggle)
                {
                    count_down();
                }
                else
                {
                    count_up();
                }
                tickstart = ticks;
            }
        }
        else
        {
            automode = 0;
        }
    }
}

/****************************** End Of Module *******************************/
