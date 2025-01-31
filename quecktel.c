#include "quecktel.h"
#include "simstatus.h"
#include "networkstatus.h"
#include "operatorstatus.h"


uint8_t AT_COMMAND_COUNT=0;
uint8_t COMPARE_MATCH1=0;

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
const char *THIRTY_SECONDS_CHECKS[]=
{  
	"AT+QISTATE\r",
	"AT+CSQ\r"
};
const char *CHECKS_RESPONSE[]=
{
	"TCP",
	"TCP LISTENER",
	NULL
	
};


const char *COMMON_RESPONSE[] =
{
   	
    	"\r\nOK\r\n",
    	"\r\nERROR\r\n"
};



const char *EDRX_RESPONSE[]=
{
	"\r\n+CEDRXS: 4,\"0000\"\r\n\r\nOK\r\n",
	"\r\nERROR\r\n"
};


const char *TCP_ALIVE[]=
{
	"\r\n+QICFG: \"tcp/keepalive\",0\r\n\r\nOK\r\n"

	
};

/*-------------------------------------------------------------------------------------------------------------------/
* Function Name: CHECK_MODULE_RESPONSE
* Description  : This function checks the response is matching as expected from the module
* Arguments    : response
* Return Value :return 0 or 1
--------------------------------------------------------------------------------------------------------------------*/
uint8_t CHECK_MODULE_RESPONSE(uint8_t *RESPONSE)
{
	switch (AT_COMMAND_COUNT)
	{
		case 0:
		{
			COMPARE_MATCH1=CHECK_OK_RESPONSE(RESPONSE);

			 break;
		}
		case 1:
		{
			COMPARE_MATCH1=Check_Common_Response(RESPONSE);

			 break;
		}
		case 2:
		{
			
			COMPARE_MATCH1=Check_Common_Response(RESPONSE);

			 break;
		}
		case 3:
		{
			
			COMPARE_MATCH1=Check_Common_Response(RESPONSE);

			 break;
		}
	        case 4:
		{
			COMPARE_MATCH1=Check_EDRX_Status(RESPONSE);
			
			break;
		}
		case 5:
		{
			COMPARE_MATCH1=Check_Common_Response(RESPONSE);

			 break;
		}
		case 6:
		{
			COMPARE_MATCH1=Check_Common_Response(RESPONSE);

			 break;
		}
		case 7:
		{
			COMPARE_MATCH1=  Check_SIM_status(RESPONSE);

			 break;
		}
		case 8:
		{
			COMPARE_MATCH1=CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		case 9:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		 
		 case 10:
		{
			COMPARE_MATCH1= Check_Network_Reg_status(RESPONSE);
			 break;
		}
		 case 11:
		{
			COMPARE_MATCH1= Check_Common_Response(RESPONSE);
			 break;
		}
		 case 12:
		{
			COMPARE_MATCH1= Check_Common_Response(RESPONSE);
			 break;
		}
	         case 13:
		{
			COMPARE_MATCH1= Check_Operator_Status(RESPONSE);
			 break;
		}
		case 14:
		{
			COMPARE_MATCH1=Check_Signal_Quality(RESPONSE);
			 break;
		}
		case 15:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		case 16:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		case 17:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		case 18:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		case 19:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		case 20:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		case 21:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
	
		
	}
	
   	return COMPARE_MATCH1; // No match found

}
//uint_t Check_30s_Data(const char *RESPONSE) {
//    for (int i = 0; CHECKS_RESPONSE[i] != NULL; i++) {
//        if (strstr(received_data, CHECKS_RESPONSE[i]) != NULL) {
//            printf("Match found: %s\n", CHECKS_RESPONSE[i]);
//        }
//    }
//}
