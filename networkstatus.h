#ifndef NETWORKSTATUS_H
#define NETWORKSTATUS_H
#include <stdint.h> 

typedef enum
{
  NETWORK_ERROR,
  NETWORK_REGISTERED
}Network_Status_t;

typedef struct
{
   Network_Status_t status;
   const char* response;
	
}NETWORK_STATUS_t;



extern Network_Status_t Check_Network_Reg_status(uint8_t *RESPONSE);
extern const NETWORK_STATUS_t NETWORK_RESPONSE[];

#endif
