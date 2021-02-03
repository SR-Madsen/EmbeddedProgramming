#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "systick.h"


#define SYSTICK_RELOAD_VALUE 80000 // 5 MS INTERRUPT
#define SYSTICK_PRIORITY 0x7E

INT16S ticks = 0; // TICK COUNTER
int tickstart = 0; // TO KEEP TRACK OF TIME


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

int* onpress(int toggle, int counter, int RGBvalues[8])
{
    static int temp[2];

    if (toggle)
    {
        temp[0] = countdown(counter, RGBvalues);
    }
    else
    {
        temp[0] = countup(counter, RGBvalues);
    }

    tickstart = ticks;
    //antiwobble(tickstart);
    temp[1] = doubleclick(tickstart, toggle);

    return temp;
}

int countup(int counter, int RGBvalues[8])
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

    return counter;
}

int countdown(int counter, int RGBvalues[8])
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

    return counter;
}

/*
void antiwobble(int tickstart)
{
    while (ticks-tickstart <= 5)
    {
    }
}
*/

int doubleclick(int tickstart, int toggle)
{
    while (ticks-tickstart <= 65)
    {
        if (GPIO_PORTF_DATA_R &= 0x10)
        {
        }
        else
        {
            toggle ^= 1;
            return toggle;
        }
    }
    return toggle;
}
