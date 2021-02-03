#ifndef SPI_H_
#define SPI_H_

#include "emp_type.h"

#define SSI_SLAVE_DAC 0
#define SSI_SLAVE_ADCV 1
#define SSI_SLAVE_ADCI 2

void init_spi();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Initialize SPI for use (Module 0, Port A)
******************************************************************************/

void spi_task(void * pvParameters);
/*****************************************************************************
*   Input    : Parameters used by operating system.
*   Output   : -
*   Function : Performs SPI related operations.
******************************************************************************/

void spi_task(void * pvParameters);
/*****************************************************************************
*   Input    : Parameters used by operating system.
*   Output   : -
*   Function : Alternative version of function that performs SPI related operations.
******************************************************************************/

void send_data(INT16U data, INT8U slave);
/*****************************************************************************
*   Input    : 16 bits of data with information to DAC/ADC and 8-bit slave identifier.
*   Output   : -
*   Function : Send 16-bit data to a specific slave.
******************************************************************************/

void write_data(INT16U data);
/*****************************************************************************
*   Input    : 16-bit data value to be put into transmit buffer.
*   Output   : -
*   Function : Write to transmit data buffer.
******************************************************************************/

INT16U get_data();
/*****************************************************************************
*   Input    : -
*   Output   : 16-bit value from data buffer.
*   Function : Read the receive data buffer.
******************************************************************************/

void clear_buffer();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Clears the receive data buffer.
******************************************************************************/

#endif /* SPI_H_ */
