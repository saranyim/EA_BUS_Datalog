#include "main.h"

//#define DATA_PRINT                                          /* uncomment the macro to print out the data */

StaticTask_t xTestTaskBuffer;
StackType_t xTestStack[STACK_SIZE];
TaskHandle_t hTaskTest;


void nvic_config(void);
void SDCardTest();
void InitGPIO();
void TaskTest();
void InitRCU();

volatile uint16_t testVal1,tV2,tV3;
uint16_t chipID;
#define uidBaseAddr 0x1FFFF7E8

void GenChipID(){
	uint16_t *waferXPos =  (uint16_t *) (uidBaseAddr);
	uint16_t *waferYPos =  (uint16_t *) (uidBaseAddr + 2);
	uint8_t *wafNum =  (uint8_t *) (uidBaseAddr+0x04);
	chipID = (*wafNum << 8) | ((*waferXPos + *waferYPos) ^ *waferYPos);

}

int main(void)
{


    SystemCoreClockUpdate();
    nvic_config();
    InitRCU();
    systick_config();
    InitGPIO();
    GenChipID();
    InitHdata();
    InitI2C_0_GPIOB_6_7(); // PCF85363, SHTC3

    InitEC200();
    InitTaskCAN();
    InitTaskUART1();
    vTaskStartScheduler();
    while (1){

    }
}



void SDCardTest(){
    sd_error_enum sd_error;
    sd_error = sd_io_init();
    if(sd_error == SD_OK){
    }else{
        // printf("\r\n Card init failed!\r\n");
    }
    card_info_get();
    mountFAT();
    AppendText("File2.txt","Hello world\r\n",14);
}

void nvic_config(void)
{
    nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
    nvic_irq_enable(SDIO_IRQn, 0, 0);
}

void InitRCU(){
	rcu_periph_clock_enable(RCU_AF);
	rcu_periph_clock_enable(RCU_FLAG_WWDGTRST);
	rcu_periph_clock_enable(RCU_FLAG_FWDGTRST);

    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_GPIOG);
    rcu_periph_clock_enable(RCU_CRC);
    
}

void InitGPIO(){
    gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP,ENABLE);
    gpio_init(_LEDR_PORT,GPIO_MODE_OUT_PP,GPIO_OSPEED_MAX,_LEDR_PIN);
    gpio_init(_LEDG_PORT,GPIO_MODE_OUT_PP,GPIO_OSPEED_MAX,_LEDG_PIN);
    gpio_init(_LEDB_PORT,GPIO_MODE_OUT_PP,GPIO_OSPEED_MAX,_LEDB_PIN);
    gpio_bit_set(_LEDR_PORT,_LEDR_PIN);
    gpio_bit_set(_LEDG_PORT,_LEDG_PIN);
    gpio_bit_set(_LEDB_PORT,_LEDB_PIN);
}

void SysTick_Handler(void)
{
    delay_decrement();
     /* Clear overflow flag */
    SysTick->CTRL;
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
        /* Call tick handler */
        xPortSysTickHandler();
    }
}


