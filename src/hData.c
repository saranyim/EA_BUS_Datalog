#include "main.h"

j1939_Header_t j1939Header;

SemaphoreHandle_t mutHData;
void Set4Cell(uint16_t pack,uint16_t idx, can_receive_message_struct bcuRxMessage);
void Set2Cell(uint16_t pack,uint16_t idx, can_receive_message_struct bcuRxMessage);

void InitHdata(){
    mutHData = xSemaphoreCreateMutex();
    xSemaphoreGive(mutHData);
}

void HData(BaseType_t xPackNo, can_receive_message_struct bcuRxMessage)
{
    uint16_t idx;
    if (xSemaphoreTake(mutHData,1 ) == pdTRUE){
        switch(bcuRxMessage.rx_efid){
        case 0x18F15AF3:
            logData[xPackNo][0] = bcuRxMessage.rx_data[0] & 0xF;
            logData[xPackNo][1] = (bcuRxMessage.rx_data[0] >> 4) & 0x3;
            logData[xPackNo][2] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 1);
            logData[xPackNo][3] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 3);
            logData[xPackNo][4] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 5);
            break;
        case 0x180A0100:
            logData[0][5] = bcuRxMessage.rx_data[1];
            logData[1][5] = bcuRxMessage.rx_data[2];
            break;
        case 0x18050001:
            logData[0][6] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data);
            logData[1][6] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);
            logData[0][7] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[1][7] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);
            break;  
        case 0x18060001:
            logData[0][8] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data);
            logData[0][9] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);
            logData[0][10] = bcuRxMessage.rx_data[4];
            logData[0][11] = bcuRxMessage.rx_data[5];
            logData[0][12] = bcuRxMessage.rx_data[6];
            logData[0][13] = bcuRxMessage.rx_data[7];
            break;
        case 0x18070001:
            logData[1][8] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data);
            logData[1][9] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);
            logData[1][10] = bcuRxMessage.rx_data[4];
            logData[1][11] = bcuRxMessage.rx_data[5];
            logData[1][12] = bcuRxMessage.rx_data[6];
            logData[1][13] = bcuRxMessage.rx_data[7];
            break;
        case 0x18080001:
            logData[0][14] = bcuRxMessage.rx_data[0];
            logData[0][15] = bcuRxMessage.rx_data[1];
            logData[0][16] = bcuRxMessage.rx_data[2];
            logData[0][17] = bcuRxMessage.rx_data[3];
            logData[0][18] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            break;
        case 0x18090001:
            logData[1][14] = bcuRxMessage.rx_data[0];
            logData[1][15] = bcuRxMessage.rx_data[1];
            logData[1][16] = bcuRxMessage.rx_data[2];
            logData[1][17] = bcuRxMessage.rx_data[3];
            logData[1][18] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            break;
        case 0x180A0001:
            logData[0][19] = bcuRxMessage.rx_data[0];
            logData[0][20] = bcuRxMessage.rx_data[1];
            logData[0][21] = bcuRxMessage.rx_data[2];
            logData[0][22] = bcuRxMessage.rx_data[3];
            logData[0][23] = bcuRxMessage.rx_data[4];
            logData[0][24] = bcuRxMessage.rx_data[5];
            break;
        case 0x180B0001:
            logData[1][19] = bcuRxMessage.rx_data[0];
            logData[1][20] = bcuRxMessage.rx_data[1];
            logData[1][21] = bcuRxMessage.rx_data[2];
            logData[1][22] = bcuRxMessage.rx_data[3];
            logData[1][23] = bcuRxMessage.rx_data[4];
            logData[1][24] = bcuRxMessage.rx_data[5];
            break;
        case 0x180C0001:
            logData[0][25] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data);
            logData[0][26] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);
            logData[0][27] = bcuRxMessage.rx_data[5];
            logData[1][27] = bcuRxMessage.rx_data[6];
            logData[0][28] = bcuRxMessage.rx_data[7] & 0x01;
            logData[0][29] = bcuRxMessage.rx_data[7] & 0x02;
            logData[0][30] = bcuRxMessage.rx_data[7] & 0x04;
            logData[0][31] = bcuRxMessage.rx_data[7] & 0x08;
            logData[0][32] = bcuRxMessage.rx_data[7] & 0x10;
            logData[0][33] = bcuRxMessage.rx_data[7] & 0x20;
            logData[0][34] = bcuRxMessage.rx_data[7] & 0x40;
            logData[0][35] = bcuRxMessage.rx_data[7] & 0x80;
            break;   
        case 0x180D0001:
            logData[0][36] = bcuRxMessage.rx_data[1] & 0x01;
            logData[0][37] = bcuRxMessage.rx_data[1] & 0x02;
            logData[0][38] = bcuRxMessage.rx_data[1] & 0x04;
            logData[0][30] = bcuRxMessage.rx_data[1] & 0x08;
            logData[0][40] = bcuRxMessage.rx_data[1] & 0x10;
            logData[0][41] = bcuRxMessage.rx_data[1] & 0x20;
            logData[0][42] = bcuRxMessage.rx_data[1] & 0x40;
            logData[0][43] = bcuRxMessage.rx_data[1] & 0x80;

            logData[0][44] = bcuRxMessage.rx_data[2] & 0x01;
            logData[0][45] = bcuRxMessage.rx_data[2] & 0x02;
            logData[0][46] = bcuRxMessage.rx_data[2] & 0x08;

            logData[0][47] = bcuRxMessage.rx_data[3] & 0x01;
            logData[0][48] = bcuRxMessage.rx_data[3] & 0x02;
            logData[0][49] = bcuRxMessage.rx_data[3] & 0x04;
            logData[0][50] = bcuRxMessage.rx_data[3] & 0x08;
            logData[0][51] = bcuRxMessage.rx_data[3] & 0x10;
            logData[0][52] = bcuRxMessage.rx_data[3] & 0x20;
            logData[0][53] = bcuRxMessage.rx_data[3] & 0x40;
            logData[0][54] = bcuRxMessage.rx_data[3] & 0x80;
            
            logData[0][55] = bcuRxMessage.rx_data[4] & 0x01;
            logData[0][56] = bcuRxMessage.rx_data[4] & 0x02;
            logData[0][57] = bcuRxMessage.rx_data[4] & 0x20;
            break; 
        case 0x180E0001:
            logData[1][36] = bcuRxMessage.rx_data[1] & 0x01;
            logData[1][37] = bcuRxMessage.rx_data[1] & 0x02;
            logData[1][38] = bcuRxMessage.rx_data[1] & 0x04;
            logData[1][30] = bcuRxMessage.rx_data[1] & 0x08;
            logData[1][40] = bcuRxMessage.rx_data[1] & 0x10;
            logData[1][41] = bcuRxMessage.rx_data[1] & 0x20;
            logData[1][42] = bcuRxMessage.rx_data[1] & 0x40;
            logData[1][43] = bcuRxMessage.rx_data[1] & 0x80;

            logData[1][44] = bcuRxMessage.rx_data[2] & 0x01;
            logData[1][45] = bcuRxMessage.rx_data[2] & 0x02;
            logData[1][46] = bcuRxMessage.rx_data[2] & 0x08;

            logData[1][47] = bcuRxMessage.rx_data[3] & 0x01;
            logData[1][48] = bcuRxMessage.rx_data[3] & 0x02;
            logData[1][49] = bcuRxMessage.rx_data[3] & 0x04;
            logData[1][50] = bcuRxMessage.rx_data[3] & 0x08;
            logData[1][51] = bcuRxMessage.rx_data[3] & 0x10;
            logData[1][52] = bcuRxMessage.rx_data[3] & 0x20;
            logData[1][53] = bcuRxMessage.rx_data[3] & 0x40;
            logData[1][54] = bcuRxMessage.rx_data[3] & 0x80;
            
            logData[1][55] = bcuRxMessage.rx_data[4] & 0x01;
            logData[1][56] = bcuRxMessage.rx_data[4] & 0x02;
            logData[1][57] = bcuRxMessage.rx_data[4] & 0x20;
            break; 
        case  0x18030101:
            Set4Cell(xPackNo,58,bcuRxMessage);
            break;
        case  0x18040101:
            Set4Cell(xPackNo,62,bcuRxMessage);
            break;
        case  0x18050101:
            Set4Cell(xPackNo,66,bcuRxMessage);
            break;
        case  0x18060101:
            Set2Cell(xPackNo,70,bcuRxMessage);
            logData[xPackNo][394] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][395] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x18030102:
            Set4Cell(xPackNo,72,bcuRxMessage);
            break;
        case  0x18040102:
            Set4Cell(xPackNo,76,bcuRxMessage);
            break;
        case  0x18050102:
            Set4Cell(xPackNo,80,bcuRxMessage);
            break;
        case  0x18060102:
            Set2Cell(xPackNo,84,bcuRxMessage);
            logData[xPackNo][396] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][397] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);                
            break;
        case  0x18030103:
            Set4Cell(xPackNo,86,bcuRxMessage);
            break;
        case  0x18040103:
            Set4Cell(xPackNo,90,bcuRxMessage);
            break;
        case  0x18050103:
            Set4Cell(xPackNo,94,bcuRxMessage);
            break;
        case  0x18060103:
            Set2Cell(xPackNo,98,bcuRxMessage);
            logData[xPackNo][398] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][399] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x18030104:
            Set4Cell(xPackNo,100,bcuRxMessage);
            break;
        case  0x18040104:
            Set4Cell(xPackNo,104,bcuRxMessage);
            break;
        case  0x18050104:
            Set4Cell(xPackNo,108,bcuRxMessage);
            break;
        case  0x18060104:
            Set2Cell(xPackNo,112,bcuRxMessage);
            logData[xPackNo][400] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][401] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x18030105:
            Set4Cell(xPackNo,114,bcuRxMessage);
            break;
        case  0x18040105:
            Set4Cell(xPackNo,118,bcuRxMessage);
            break;
        case  0x18050105:
            Set4Cell(xPackNo,122,bcuRxMessage);
            break;
        case  0x18060105:
            Set2Cell(xPackNo,126,bcuRxMessage);
            logData[xPackNo][402] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][403] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x18030106:
            Set4Cell(xPackNo,128,bcuRxMessage);
            break;
        case  0x18040106:
            Set4Cell(xPackNo,1322,bcuRxMessage);
            break;
        case  0x18050106:
            Set4Cell(xPackNo,136,bcuRxMessage);
            break;
        case  0x18060106:
            Set2Cell(xPackNo,140,bcuRxMessage);
            logData[xPackNo][404] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][405] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x18030107:
            Set4Cell(xPackNo,142,bcuRxMessage);
            break;
        case  0x18040107:
            Set4Cell(xPackNo,146,bcuRxMessage);
            break;
        case  0x18050107:
            Set4Cell(xPackNo,150,bcuRxMessage);
            break;
        case  0x18060107:
            Set2Cell(xPackNo,154,bcuRxMessage);
            logData[xPackNo][406] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][407] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x18030108:
            Set4Cell(xPackNo,156,bcuRxMessage);
            break;
        case  0x18040108:
            Set4Cell(xPackNo,160,bcuRxMessage);
            break;
        case  0x18050108:
            Set4Cell(xPackNo,164,bcuRxMessage);
            break;
        case  0x18060108:
            Set2Cell(xPackNo,168,bcuRxMessage);
            logData[xPackNo][408] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][409] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x18030109:
            Set4Cell(xPackNo,170,bcuRxMessage);
            break;
        case  0x18040109:
            Set4Cell(xPackNo,174,bcuRxMessage);
            break;
        case  0x18050109:
            Set4Cell(xPackNo,178,bcuRxMessage);
            break;
        case  0x18060109:
            Set2Cell(xPackNo,182,bcuRxMessage);
            logData[xPackNo][410] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][411] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x1803010A:
            Set4Cell(xPackNo,184,bcuRxMessage);
            break;
        case  0x1804010A:
            Set4Cell(xPackNo,188,bcuRxMessage);
            break;
        case  0x1805010A:
            Set4Cell(xPackNo,192,bcuRxMessage);
            break;
        case  0x1806010A:
            Set2Cell(xPackNo,196,bcuRxMessage);
            logData[xPackNo][412] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][413] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x1803010B:
            Set4Cell(xPackNo,198,bcuRxMessage);
            break;
        case  0x1804010B:
            Set4Cell(xPackNo,202,bcuRxMessage);
            break;
        case  0x1805010B:
            Set4Cell(xPackNo,206,bcuRxMessage);
            break;
        case  0x1806010B:
            Set2Cell(xPackNo,210,bcuRxMessage);
            logData[xPackNo][414] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][415] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x1803010C:
            Set4Cell(xPackNo,212,bcuRxMessage);
            break;
        case  0x1804010C:
            Set4Cell(xPackNo,216,bcuRxMessage);
            break;
        case  0x1805010C:
            Set4Cell(xPackNo,220,bcuRxMessage);
            break;
        case  0x1806010C:
            Set2Cell(xPackNo,224,bcuRxMessage);
            logData[xPackNo][416] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][417] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x1803010D:
            Set4Cell(xPackNo,226,bcuRxMessage);
            break;
        case  0x1804010D:
            Set4Cell(xPackNo,230,bcuRxMessage);
            break;
        case  0x1805010D:
            Set4Cell(xPackNo,234,bcuRxMessage);
            break;
        case  0x1806010D:
            Set2Cell(xPackNo,238,bcuRxMessage);
            logData[xPackNo][418] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][419] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x1803010E:
            Set4Cell(xPackNo,240,bcuRxMessage);
            break;
        case  0x1804010E:
            Set4Cell(xPackNo,244,bcuRxMessage);
            break;
        case  0x1805010E:
            Set4Cell(xPackNo,248,bcuRxMessage);
            break;
        case  0x1806010E:
            Set2Cell(xPackNo,252,bcuRxMessage);
            logData[xPackNo][420] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][421] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x1803010F:
            Set4Cell(xPackNo,254,bcuRxMessage);
            break;
        case  0x1804010F:
            Set4Cell(xPackNo,258,bcuRxMessage);
            break;
        case  0x1805010F:
            Set4Cell(xPackNo,262,bcuRxMessage);
            break;
        case  0x1806010F:
            Set2Cell(xPackNo,266,bcuRxMessage);
            logData[xPackNo][422] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][423] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x18030110:
            Set4Cell(xPackNo,268,bcuRxMessage);
            break;
        case  0x18040110:
            Set4Cell(xPackNo,272,bcuRxMessage);
            break;
        case  0x18050110:
            Set4Cell(xPackNo,276,bcuRxMessage);
            break;
        case  0x18060110:
            Set2Cell(xPackNo,280,bcuRxMessage);
            logData[xPackNo][424] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][425] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            
            break;
        case  0x18030111:
            Set4Cell(xPackNo,282,bcuRxMessage);
            break;
        case  0x18040111:
            Set4Cell(xPackNo,286,bcuRxMessage);
            break;
        case  0x18050111:
            Set4Cell(xPackNo,290,bcuRxMessage);
            break;
        case  0x18060111:
            Set2Cell(xPackNo,294,bcuRxMessage);
            logData[xPackNo][426] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][427] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
             break;
        case  0x18030112:
            Set4Cell(xPackNo,296,bcuRxMessage);
            break;
        case  0x18040112:
            Set4Cell(xPackNo,300,bcuRxMessage);
            break;
        case  0x18050112:
            Set4Cell(xPackNo,304,bcuRxMessage);
            break;
        case  0x18060112:
            Set2Cell(xPackNo,308,bcuRxMessage);
            logData[xPackNo][428] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][429] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x18030113:
            Set4Cell(xPackNo,310,bcuRxMessage);
            break;
        case  0x18040113:
            Set4Cell(xPackNo,314,bcuRxMessage);
            break;
        case  0x18050113:
            Set4Cell(xPackNo,318,bcuRxMessage);
            break;
        case  0x18060113:
            Set2Cell(xPackNo,322,bcuRxMessage);
            logData[xPackNo][430] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][431] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x18030114:
            Set4Cell(xPackNo,324,bcuRxMessage);
            break;
        case  0x18040114:
            Set4Cell(xPackNo,328,bcuRxMessage);
            break;
        case  0x18050114:
            Set4Cell(xPackNo,332,bcuRxMessage);
            break;
        case  0x18060114:
            Set2Cell(xPackNo,336,bcuRxMessage);
            logData[xPackNo][432] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][433] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x18030115:
            Set4Cell(xPackNo,338,bcuRxMessage);
            break;
        case  0x18040115:
            Set4Cell(xPackNo,342,bcuRxMessage);
            break;
        case  0x18050115:
            Set4Cell(xPackNo,346,bcuRxMessage);
            break;
        case  0x18060115:
            Set2Cell(xPackNo,350,bcuRxMessage);
           logData[xPackNo][434] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][435] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
             break;
        case  0x18030116:
            Set4Cell(xPackNo,352,bcuRxMessage);
            break;
        case  0x18040116:
            Set4Cell(xPackNo,356,bcuRxMessage);
            break;
        case  0x18050116:
            Set4Cell(xPackNo,360,bcuRxMessage);
            break;
        case  0x18060116:
            Set2Cell(xPackNo,364,bcuRxMessage);
            logData[xPackNo][436] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][437] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x18030117:
            Set4Cell(xPackNo,366,bcuRxMessage);
            break;
        case  0x18040117:
            Set4Cell(xPackNo,370,bcuRxMessage);
            break;
        case  0x18050117:
            Set4Cell(xPackNo,374,bcuRxMessage);
            break;
        case  0x18060117:
            Set2Cell(xPackNo,378,bcuRxMessage);
            logData[xPackNo][438] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][439] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case  0x18030118:
            Set4Cell(xPackNo,380,bcuRxMessage);
            break;
        case  0x18040118:
            Set4Cell(xPackNo,384,bcuRxMessage);
            break;
        case  0x18050118:
            Set4Cell(xPackNo,388,bcuRxMessage);
            break;
        case  0x18060118:
            Set2Cell(xPackNo,392,bcuRxMessage);
            logData[xPackNo][440] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
            logData[xPackNo][441] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080101:
            logData[xPackNo][442] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080102:
            logData[xPackNo][443] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080103:
            logData[xPackNo][444] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080104:
            logData[xPackNo][445] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080105:
            logData[xPackNo][446] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080106:
            logData[xPackNo][447] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080107:
            logData[xPackNo][448] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080108:
            logData[xPackNo][449] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080109:
            logData[xPackNo][450] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x1808010A:
            logData[xPackNo][451] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x1808010B:
            logData[xPackNo][452] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x1808010C:
            logData[xPackNo][453] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x1808010D:
            logData[xPackNo][454] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x1808010E:
            logData[xPackNo][455] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x1808010F:
            logData[xPackNo][456] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080110:
            logData[xPackNo][457] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080111:
            logData[xPackNo][458] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080112:
            logData[xPackNo][459] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080113:
            logData[xPackNo][460] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080114:
            logData[xPackNo][461] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080115:
            logData[xPackNo][462] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080116:
            logData[xPackNo][463] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080117:
            logData[xPackNo][464] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18080118:
            logData[xPackNo][465] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);    
            break;
        case 0x18010101:
            logData[xPackNo][466] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010102:
            logData[xPackNo][467] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010103:
            logData[xPackNo][468] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010104:
            logData[xPackNo][469] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010105:
            logData[xPackNo][470] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010106:
            logData[xPackNo][471] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010107:
            logData[xPackNo][472] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010108:
            logData[xPackNo][473] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010109:
            logData[xPackNo][474] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x1801010A:
            logData[xPackNo][475] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x1801010B:
            logData[xPackNo][476] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x1801010C:
            logData[xPackNo][477] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x1801010D:
            logData[xPackNo][478] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x1801010E:
            logData[xPackNo][479] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x1801010F:
            logData[xPackNo][480] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010110:
            logData[xPackNo][481] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010111:
            logData[xPackNo][482] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010112:
            logData[xPackNo][483] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010113:
            logData[xPackNo][484] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010114:
            logData[xPackNo][485] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010115:
            logData[xPackNo][486] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010116:
            logData[xPackNo][487] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010117:
            logData[xPackNo][488] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        case 0x18010118:
            logData[xPackNo][489] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);    
            break;
        }
      
        xSemaphoreGive(mutHData);        
    }
}

void Set4Cell(uint16_t pack,uint16_t idx, can_receive_message_struct bcuRxMessage){
    logData[pack][idx++] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data);
    logData[pack][idx++] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);
    logData[pack][idx++] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 4);
    logData[pack][idx++] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 6);
}

void Set2Cell(uint16_t pack,uint16_t idx, can_receive_message_struct bcuRxMessage){
    logData[pack][idx++] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data);
    logData[pack][idx++] = BYTES_TO_UINT16_BE(bcuRxMessage.rx_data + 2);
  
}