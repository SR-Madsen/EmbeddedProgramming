#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "gpio.h"
#include "systick.h"
#include "tmodel.h"
#include "systick.h"
#include "rtcs.h"
#include "sw1task.h"
#include "leds.h"


int main(void)
/*****************************************************************************
*   Input    : NONE
*   Output   : Returns 0
*   Function : Init hardware and then loop forever
******************************************************************************/
{
  init_gpio();
  init_rtcs();

  start_task(TASK_SW1,switch_task);
  start_task(TASK_GREEN_LED,green_task);
  start_task(TASK_YELLOW_LED,yellow_task);
  start_task(TASK_RED_LED,red_task);

  schedule();

  return( 0 );
}
