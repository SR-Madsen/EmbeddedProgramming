#ifndef LEDS_H_
#define LEDS_H_

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"

void green_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data);
void yellow_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data);
void red_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data);

#endif /* LEDS_H_ */
