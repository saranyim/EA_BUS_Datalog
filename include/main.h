#ifndef __MAIN_H__
#define __MAIN_H__

#include "gd32f30x.h"

#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <string.h>
#include <queue.h>

#include "hw_def.h"
#include "pcf85363.h"
#include "prj_data.h"
#include "gd32f30x.h"
#include "systick.h"
#include "SDIO_FAT.h"
#include "hardawareInit.h"
#include "macro.h"
#include "taskcan.h"
#include "TaskUart1ToCan2.h"
#include "hdata.h"
#include "ec200.h"

#define STACK_SIZE 512
extern uint16_t chipID;

#endif