#ifndef __TASKCAN_H__
#define __TASKCAN_H__
#include "main.h"

typedef union{
	struct __attribute__((packed)){
		unsigned SA:8;
		unsigned PS:8;
		unsigned PF:8;
		unsigned DP:1;
        unsigned R:1;
        unsigned P:3;
        unsigned :3;
		
	};
	uint32_t id;
	uint8_t array[4];
}j1939_Header_t;

void InitTaskCAN();
void canAddTxMsg(can_trasnmit_message_struct canMsg);
#endif