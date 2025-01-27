#include "simstatus.h"
#include "string.h"



const Cpin_Response_t CPIN_RESPONSE[]=
{
	{READY,"\r\n+CPIN: READY\r\n\r\nOK\r\n"},
	
	{READY,"\r\n+CPIN: SIM PIN\r\n\r\nOK\r\n"},
	
	{READY,"\r\n+CPIN: SIM PUK\r\n\r\nOK\r\n"},
	
	{READY,"\r\n+CPIN: SIM PIN2\r\n\r\nOK\r\n"},
	
	{READY,"\r\n+CPIN: SIM PUK2\r\n\r\nOK\r\n"},
	{SIM_ERROR,"\r\nERROR\r\n"}
	
};

Cpin_Status_t Check_SIM_status(uint8_t *RESPONSE)
{
    int String_index;

    
    for (String_index = 0; String_index < (sizeof(CPIN_RESPONSE) / sizeof(CPIN_RESPONSE[0])); String_index++)
    {
        
        if (strncmp((char *)RESPONSE, CPIN_RESPONSE[String_index].response, strlen(CPIN_RESPONSE[String_index].response)) == 0)
        {
            return CPIN_RESPONSE[String_index].status;  // Return the matching status
        }
    }

    return SIM_ERROR;  // Return SIM_ERROR if no match is found
}