#ifndef OPERATORSTATUS_H
#define OPERATORSTATUS_H
#include<string.h>
#include<stdint.h>
typedef enum
{
	NETWORK_OPERATOR_ERROR,
	NETWORK_OPERATOR_AVAILABLE
}N_Operator_Status_t;

typedef struct
{
  N_Operator_Status_t status;
  const char* Prefix_Response;
  const char* End_Response;
}N_OPERATOR_Status_t;


extern const  N_OPERATOR_Status_t OPERATOR_STATUS_RESPONSE[];
extern N_Operator_Status_t Check_Operator_Status(uint8_t *RESPONSE);
#endif