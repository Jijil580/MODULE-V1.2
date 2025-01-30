#include "operatorstatus.h"
#include "string.h"

const  N_OPERATOR_Status_t OPERATOR_STATUS_RESPONSE[]=
{
	
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 0,0,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 0,0,\"","\",7\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 0,1,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 0,1,\"","\",7\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 0,2,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 0,2,\"","\",7\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 0,3,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 0,3,\"","\",7\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 0,4,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 0,4,\"","\",7\r\n\r\nOK\r\n"},
	
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 1,0,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 1,0,\"","\",7\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 1,1,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 1,1,\"","\",7\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 1,2,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 1,2,\"","\",7\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 1,3,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 1,3,\"","\",7\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 1,4,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 1,4,\"","\",7\r\n\r\nOK\r\n"},
	
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 2,0,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 2,0,\"","\",7\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 2,1,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 2,1,\"","\",7\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 2,2,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 2,2,\"","\",7\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 2,3,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 2,3,\"","\",7\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 2,4,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 2,4,\"","\",7\r\n\r\nOK\r\n"},
	
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 3,0,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 3,0,\"","\",7\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 3,1,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 3,1,\"","\",7\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 3,2,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 3,2,\"","\",7\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 3,3,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 3,3,\"","\",7\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 3,4,\"","\",0\r\n\r\nOK\r\n"},
	{NETWORK_OPERATOR_AVAILABLE,"\r\n+COPS: 3,4,\"","\",7\r\n\r\nOK\r\n"}
};

N_Operator_Status_t Check_Operator_Status(uint8_t *RESPONSE)
{
	int String_index;
	const char *end_RESPONSE = strrchr((char*)RESPONSE, '"');///POINTS TO THES RESPONSE AFTER LAST OCCURANCE OF"
	
	for (String_index = 0; String_index < (sizeof(OPERATOR_STATUS_RESPONSE) / sizeof(OPERATOR_STATUS_RESPONSE[0])); String_index++)
        {
        if ((strncmp((char *)RESPONSE,OPERATOR_STATUS_RESPONSE[String_index].Prefix_Response,strlen(OPERATOR_STATUS_RESPONSE[String_index].Prefix_Response))==0)
	&&(strcmp(end_RESPONSE,OPERATOR_STATUS_RESPONSE[String_index].End_Response)==0))
        {
            return OPERATOR_STATUS_RESPONSE[String_index].status; 
        }
    }

}