#include "main.h"

#define CAN_BAUDRATE  250 

StaticTask_t xCANTaskBuffer;
StackType_t xCANStack[STACK_SIZE];
TaskHandle_t CANTaskHandle;




j1939_Header_t j1939Header;
can_receive_message_struct bcuRxMessage;
can_receive_message_struct canRxData[22][10];


void TaskCAN(void *pvParameters);

///////////////////////////////////////////////////////////////////

void InitTaskCAN(){
    Init_CAN0_GPIOB_8_9(250);

   
    CANTaskHandle = xTaskCreateStatic(
        TaskCAN,      /* Function that implements the task. */
        "CANRX",         /* Text name for the task. */
        STACK_SIZE,       /* Number of indexes in the xBlinkyStack array. */
        (void *)0,        /* Parameter passed into the task. */
        tskIDLE_PRIORITY, /* Priority at which the task is created. */
        xCANStack,           /* Array to use as the task's stack. */
        &xCANTaskBuffer);    /* Variable to hold the task's data structure. */

}

void TaskCAN(void *pvParameters){
    uint8_t bcuDestination;
    float averageV;
    uint16_t pfCmd;
    j1939_Header_t txHeader;
  
    can_trasnmit_message_struct transmit_message;

    while(1){
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		// gpio_bit_reset(_LEDR_PORT,_LEDR_PIN);
        // gpio_bit_reset(_LEDG_PORT,_LEDG_PIN);
        // gpio_bit_reset(_LEDB_PORT,_LEDB_PIN);
        HData(0,bcuRxMessage);
        // (gpio_output_bit_get(_LEDR_PORT,_LEDR_PIN))?gpio_bit_reset(_LEDR_PORT,_LEDR_PIN):gpio_bit_set(_LEDR_PORT,_LEDR_PIN);;
        // (gpio_output_bit_get(_LEDG_PORT,_LEDG_PIN))?gpio_bit_reset(_LEDG_PORT,_LEDG_PIN):gpio_bit_set(_LEDG_PORT,_LEDG_PIN);;
        // (gpio_output_bit_get(_LEDB_PORT,_LEDB_PIN))?gpio_bit_reset(_LEDB_PORT,_LEDB_PIN):gpio_bit_set(_LEDB_PORT,_LEDB_PIN);;
            
    }
}

void CAN0_RX1_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
     /* check the receive message */
    can_message_receive(CAN0, CAN_FIFO1, &bcuRxMessage);
    vTaskNotifyGiveFromISR( CANTaskHandle, &xHigherPriorityTaskWoken);
    if( xHigherPriorityTaskWoken )
    {
        /* Actual macro used here is port specific. */
        // taskYIELD_FROM_ISR ();
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}
