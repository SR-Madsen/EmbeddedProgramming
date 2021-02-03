/************************************************************************************************
* UNIVERSITY OF SOUTHERN DENMARK
* EMBEDDED PROGRAMMING (EMP)
* Sebastian Rud Madsen
*
* MODULE NAME: main.c
*
* PROJECT: ASSIGNMENT 3
*
* DESCRIPTION:
*    - WRITE GENERAL FUNCTIONS FOR THE LCD-DISPLAY (CLEAR, SETCURSOR, WRITE CHARACTER, PRINT STRING) IN AN LCD.C AND LCD.H
*    - DESIGN A CLOCK WHICH PRINTS OUT HOURS AND MINUTES TO THE DISPLAY IN HH:MM FORMAT
*    - USE THE BUTTON (SWITCH 1) FUNCTIONALITY TO SET THE TIME
*       - A SINGLE PRESS COUNTS ONE MINUTE UP OR DOWN.
*       - A DOUBLE PRESS CHANGES DIRECTION
*       - A LONG PRESS MAKES THE CLOCK RUN
*       - WHEN THE TIME IS RUNNING, THE ":" CHARACTER WILL FLASH EVERY SECOND
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
#include "buttondriver.h"
#include "gpio.h"
#include "lcd.h"

/******************************************* DEFINES *******************************************/

/****************************************** CONSTANTS ******************************************/

/****************************************** VARIABLES ******************************************/
extern INT32U ticks;

/****************************************** FUNCTIONS ******************************************/


int main(void)
{
    INT8U event;
    INT8U alive_timer = 200;

    disable_global_int(); // TEMPORARILY DISABLE GLOBAL INTERRUPTS WHILE INITIALIZING SYSTICK
    init_systick(); // INITIALIZE SYSTICK
    enable_global_int(); // RE-ENABLE GLOBAL INTERRUPTS
    gpio_init(); // INITIALIZE GPIO


    // LOOP
    while(1)
    {
        while (!ticks); // EXECUTES EVERY 5 MS

        ticks--;

        if (!--alive_timer) // SIGNALS THAT PROGRAM IS RUNNING
        {
            alive_timer = 200; // ALIVE TIMER 1000 MS
            GPIO_PORTD_DATA_R ^= 0x40; // TOGGLE PD6 (RED LED ON EMP BOARD)

            ToggleColon();


            //WriteChar('1');
        }

        event = button_event_determine(); // BUTTON DRIVER
        //light_event_react(event); // TRAFFIC LIGHT


        //if (event)
        //{
        //    ShiftCursorLeft();
        //}
    }

    return 0;
}
