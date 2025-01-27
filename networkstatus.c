#include "networkstatus.h"
#include "string.h"
#include <stdio.h>

const NETWORK_STATUS_t NETWORK_RESPONSE[] =
{
    {NETWORK_REGISTERED, "\r\n+CREG: 0,1\r\n\r\nOK\r\n"},
    {NETWORK_ERROR, "\r\n+CREG: 0,2\r\n\r\nOK\r\n"},
    {NETWORK_ERROR, "\r\n+CREG: 0,3\r\n\r\nOK\r\n"},
    {NETWORK_ERROR, "\r\n+CREG: 0,4\r\n\r\nOK\r\n"},
    {NETWORK_REGISTERED, "\r\n+CREG: 0,5\r\n\r\nOK\r\n"},
    
    {NETWORK_ERROR, "\r\n+CREG: 1,0\r\n\r\nOK\r\n"},
    {NETWORK_REGISTERED, "\r\n+CREG: 1,1\r\n\r\nOK\r\n"},
    {NETWORK_ERROR, "\r\n+CREG: 1,2\r\n\r\nOK\r\n"},
    {NETWORK_ERROR, "\r\n+CREG: 1,3\r\n\r\nOK\r\n"},
    {NETWORK_ERROR, "\r\n+CREG: 1,4\r\n\r\nOK\r\n"},
    {NETWORK_REGISTERED, "\r\n+CREG: 1,5\r\n\r\nOK\r\n"},
    
    {NETWORK_ERROR, "\r\n+CREG: 2,0\r\n\r\nOK\r\n"},
    {NETWORK_REGISTERED, "\r\n+CREG: 2,1\r\n\r\nOK\r\n"},
    {NETWORK_ERROR, "\r\n+CREG: 2,2\r\n\r\nOK\r\n"},
    {NETWORK_ERROR, "\r\n+CREG: 2,3\r\n\r\nOK\r\n"},
    {NETWORK_ERROR, "\r\n+CREG: 2,4\r\n\r\nOK\r\n"},
    {NETWORK_REGISTERED, "\r\n+CREG: 2,5\r\n\r\nOK\r\n"}
};

Network_Status_t Check_Network_Reg_status(uint8_t *RESPONSE)
{
    int String_index;

    for (String_index = 0; String_index < (sizeof(NETWORK_RESPONSE) / sizeof(NETWORK_RESPONSE[0])); String_index++)
    {
        if (strstr((char *)RESPONSE, NETWORK_RESPONSE[String_index].response) != NULL)
        {
            return NETWORK_RESPONSE[String_index].status;  // Return the matching status
        }
    }

    return NETWORK_ERROR;  // Return NETWORK_ERROR if no match is found
}
