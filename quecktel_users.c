#include  "r_cg_macrodriver.h"
#include "quecktel.h"
#include  "string.h"
#include "r_cg_sau.h"

uint8_t Check_Common_Response(uint8_t *RESPONSE);
uint8_t Check_SIM_status(uint8_t *RESPONSE);
uint8_t Check_EDRX_Status(uint8_t *RESPONSE);

uint8_t Check_Common_Response(uint8_t *RESPONSE)
{

	
        
	 if (strncmp((char *)RESPONSE, COMMON_RESPONSE[0], strlen(COMMON_RESPONSE[0])) == 0)
         {
         	return 1;        
         }
         if (strncmp((char *)RESPONSE, COMMON_RESPONSE[1], strlen(COMMON_RESPONSE[1])) == 0)
         {
         	return 1;        
         }
                                                   
				 
	 if (strncmp((char *)RESPONSE, COMMON_RESPONSE[2], strlen(COMMON_RESPONSE[2])) == 0)
         {
                return 0;        
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
	
	 if (strncmp((char *)RESPONSE, SIM_QUERRY_RESPONSE[0], strlen(SIM_QUERRY_RESPONSE[0])) == 0)
	 {
	 	return 1; 	 
         }
	 if (strncmp((char *)RESPONSE, SIM_QUERRY_RESPONSE[1], strlen(SIM_QUERRY_RESPONSE[1])) == 0)
	 {
	 	return 1; 	 
         }
	 if (strncmp((char *)RESPONSE, SIM_QUERRY_RESPONSE[2], strlen(SIM_QUERRY_RESPONSE[2])) == 0)
	 {
	 	return 1; 	 
         }
	 if (strncmp((char *)RESPONSE, SIM_QUERRY_RESPONSE[3], strlen(SIM_QUERRY_RESPONSE[3])) == 0)
	 {
	 	return 1; 	 
         }
	 if (strncmp((char *)RESPONSE, SIM_QUERRY_RESPONSE[4], strlen(SIM_QUERRY_RESPONSE[4])) == 0)
	 {
	 	return 1; 	 
         }
	 if (strncmp((char *)RESPONSE, SIM_QUERRY_RESPONSE[5], strlen(SIM_QUERRY_RESPONSE[5])) == 0)
	 {
	 	return 0; 	 
         }
	 return 0;
	
	
}

uint8_t Ceck_Network_Reg_status(uint8_t *RESPONSE)
{
	 if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[0], strlen(NETWORK_REGI_STATUS[0])) == 0)
	 {
	 	return 0; 	 
         }
	 if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[1], strlen(NETWORK_REGI_STATUS[1])) == 0)
	 {
	 	return 1; 	 
         }
	  if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[2], strlen(NETWORK_REGI_STATUS[2])) == 0)
	 {
	 	return 0; 	 
         }
	  if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[3], strlen(NETWORK_REGI_STATUS[3])) == 0)
	 {
	 	return 0; 	 
         }
	  if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[4], strlen(NETWORK_REGI_STATUS[4])) == 0)
	 {
	 	return 0; 	 
         }
	  if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[5], strlen(NETWORK_REGI_STATUS[5])) == 0)
	 {
	 	return 1; 	 
         }
	  if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[6], strlen(NETWORK_REGI_STATUS[6])) == 0)
	 {
	 	return 0; 	 
         }
	 if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[7], strlen(NETWORK_REGI_STATUS[7])) == 0)
	 {
	 	return 1; 	 
         }
	  if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[8], strlen(NETWORK_REGI_STATUS[8])) == 0)
	 {
	 	return 0; 	 
         }
	  if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[9], strlen(NETWORK_REGI_STATUS[9])) == 0)
	 {
	 	return 0; 	 
         }
	  if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[10], strlen(NETWORK_REGI_STATUS[10])) == 0)
	 {
	 	return 0; 	 
         }
	  if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[11], strlen(NETWORK_REGI_STATUS[11])) == 0)
	 {
	 	return 1; 	 
         }
	  if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[12], strlen(NETWORK_REGI_STATUS[12])) == 0)
	 {
	 	return 0; 	 
         }
	 if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[13], strlen(NETWORK_REGI_STATUS[13])) == 0)
	 {
	 	return 1; 	 
         }
	  if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[14], strlen(NETWORK_REGI_STATUS[14])) == 0)
	 {
	 	return 0; 	 
         }
	  if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[15], strlen(NETWORK_REGI_STATUS[15])) == 0)
	 {
	 	return 0; 	 
         }
	  if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[16], strlen(NETWORK_REGI_STATUS[16])) == 0)
	 {
	 	return 0; 	 
         }
	  if (strncmp((char *)RESPONSE, NETWORK_REGI_STATUS[17], strlen(NETWORK_REGI_STATUS[17])) == 0)
	 {
	 	return 1; 	 
         }
	 
	 return 0;
		 	 
	 
}
uint8_t Check_Operator_Status(uint8_t *RESPONSE)
{
   if (strncmp((char *)RESPONSE, OPERATOR_STATUS[0], strlen(OPERATOR_STATUS[0])) == 0)
	 {
	 	return 1; 	 
         }	
}

