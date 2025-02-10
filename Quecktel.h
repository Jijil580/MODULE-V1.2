#ifndef QUECKTEL_H
#define QUECKTEL_H
#include "r_cg_macrodriver.h"


#define GENERATE_ATCOMMAND(CONNECTIONID,DATA_LENGTH)    "AT+QISEND="#CONNECTIONID","DATA_LENGTH"\r\n" 
#define METER_REPLIED    (METER_DATA==1&&TCP_DATA==0)
#define GURUX_COMMAND    (METER_DATA==0&&TCP_DATA==1)
#define RECEPTION_COMPLETED_FROM_METER  (WAIT_COUNT>WAIT_TIME1)
#define  RECEPTION_COMPLETED_FROM_MODULE (WAIT_COUNT>WAIT_TIME2)
extern  uint8_t RX0_BUFFER[512];
extern uint8_t RX1_BUFFER[1024];
extern const char *at_commands[];
extern const char *COMMON_RESPONSE[];
extern const char *EDRX_RESPONSE[];
extern const char *SIM_QUERRY_RESPONSE[];
extern const char *NETWORK_REGI_STATUS[];
extern const char *OPERATOR_STATUS[];
extern const char *SIGNAL_QUALITY[];
extern const char *THIRTY_SECONDS_CHECKS[];
uint8_t Check_Common_Response(uint8_t *RESPONSE);

extern uint8_t COMPARE_MATCH1;
extern uint8_t AT_COMMAND_COUNT;
extern long int TIMER_COUNT;
extern long int TIMER1_COUNT;
extern uint8_t METER_DATA;
extern uint8_t TCP_DATA;
extern uint8_t DATA_RECIEVED;
extern uint8_t HANDLING_METER_DATA;
//uint8_t Check_SIM_status(uint8_t *RESPONSE);
uint8_t Check_EDRX_Status(uint8_t *RESPONSE);
uint8_t Check_QISTATE(uint8_t *RESPONSE);
uint8_t CHECK_OK_RESPONSE(uint8_t *RESPONSE);
uint8_t Check_Signal_Quality(uint8_t *RESPONSE);
extern uint8_t CHECK_MODULE_RESPONSE(uint8_t *RESPONSE);

#endif