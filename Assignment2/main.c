/************************************************************************************************
* UNIVERSITY OF SOUTHERN DENMARK
* EMBEDDED PROGRAMMING (EMP)
* Sebastian Rud Madsen
*
* MODULE NAME: main
*
* PROJECT: ASSIGNMENT 2
*
* DESCRIPTION:
*    - USE THE 3 LEDS ON THE EMP BOARD TO PROGRAM A TRAFFIC LIGHT
*    - THE LEDS MUST CYCLE AS A TRAFFIC LIGHT WOULD
*    - A SINGLE PRESS OF SWITCH 1 WILL MAKE THE YELLOW LIGHT FLASH ONCE PER SECOND
*    - A DOUBLE PRESS OF SWITCH 1 WILL MAKE THE RED LIGHT PERMANENTLY ON
*    - A 2-SECOND CONTINOUS PRESS RETURNS THE TRAFFIC LIGHT TO NORMAL OPERATION
*    - ALL TIMING IS CONTROLLED BY SYSTICK AND ITS "TICKS" VARIABLE
*    - THE TRAFFIC LIGHT MUST BE IMPLEMENTED AS A STATE MACHINE WITH SWITCH 1 PRESSES AND TIMING AS INPUT
*    - THE PROGRAM MUST HAVE A DRIVER WHICH READS SWITCH 1 AND HANDS PRESS EVENTS TO TRAFFIC LIGHT
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
#include "systick.h"
#include "buttondriver.h"
#include "gpio.h"
#include "trafficlight.h"
#include "emp_type.h"

/******************************************* DEFINES *******************************************/

/****************************************** CONSTANTS ******************************************/

/****************************************** VARIABLES ******************************************/
extern INT16U ticks;

/****************************************** FUNCTIONS ******************************************/


int main(void)
{
    INT8U event;
    INT8U alive_timer = 100;

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
            alive_timer = 100; // ALIVE TIMER 500 MS
            GPIO_PORTD_DATA_R ^= 0x40; // TOGGLE PD6 (RED LED ON EMP BOARD)
        }

        event = button_event_determine(); // BUTTON DRIVER
        light_event_react(event); // TRAFFIC LIGHT

    }

	return 0;
}
