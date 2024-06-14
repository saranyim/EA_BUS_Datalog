#include "main.h"
#include "jsonObjLookup.h"


StaticTask_t xTaskUC200;
StackType_t xStackUC200[STACK_SIZE];
TaskHandle_t xHandleUC200;

StaticTask_t xTaskDebug;
StackType_t xStackDebug[128];
TaskHandle_t xHandleDebug;

__IO uint8_t tempTx[64];

FlagStatus fDetectNewLine;
const char simPIN[]   = ""; 

char strLat[16],strLong[16];
char strDate[16],strTime[16];

uint16_t code,sinterval,rinterval,service_state,user_id;
  int jsonResponse[5];
void TaskEC200(void * pvParameters);
void TaskRxDebug(void * pvParameters);

FlagStatus InitGPS();
FlagStatus GetGPSData();

FlagStatus SendHTTP();
void PrepareJsonGroupAll(uint16_t packNo);
uint16_t dataPack;

#define ec200Uart_DATA_ADDRESS    ((uint32_t)&USART_DATA(ec200Uart))

__IO FlagStatus g_transfer_complete = RESET;
char rxbuffer[1024];
char header[500];
char jsonStr[10000];

char * txbuffer;

char productID[9];
char txDebugbuffer[1024];
uint16_t txDebugCnt,txDebugLen;
FlagStatus PowerON();


__IO uint16_t rxcount,txcount,tx_size;
__IO FlagStatus fTxFree,fRxReady;



void  ec200UartISR(void)
{
    if(RESET != usart_interrupt_flag_get(ec200Uart, USART_INT_FLAG_RBNE)){
        /* receive data */
        rxcount %= 1024;
		rxbuffer[rxcount++] = usart_data_receive(ec200Uart);
		// rxbuffer[rxcount] = 0;
         if(rxbuffer[rxcount - 1] == '\n'){
			fRxReady = SET;
			
			// rxbuffer[rxcount++] = 0;
			// rxcount = 0;
        }
		
    }
    if(RESET != usart_interrupt_flag_get(ec200Uart, USART_INT_FLAG_TBE)){
         /* transmit data */
       
        if(txcount >= tx_size){
			usart_interrupt_disable(ec200Uart, USART_INT_TBE);
			fTxFree = SET;
		}
		else{
			 usart_data_transmit(ec200Uart, txbuffer[txcount++]);
		}
    }
}




void InitEC200(){
	InitUSART_0_GPIOA_9_10(115200); // EC200
	gpio_init(_oCT3V8_Port, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,_oCT3V8_Pin);
	gpio_init(_oPWR_Port, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,_oPWR_Pin);
	/*DTR Pin*/
	gpio_init(_DTR_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, _DTR_PIN);
	
    fTxFree = SET;
    xHandleUC200 = xTaskCreateStatic(
        TaskEC200,      /* Function that implements the task. */
        "taskUart",         /* Text name for the task. */
        STACK_SIZE,       /* Number of indexes in the xBlinkyStack array. */
        (void *)0,        /* Parameter passed into the task. */
        tskIDLE_PRIORITY, /* Priority at which the task is created. */
        xStackUC200,           /* Array to use as the task's stack. */
        &xTaskUC200);    /* Variable to hold the task's data structure. */
	
}


FlagStatus SendDataToUart(char * tx){

	while(fTxFree == RESET) // wait prev transmission to complete
		vTaskDelay(20);
	fTxFree = RESET;
	txbuffer = tx;
	tx_size = strlen(txbuffer);
	txcount = 0;

	usart_data_transmit(ec200Uart,txbuffer[txcount++]);
	usart_interrupt_enable(ec200Uart, USART_INT_TBE);
	return SET;
}



FlagStatus SendCheckATCmd(char * tx,char *rx,uint32_t responseTime){
	uint16_t tryCnt = 0;
	uint16_t tryTime;
	tryTime = responseTime / 100;
	rxcount = 0;
	// vTaskDelay(1000);
	rxbuffer[0] = 0;
	SendDataToUart(tx);
	
	while(tryCnt++ < tryTime){
		vTaskDelay(10);
		 
		if(strstr(rxbuffer,rx)){
			// rxbuffer[rxcount++] = 0;
			// vTaskDelay(200);
			return SET;
		}
	}
	// SendDebug("\r\nFail\r\n",0);
	// vTaskDelay(200);
	
	return RESET;
}

void TaskRxDebug(void * pvParameters){
	while(1){
		if(fRxReady == SET){
			fRxReady = RESET;
			// rxbuffer[rxcount] = 0;
			// // SendDebug(rxbuffer,1);
		}
		// // SendDebug("hello\r\n");
		vTaskDelay(10);
	}
}


void GetRTCTime(){
	char * strPars;
	uint16_t len;
	SendCheckATCmd("AT+CCLK?\r", "OK", 1000);
	strPars = strstr(rxbuffer,"+CCLK:");
	if(strPars != NULL){
		strncpy(strDate,strPars + 8,8);
		strncpy(strTime,strPars + 17,8);
		// char* start = strstr(strPars, ",");
		// start += 1;
		// char* end = strstr(start,",");
		// len = (uint16_t)(end - start);
		// strncpy(strDate,start,len);
		// end += 1;
		// char* nextcomma = strstr(end,"+");
		// len = (uint16_t)(nextcomma - end);
		// strncpy(strTime,end,len);
		// return SET;
	}
		
}

void TaskEC200(void * pvParameters){
	
	// while(1){
	// 	strcpy(jsonStr,"Hello world\r\n");
	// 	SendDataToUart(jsonStr);
	// 	vTaskDelay(100);
	// }
	strcpy(strLat,"0");
	strcpy(strLong,"0");
	
	sprintf(productID,"%08X",FMC_PID);
	gpio_bit_write(_oCT3V8_Port,_oCT3V8_Pin,1);
	vTaskDelay(2000);
	gpio_bit_write(_oCT3V8_Port,_oCT3V8_Pin,0);
	vTaskDelay(2000);

	
	while(PowerON() == RESET){
		// power off - power on
		gpio_bit_write(_oCT3V8_Port,_oCT3V8_Pin,1);
		vTaskDelay(2000);
		gpio_bit_write(_oCT3V8_Port,_oCT3V8_Pin,0);
		vTaskDelay(2000);
	}
	SendCheckATCmd("AT+IPR?\r", "OK", 1000); 
	SendCheckATCmd("AT+IPR=921600\r", "OK", 1000); 
 	InitUSART_0_GPIOA_9_10(921600); // EC200
	// while(1){
	// 	GetRTCTime();
	// 	vTaskDelay(500);
	// }
	while(InitGPS() == RESET)
		vTaskDelay(2000);

	while(1){
		GetGPSData();
		// vTaskDelay(1000);
		SendHTTP();

	}
}

FlagStatus PowerON(){

	gpio_bit_write(_oPWR_Port,_oPWR_Pin,1);
	vTaskDelay(3000);
	gpio_bit_write(_oPWR_Port,_oPWR_Pin,0);
	vTaskDelay(5000); 
	if(SendCheckATCmd("AT\r","OK",5000) == RESET){

	
		return RESET;
	}


	SendCheckATCmd("AT+QHTTPCFG=\"contextid\",1\r", "OK", 1000);
	
	SendCheckATCmd("AT+QHTTPCFG=\"requestheader\",0\r", "OK", 1000);
	SendCheckATCmd("AT+QHTTPCFG=\"responseheader\",1\r", "OK", 1000);
	
	SendCheckATCmd("AT+QIACT?\r", "OK", 1000);	
	vTaskDelay(1000);


	SendCheckATCmd("AT+QICSGP=1,1,\"internet\",\"\",\"\",1\r", "", 1000);
	SendCheckATCmd("AT+QIACT=1\r", "OK", 1000);
	if(SendCheckATCmd("AT+QIACT?\r", "OK", 1000)) // get IP address
	{
		return SET;
	}
	else
	{
		return RESET;
	}
	
}




FlagStatus SendHTTP(){
	FlagStatus res;
	uint8_t tempStr[1024];
	SendCheckATCmd("AT+QHTTPCFG=\"contenttype\",1\r", "OK", 1000); // type text/plain
	// for(int i = 0; i < 5;i++)
       
	while(1)
	{
		(gpio_output_bit_get(_LEDG_PORT,_LEDG_PIN))?gpio_bit_reset(_LEDG_PORT,_LEDG_PIN):gpio_bit_set(_LEDG_PORT,_LEDG_PIN);;
		// dataPack ^= 1;
		dataPack = 0; // for debug
		GetRTCTime();
		
		PrepareJsonGroupAll(dataPack);
		sprintf(tempTx,"AT+QHTTPPOST=%u,80,80\r",strlen(jsonStr));
		vTaskDelay(100);
		SendCheckATCmd(tempTx, "CONNECT", 100);
		vTaskDelay(100);
		SendCheckATCmd(jsonStr,"OK",100);
		vTaskDelay(100);
		res = SendCheckATCmd("AT+QHTTPREAD=80\r", "+QHTTPREAD: 0", 100);
		// SendCheckATCmd("AT+QICLOSE=0,1\r", "OK", 1000);
		vTaskDelay(100);
	}


	// SendCheckATCmd("AT+QICLOSE=0,1\r", "OK", 3000);

	return res;
}

FlagStatus InitGPS(){
	return SendCheckATCmd("AT+QGPS=1\r", "OK", 3000);

}

FlagStatus GetGPSData(){
	uint16_t len;
	char * strGPS;
	// +QGPSLOC: 061551.000,1846.7916N,09905.4562E,1.6,287.9,3,000.00,4.1,2.2,190923,07
	// 
	// OK

	// 	Tx : AT+QGPSLOC=0
	// AT+QGPSLOC=0+CMS ERROR: 516

	if(SendCheckATCmd("AT+QGPSLOC=0\r", "OK", 3000) == SET)
	{
		// sprintf(rxbuffer,"AT+QGPSLOC=0\r"
		// "OK\r\n"
		// "+QGPSLOC: 061551.000,1846.7916N,09905.4562E,1.6,287.9,3,000.00,4.1,2.2,190923,07\r\n"
		// "\r\n"
		// "OK\r\n");
		strGPS = strstr(rxbuffer,"+QGPSLOC:");
		if(strGPS != NULL){
			char* start = strstr(strGPS, ",");
			start += 1;
			char* end = strstr(start,",");
			len = (uint16_t)(end - start);
			strncpy(strLat,start,len);
			end += 1;
			char* nextcomma = strstr(end,",");
			len = (uint16_t)(nextcomma - end);
			strncpy(strLong,end,len);
			return SET;
		}
		return RESET;
	}
	else 
		return RESET;


}

void PrepareJsonGroupAll(uint16_t packNo){
	uint16_t idx = 0;
	SendCheckATCmd("AT+QHTTPCFG=\"url\",\"http://amt-datalog.energyabsolute.com/g6\"\r", "OK", 1000); 
	strcpy(jsonStr,"[{");
	sprintf(jsonStr + strlen(jsonStr),"\"DATALOG ID\":\"L%04u\",",chipID);
	sprintf(jsonStr + strlen(jsonStr),"\"BATTERY ID\":\"BAT%04u\",",packNo + 1);
	sprintf(jsonStr + strlen(jsonStr),"\"Date\":\"%s\",",strDate); // date
	sprintf(jsonStr + strlen(jsonStr),"\"TS\":\"%s\",",strTime); // time


	for(idx = 0; idx < 489; idx++) // vcell for 24 pack
	{

		sprintf(jsonStr + strlen(jsonStr),"\"%s\":\"%04u\",",objectNames2[idx],logData[packNo][idx]);
	
	}
	sprintf(jsonStr + strlen(jsonStr),"\"%s\":\"%04u\"",objectNames2[idx],logData[packNo][489]);
	strcat(jsonStr,"}]");
	txDebugLen = strlen(jsonStr);
}