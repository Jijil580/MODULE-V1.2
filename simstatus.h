#ifndef SIMSTATUS_H
#define SIMSTATUS_H
#include <stdint.h> 
typedef enum
{
	SIM_ERROR,
	READY	
}Cpin_Status_t;


typedef struct
{
	Cpin_Status_t status;
	const char* response;
}Cpin_Response_t;

extern const Cpin_Response_t CPIN_RESPONSE[];

extern Cpin_Status_t Check_SIM_status(uint8_t *RESPONSE);
#endif