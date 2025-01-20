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
	
}


