#include  "r_cg_macrodriver.h"
#include "quecktel.h"
#include  "string.h"
#include "r_cg_sau.h"

#define CHECK(index) if(strncmp((char *)RESPONSE, SIGNAL_QUALITY["#index"], strlen(SIGNAL_QUALITY["#index"])) == 0)

uint8_t Check_Common_Response(uint8_t *RESPONSE);
uint8_t Check_SIM_status(uint8_t *RESPONSE);
uint8_t Check_EDRX_Status(uint8_t *RESPONSE);


int Sting_index=0;



uint8_t CHECK_OK_RESPONSE(uint8_t *RESPONSE)
{
	int BUF_FLAG; 
	RX0_BUFFER[RX0_BUFFER_COUNT]='\0';
	for (BUF_FLAG = 0;BUF_FLAG < RX0_BUFFER_COUNT;BUF_FLAG++)
        {
            // Check if the current sequence matches "OK\r\n"
            if(RESPONSE[BUF_FLAG] == 'O' && RESPONSE[BUF_FLAG+ 1] == 'K' && RESPONSE[BUF_FLAG+ 2] == '\r' && RESPONSE[BUF_FLAG + 3] == '\n')
            {
                return 1; // Match found, return 1
            }
	}

        return 0; // No match found

}


uint8_t Check_Common_Response(uint8_t *RESPONSE)
{

	for(Sting_index=0;Sting_index<=2;Sting_index++)
	{
        
	 	if (strncmp((char *)RESPONSE, COMMON_RESPONSE[Sting_index], strlen(COMMON_RESPONSE[Sting_index])) == 0)
         	{
         		return 1;        
        	 }
	}
         			 
			
			
	return 0; 
}

uint8_t Check_EDRX_Status(uint8_t *RESPONSE)
{
	 if (strncmp((char *)RESPONSE, EDRX_RESPONSE[0], strlen(EDRX_RESPONSE[0])) == 0)
	 {
	 	return 1; 	 
         }
	  if (strncmp((char *)RESPONSE, EDRX_RESPONSE[1], strlen(EDRX_RESPONSE[1])) == 0)
	 {
	 	return 0; 	 
         }
	 return 0;
	
}



uint8_t Check_SIM_status(uint8_t *RESPONSE)
{
	for(Sting_index=0;Sting_index<=5;Sting_index++)
	{
	 	if (strncmp((char *)RESPONSE, SIM_QUERRY_RESPONSE[Sting_index], strlen(SIM_QUERRY_RESPONSE[Sting_index])) == 0)
	 	{
			if(Sting_index!=5)
	 		return 1;
			else 
			return 1;
         	}
	}
	
	 return 0;
	
	
}

uint8_t Ceck_Network_Reg_status(uint8_t *RESPONSE)///1,57 11 13 17 retun 1 for these index
{
	for(Sting_index=0;Sting_index<=17;Sting_index++)
	{
	 	if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[Sting_index], strlen(NETWORK_REGI_STATUS[Sting_index])) == 0)
	 	{
			if((Sting_index==1)||(Sting_index==5)||(Sting_index==7)||(Sting_index==11)||(Sting_index==13)||(Sting_index==17))
	 		return 1; 
			else
			return 1;
         	}
	}	
	 
	 
	 return 0;
		 	 
	 
}
uint8_t Check_Operator_Status(uint8_t *RESPONSE)
{
   if (strncmp((char *)RESPONSE, OPERATOR_STATUS[0], strlen(OPERATOR_STATUS[0])) == 0)
	 {
	 	return 1; 	 
         }	
	 return 0;
}
uint8_t Check_Sigmal_Qulity(uint8_t *RESPONSE)
{
	for(Sting_index=0;Sting_index<=288;Sting_index++)
	{
		if(strncmp((char *)RESPONSE, SIGNAL_QUALITY[Sting_index], strlen(SIGNAL_QUALITY[Sting_index])) == 0)
	 	{
	 		return 1; 	 
        	}	
		
		
	}
	 return 0;
	
}


