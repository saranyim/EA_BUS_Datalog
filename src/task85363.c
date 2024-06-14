#include "main.h"

StaticTask_t x85363Buffer;
StackType_t x85363Stack[128];
TaskHandle_t h85363;

void Task85363();

void InitTask85363(){
    h85363 = xTaskCreateStatic(
        Task85363,      /* Function that implements the task. */
        "TaskI2CEEP",         /* Text name for the task. */
        128,       /* Number of indexes in the xBlinkyStack array. */
        (void *)0,        /* Parameter passed into the task. */
        tskIDLE_PRIORITY, /* Priority at which the task is created. */
        x85363Stack,           /* Array to use as the task's stack. */
        &x85363Buffer);    /* Variable to hold the task's data structure. */
}

void Task85363(){
    InitPCF85363();
    while(1){
        getTime();
        vTaskDelay(500);
    }
}