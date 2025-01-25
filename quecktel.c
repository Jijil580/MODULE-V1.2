#include "quecktel.h"

 const char *at_commands[] = {
    "ATI\r\n",                                         //:0
    
    "ATE0\r\n",                                        //:1
    
    "AT+QSCLKEX=0\r\n",                                //:2
    
    "AT+CEDRXS=0,4\r\n",                               //:3
    
    "AT+CEDRXS?\r",                                    //:4
    
    "AT+QCFG=\"NWSCANMODE\",0\r",                      //:5
    
    "AT+QICSGP=1,3,\"tpplus.smwbiot\",\"\",\"\"\r",    //:6
    
    "AT+CPIN?\r",                                      //:7
    
    "AT+EGMR=0,7\r",                                   //:8
    
    "AT+CCID\r",                                       //:9
    
    "AT+CREG?\r",                                      //:10
    
    "AT+CREG=0\r",                                     //:11
    
    "AT+CGREG=0\r",                                    //:12
    
    "AT+COPS?\r",                                      //:13
    
    "AT+CSQ\r",                                        //:14
    
    "AT+QICFG=\"passiveclosed\",1\r",                  //:15
    
    "AT+QICFG=\"tcp/keepalive\"\r",                    //:16
    
    "AT+QIACT=1\r",                                    //:17
    
    "AT+QIACT?\r",                                     //:18
    
    "AT+QLTS=2\r",                                     //:19
    
    "AT+QLTS=2\r",                                     //:20
    
    "AT+QIOPEN=1,1,\"TCP LISTENER\",\"::1\",0,4059,1,1\r"//:21
  
};

const char *COMMON_RESPONSE[] =
{
   	"\r\nQuectel\r\nEC200U\r\nRevision: EC200UCNAAR03A09M08\r\n\r\nOK\r\n",
    	"\r\nOK\r\n",
    	"\r\nERROR\r\n"
};


const char *EDRX_RESPONSE[]=
{
	"\r\n+CEDRXS: 4,\"0000\"\r\n\r\nOK\r\n",
	"\r\nERROR\r\n"
};

const char *SIM_QUERRY_RESPONSE[]=
{
	"\r\n+CPIN: READY\r\n\r\nOK\r\n",
	
	"\r\n+CPIN: SIM PIN\r\n\r\nOK\r\n",
	
	"\r\n+CPIN: SIM PUK\r\n\r\nOK\r\n",
	
	"\r\n+CPIN: SIM PIN2\r\n\r\nOK\r\n",
	
	"\r\n+CPIN: SIM PUK2\r\n\r\nOK\r\n",
	"\r\nERROR\r\n"
	
};


const char *NETWORK_OPERATOR_STSTUS[]=
{
	"\r\n+COPS: 0,0,\"IND airtel\",7\r\n\r\nOK\r\n",

	
};
	
	

const char *NETWORK_REGI_STATUS[]=
{
	"\r\n+CREG: 0,0\r\n\r\nOK\r\n",////- <CR><LF>+CREG: 0,1<CR><LF><CR><LF>OK<CR><LF>

	"\r\n+CREG: 0,1\r\n\r\nOK\r\n",
	"\r\n+CREG: 0,2\r\n\r\nOK\r\n",
	"\r\n+CREG: 0,3\r\n\r\nOK\r\n",
	"\r\n+CREG: 0,4\r\n\r\nOK\r\n",
	"\r\n+CREG: 0,5\r\n\r\nOK\r\n",
	
	"\r\n+CREG: 1,0\r\n\r\nOK\r\n",
	"\r\n+CREG: 1,1\r\n\r\nOK\r\n",
	"\r\n+CREG: 1,2\r\n\r\nOK\r\n",
	"\r\n+CREG: 1,3\r\n\r\nOK\r\n",
	"\r\n+CREG: 1,4\r\n\r\nOK\r\n",
	"\r\n+CREG: 1,5\r\n\r\nOK\r\n",
	
	"\r\n+CREG: 2,0\r\n\r\nOK\r\n",
	"\r\n+CREG: 2,1\r\n\r\nOK\r\n",
	"\r\n+CREG: 2,2\r\n\r\nOK\r\n",
	"\r\n+CREG: 2,3\r\n\r\nOK\r\n",
	"\r\n+CREG: 2,4\r\n\r\nOK\r\n",
	"\r\n+CREG: 2,5\r\n\r\nOK\r\n"  

	
};
const char *OPERATOR_STATUS[]=
{
	"\r\n+COPS: 0,0,\"IND airtel\",0\r\n\r\nOK\r\n",
	"\r\n+COPS: 0,0,\"IND airtel\",7\r\n\r\nOK\r\n",
	"\r\n+COPS: 0,1,\"IND airtel\",0\r\n\r\nOK\r\n",
	"\r\n+COPS: 0,1,\"IND airtel\",7\r\n\r\nOK\r\n",
	"\r\n+COPS: 0,2,\"IND airtel\",0\r\n\r\nOK\r\n",
	"\r\n+COPS: 0,2,\"IND airtel\",7\r\n\r\nOK\r\n",
	
	"\r\n+COPS: 1,0,\"IND airtel\",0\r\n\r\nOK\r\n",
	"\r\n+COPS: 1,0,\"IND airtel\",7\r\n\r\nOK\r\n",
	"\r\n+COPS: 1,1,\"IND airtel\",0\r\n\r\nOK\r\n",
	"\r\n+COPS: 1,1,\"IND airtel\",7\r\n\r\nOK\r\n",
	"\r\n+COPS: 1,2,\"IND airtel\",0\r\n\r\nOK\r\n",
	"\r\n+COPS: 1,2,\"IND airtel\",7\r\n\r\nOK\r\n",
	
	"\r\n+COPS: 2,0,\"IND airtel\",0\r\n\r\nOK\r\n",
	"\r\n+COPS: 2,0,\"IND airtel\",7\r\n\r\nOK\r\n",
	"\r\n+COPS: 2,1,\"IND airtel\",0\r\n\r\nOK\r\n",
	"\r\n+COPS: 2,1,\"IND airtel\",7\r\n\r\nOK\r\n",
	"\r\n+COPS: 2,2,\"IND airtel\",0\r\n\r\nOK\r\n",
	"\r\n+COPS: 2,2,\"IND airtel\",7\r\n\r\nOK\r\n",
	
	"\r\n+COPS: 3,0,\"IND airtel\",0\r\n\r\nOK\r\n",
	"\r\n+COPS: 3,0,\"IND airtel\",7\r\n\r\nOK\r\n",
	"\r\n+COPS: 3,1,\"IND airtel\",0\r\n\r\nOK\r\n",
	"\r\n+COPS: 3,1,\"IND airtel\",7\r\n\r\nOK\r\n",
	"\r\n+COPS: 3,2,\"IND airtel\",0\r\n\r\nOK\r\n",
	"\r\n+COPS: 3,2,\"IND airtel\",7\r\n\r\nOK\r\n",
	
        "\r\n+COPS: 3,0,\"IND airtel\",0\r\n\r\nOK\r\n",
	"\r\n+COPS: 3,0,\"IND airtel\",7\r\n\r\nOK\r\n",
	"\r\n+COPS: 3,1,\"IND airtel\",0\r\n\r\nOK\r\n",
	"\r\n+COPS: 3,1,\"IND airtel\",7\r\n\r\nOK\r\n",
	"\r\n+COPS: 3,2,\"IND airtel\",0\r\n\r\nOK\r\n",
	"\r\n+COPS: 3,2,\"IND airtel\",7\r\n\r\nOK\r\n"

	
};

const char *TCP_ALIVE[]=
{
	"\r\n+QICFG: \"tcp/keepalive\",0\r\n\r\nOK\r\n"

	
};

