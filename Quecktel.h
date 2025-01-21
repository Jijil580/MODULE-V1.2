#ifndef QUECKTEL_H
#define QUECKTEL_H
#include "r_cg_macrodriver.h"
extern const char *at_commands[];
extern const char *COMMON_RESPONSE[];
extern const char *EDRX_RESPONSE[];
extern const char *SIM_QUERRY_RESPONSE[];
extern const char *NETWORK_REGI_STATUS[];
extern const char *OPERATOR_STATUS[];
extern const char *SIGNAL_QUALITY[];
uint8_t Check_Common_Response(uint8_t *RESPONSE);
uint8_t Check_SIM_status(uint8_t *RESPONSE);
uint8_t Check_EDRX_Status(uint8_t *RESPONSE);
uint8_t Ceck_Network_Reg_status(uint8_t *RESPONSE);
uint8_t CHECK_OK_RESPONSE(uint8_t *RESPONSE);



#endif