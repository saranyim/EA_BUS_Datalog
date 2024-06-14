#ifndef __PRJ_DATA_H__
#define __PRJ_DATA_H__
#include "main.h"

typedef struct {
        uint16_t cellV[14];
        uint16_t PackV;
        uint16_t minVolt;
        uint16_t maxVolt;
        uint16_t minVIdx;
        uint16_t maxVIdx;
        uint16_t minTemp;
        uint16_t maxTemp;
        uint16_t minTempIdx;
        uint16_t maxTempIdx;
        uint16_t averageVolt;
        uint16_t balanceV;

}bmu_data_t;


typedef struct{
    Time_t time; // 7 half word
    uint16_t volt;
    uint16_t current;
    uint16_t minVolt;
    uint16_t maxVolt;
    uint16_t minVID;
    uint16_t maxVID;
    uint16_t minT;
    uint16_t maxT;
    uint16_t minTID;
    uint16_t maxTID;
    uint16_t SoC;
    uint16_t SoH;
    uint16_t udc;
    uint16_t humi;
    uint16_t accX;
    uint16_t accY;
    uint16_t accZ;
    uint16_t RelayState;
    uint16_t VCUReq;
    uint16_t EvBmsStatus;
    uint16_t SelfStatus;
    uint16_t ChrStepStatus;
    uint16_t DsgStepStatus;
    uint8_t fault[8];
    bmu_data_t bmuData[24]; 

}log_data_t;


uint16_t logData[2][490];
#endif