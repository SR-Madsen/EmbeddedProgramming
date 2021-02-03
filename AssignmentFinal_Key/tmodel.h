/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: tmodel.h
*
* PROJECT....: EMP
*
* DESCRIPTION: Task model definitions
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 190516  JFH   Module created.
*
*****************************************************************************/

#ifndef TMODEL_H_
#define TMODEL_H_

/***************************** Include files *******************************/
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "message_buffer.h"

/*****************************    Defines    *******************************/

/********************** External declaration of Variables ******************/
//Queues
xQueueHandle Q_UART_TX;             // Uart Transmit Queue
xQueueHandle Q_UART_RX;             // UART Receive Queue
xQueueHandle Q_LED_DISP;            // LED Display Queue
xQueueHandle Q_LOG_STRUCT;          // Log Struct Queue

// Semaphores
xSemaphoreHandle SEM_FUEL_COUNT;    // Fuel Count Semaphore
xSemaphoreHandle SEM_RTC;           // RTC Semaphore

// Message buffer
MessageBufferHandle_t   BUTTON_EVENT;   // Button event message
MessageBufferHandle_t   KEY_EVENT;      // Key event message
MessageBufferHandle_t   FUEL_LIMIT;     // Fuel limit message
MessageBufferHandle_t   DREH_EVENT;     // Drehimpulsgeber message
MessageBufferHandle_t   APPR_LIMIT;     // Limit approaching message
MessageBufferHandle_t   TERMINATE;      // Terminate refueling message

// Structs
typedef struct
{
    INT32U  time_begin;     // Time where refueling begins in seconds
    INT32U  time_end;       // Time where refueling ends in seconds
    INT8U   product;        // Product, 1 for 92 Octane, 2 for 95 Octane, 4 for E10
    INT16U  qty;            // Amount of fuel in 0.1 L
    INT16U  price;          // Price in 0.01 DKK
    INT8U   pay_type;       // Payment type, 0 for cash, 1 for account
}logParam;


/*****************************   Constants   *******************************/


/*************************  Function interfaces ****************************/


/****************************** End Of Module *******************************/

#endif /* TMODEL_H_ */
