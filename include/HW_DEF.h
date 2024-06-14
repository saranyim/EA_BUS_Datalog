#include "gd32f30x.h"

#define pcf8536_i2c I2C0


//-- EC200 
#define ec200Uart USART0
#define ec200UartISR USART0_IRQHandler
#define _oCT3V8_Port GPIOA
#define _oCT3V8_Pin GPIO_PIN_0

#define _oPWR_Port GPIOA
#define _oPWR_Pin GPIO_PIN_12

#define _DTR_PORT GPIOA
#define _DTR_PIN GPIO_PIN_11
//-- END EC200

#define _LEDR_PORT GPIOB
#define _LEDR_PIN GPIO_PIN_3

#define _LEDG_PORT GPIOB
#define _LEDG_PIN GPIO_PIN_4

#define _LEDB_PORT GPIOB
#define _LEDB_PIN GPIO_PIN_5


//-- UART to CAN
#define CANUART USART1
#define CANUARTISR USART1_IRQHandler