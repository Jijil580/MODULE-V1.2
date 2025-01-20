#include "quecktel.h"

 const char *at_commands[] = {
    "ATI\r\n",
    
    "ATE0\r\n",
    
    "AT+QSCLKEX=0\r\n",
    
    "AT+CEDRXS=0,4\r\n",
    
    "AT+CEDRXS?\r",
    
    "AT+QCFG=\"NWSCANMODE\",0\r",
    
    "AT+QICSGP=1,3,\"tpplus.smwbiot\",\"\",\"\"\r",
    
    "AT+CPIN?\r",
    
    "AT+EGMR=0,7\r",
    
    "AT+CCID\r",
    
    "AT+CREG?\r",
    
    "AT+CREG=0\r",
    
    "AT+CGREG=0\r",
    
    "AT+COPS?\r",
    
    "AT+CSQ\r",
    
    "AT+QICFG=\"passiveclosed\",1\r",
    
    "AT+QICFG=\"tcp/keepalive\"\r",
    
    "AT+QIACT=1\r",
    
    "AT+QIACT?\r",
    
    "AT+QLTS=2\r",
    
    "AT+QLTS=2\r",
    
    "AT+QIOPEN=1,1,\"TCP LISTENER\",\"::1\",0,4059,1,1\r"
  
};

const char *COMMON_RESPONSE[] = {
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
const char *NETWORK_REG_STATUS[]=
{
	"\r\n+CREG: 0,0\r\n\r\nOK\r\n",
	
	"\r\n+CREG: 0,1\r\n\r\nOK\r\n",
	
	"\r\n+CREG: 0,2\r\n\r\nOK\r\n",
	
	"\r\n+CREG: 0,3\r\n\r\nOK\r\n",
	
	"\r\n+CREG: 0,4\r\n\r\nOK\r\n",
	
	"\r\n+CREG: 0,5\r\n\r\nOK\r\n"	
};

const char *NETWORK_OPERATOR_STSTUS[]=
{
	"\r\n+COPS: 0,0,\"IND airtel\",7\r\n\r\nOK\r\n",

	
};
const char *SIGNAL_QUALITY[]=
{
	"\r\n+CSQ: 22,99\\r\n\r\nOK\r\n"
	
	
};
//const char *PDP_CONTEXT_STATUS[]=
//{
//	"\r\n+QIACT: 1,1,2,\"2401:4900:9831:FD7B::2\"\r\n\r\nOK\r\n"

	
	
	
////};
//const char *NETWORK_REG_STATUS[]=
//{
//	"\r\n+CREG: 0,0\r\n\r\nOK\r\n",
//	"\r\n+CREG: 0,1\r\n\r\nOK\r\n",
//	"\r\n+CREG: 0,2\r\n\r\nOK\r\n",
//	"\r\n+CREG: 0,3\r\n\r\nOK\r\n",
//	"\r\n+CREG: 0,4\r\n\r\nOK\r\n",
//	"\r\n+CREG: 0,5\r\n\r\nOK\r\n",
	
//	"\r\n+CREG: 1,0\r\n\r\nOK\r\n",
//	"\r\n+CREG: 1,1\r\n\r\nOK\r\n",
//	"\r\n+CREG: 1,2\r\n\r\nOK\r\n",
//	"\r\n+CREG: 1,3\r\n\r\nOK\r\n",
//	"\r\n+CREG: 1,4\r\n\r\nOK\r\n",
//	"\r\n+CREG: 1,5\r\n\r\nOK\r\n",
	
//	"\r\n+CREG: 2,0\r\n\r\nOK\r\n",
//	"\r\n+CREG: 2,1\r\n\r\nOK\r\n",
//	"\r\n+CREG: 2,2\r\n\r\nOK\r\n",
//	"\r\n+CREG: 2,3\r\n\r\nOK\r\n",
//	"\r\n+CREG: 2,4\r\n\r\nOK\r\n",
//	"\r\n+CREG: 2,5\r\n\r\nOK\r\n"

	
//}

