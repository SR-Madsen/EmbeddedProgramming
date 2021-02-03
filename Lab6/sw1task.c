#include "sw1task.h"
#include "tmodel.h"
#include "rtcs.h"

void switch_task(INT8U my_id, INT8U my_state, INT8U event, INT8U data)
{
    switch (my_state)
    {
    case 0:
    {
            if (GPIO_PORTF_DATA_R & 0x10)
            {
                //
            }
            else
            {
                set_state(1);
            }
        break;
    }

    case 1:
    {
        if (GPIO_PORTF_DATA_R & 0x10)
        {
            signal(SW1_SEM);
            set_state(0);
        }
        break;
    }

    default:
        set_state(0);
        break;
    }
}
