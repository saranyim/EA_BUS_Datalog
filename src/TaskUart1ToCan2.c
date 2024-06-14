#include "main.h"



#define uart1RxBufSize 32
#define _txBufSize 16
#define _rxBufSize 32

void TaskUART1();

StaticTask_t xUARTBuffer1;
StackType_t xUARTStack1[STACK_SIZE];
TaskHandle_t UARTHandle1;


uint8_t uartTxBuf1[uart1RxBufSize];
uint8_t uartRxBuf1[uart1RxBufSize];
volatile char UART1_Data;
uint16_t txIndex1;
uint16_t txLen1;
uint16_t rxIndex1;
uint16_t rxTimeOut1;

uint16_t rxByte1;

uint16_t fRxReady1;

#define DATA_SIZE 16
#define QUEUE_LENGTH 10 // Adjust based on expected processing time and data rate
j1939_Header_t uart1939Header;
// Create a queue handle
QueueHandle_t xQueueU1Rx;
can_receive_message_struct uartCanRx;
ErrStatus CheckRxChks(uint8_t * inputBuf){
	uint16_t len = inputBuf[0] & 0x7F;
	uint8_t chks = 0;
	for(int i =0; i < len;i++){
		chks += inputBuf[i];
	}
	return (inputBuf[len] == chks)?(SUCCESS):(ERROR);
}

void CANUARTISR(void)
{
    if(RESET != usart_interrupt_flag_get(CANUART, USART_INT_FLAG_RBNE)){
        /* receive data */
     	rxByte1 = usart_data_receive(CANUART);
		if((rxByte1 == 0x8F) && (rxIndex1 == 0)){

		}
		uartRxBuf1[rxIndex1++] = rxByte1;
		
		if(rxIndex1 == 16){
			rxIndex1 = 0;
			BaseType_t xHigherPriorityTaskWoken = pdFALSE;
			vTaskNotifyGiveFromISR( UARTHandle1, &xHigherPriorityTaskWoken);
			if( xHigherPriorityTaskWoken )
			{
				/* Actual macro used here is port specific. */
				// taskYIELD_FROM_ISR ();
				
				portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
			}
		}

    }
    if(RESET != usart_interrupt_flag_get(CANUART, USART_INT_FLAG_TBE)){
        /* transmit data */
        usart_data_transmit(CANUART, uartTxBuf1[txIndex1++]);
        if(txIndex1 == txLen1){
            usart_interrupt_disable(CANUART, USART_INT_TBE);
        }
    }
}

void StartTxUart2CANPC(){
	uint16_t chks;
	txLen1 = (uartTxBuf1[0] & 0x7F);
	txIndex1 = 0;
		chks = 0;
	for(int i =0 ;i < txLen1;i++)
		chks += uartTxBuf1[i];
	uartTxBuf1[txLen1] = chks;
	txLen1 += 1;
	usart_data_transmit(CANUART, uartTxBuf1[txIndex1++]);
    usart_interrupt_enable(CANUART, USART_INT_TBE);
}


void InitTaskUART1(){

	InitUSART_1_GPIOA_2_3(460800); // to CAN	
	UARTHandle1 = xTaskCreateStatic(
	TaskUART1,      /* Function that implements the task. */
	"UARTTask",         /* Text name for the task. */
	 STACK_SIZE,       /* Number of indexes in the xBlinkyStack array. */
	(void *)0,        /* Parameter passed into the task. */
	configMAX_PRIORITIES - 1, /* Priority at which the task is created. */
	xUARTStack1,           /* Array to use as the task's stack. */
	&xUARTBuffer1);    /* Variable to hold the task's data structure. */

	
}


void TaskUART1(){

	vTaskDelay(500);
	uartTxBuf1[0] = 0x8F;
	uartTxBuf1[1] = 0xFF;
	uartTxBuf1[2] = 0xFF;
	uartTxBuf1[3] = 0xFF;
	uartTxBuf1[4] = 0xFF;
	uartTxBuf1[5] = 3;
	uartTxBuf1[6] = 16;
	uartTxBuf1[7] =	0xFF;
	uartTxBuf1[8] = 0xFF;
	uartTxBuf1[9] = 0xFF;
	uartTxBuf1[10] = 0xFF;
	uartTxBuf1[11] = 0xFF;
	uartTxBuf1[12] = 0xFF;
	uartTxBuf1[13] = 0xFF;
	uartTxBuf1[14] = 1;

		
	StartTxUart2CANPC();
	usart_interrupt_enable(USART1, USART_INT_RBNE);

	vTaskDelay(100);
	


	while(1)
	{
		 if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) == pdPASS)
		 {
			if(CheckRxChks(uartRxBuf1))
			{
				uartCanRx.rx_efid = BYTES_TO_UINT32_BE(uartRxBuf1 + 1);
				memcpy(uartCanRx.rx_data,uartRxBuf1 + 6,8);
				uartCanRx.rx_dlen = uartRxBuf1[14];
				HData(1,uartCanRx);
				// (gpio_output_bit_get(_LEDR_PORT,_LEDR_PIN))?gpio_bit_reset(_LEDR_PORT,_LEDR_PIN):gpio_bit_set(_LEDR_PORT,_LEDR_PIN);;
       
			}
            
        }
	}

}