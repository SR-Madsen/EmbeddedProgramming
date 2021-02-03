/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: main.c
*
* PROJECT....: EMP
*
* DESCRIPTION: Assignment 1, main module. No main.h file.
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150215  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "swtimers.h"
#include "systick.h"
#include "button.h"
#include "counter.h"
#include "countled.h"
#include "uart0.h"
#include "gpio.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
extern INT16S ticks;
/*****************************   Functions   *******************************/



int main(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : The super loop.
******************************************************************************/
{
  INT8U event = 0;
  INT8U old_event = 0;
  INT8U counter_value = 0;
  INT8U old_c_v = 0;
  INT8U alive_timer = TIM_500_MSEC;

  disable_global_int();
  init_systick();
  init_gpio();
  enable_global_int();

  INT32U baud_rate = 115200;
  INT8U databits = 8;
  INT8U stopbits = 1;
  INT8U parity = 'n';

  uart0_init(baud_rate, databits, stopbits, parity);

  // Loop forever.
  while(1)
  {
	// System part of the super loop.
    // ------------------------------
	while( !ticks );

	// The following will be executed every 5mS
    ticks--;

	if( ! --alive_timer )
	{
	  alive_timer        = TIM_500_MSEC;
	  GPIO_PORTD_DATA_R ^= 0x40;
	}

	// Application part of the super loop.
	// -----------------------------------
	old_event = event;
	event = select_button();
	if (old_event == event)
	{

	}
	else
	{
	    send_event(event);
	}
	old_c_v = counter_value;
	counter_value = counter( event );
	if (old_c_v == counter_value)
	{

	}
	else
	{
	    send_counter(counter_value);
	}
	counter_leds( counter_value );
  }
  return( 0 );
}

/****************************** End Of Module *******************************/
