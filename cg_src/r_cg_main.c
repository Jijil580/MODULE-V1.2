/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2015, 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_main.c
* Version      : Code Generator for RL78/I1C V1.01.07.02 [08 Nov 2021]
* Device(s)    : R5F10NLE
* Tool-Chain   : CCRL
* Description  : This file implements main function.
* Creation Date: 11-10-2024
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_tau.h"
#include "r_cg_wdt.h"
#include <stdio.h>
#include <stdlib.h>
#include "r_cg_sau.h"
#include "string.h"
#include "quecktel.h"
#include "r_cg_userdefine.h"



char at_command[50];
uint8_t TCP_SUCCESS[]="tcplisten mode\r\n";
uint8_t TCP_REPLY[]="HELLO IAM METER\r\n";
uint8_t TCP_CLOSE[]="AT+QICLOSE=1\r";
uint8_t TCP_OPEN[]="AT+QIOPEN=1,1,\"TCP LISTENER\",\"2401:4900:9831:FD7B::2\",0,4059,1,1\r";
uint8_t TEST_TCP_DATA[]="my name is jijil";




uint8_t TEMP_BUFFER[512];
 


uint8_t RECIEVED=0;
uint8_t RECIEVED_TCP=0;
long int TIMER_COUNT;
long int TIMER1_COUNT;

extern uint8_t COMPARE_MATCH1=0;
extern uint8_t TCP_INIT_STATUS;


int FEEDBACK_LENGTHG;
uint8_t count=0;
uint8_t BUF_FLAG=0;
uint8_t AT_COMMAND_COUNT=0;
uint8_t MODULE_MODE=0;

uint8_t TCP_DATA_PROCESSED=0;
int connection_id=11;
uint8_t frame_size=sizeof(TCP_REPLY);
uint8_t framsize=0;
uint8_t tcp_count=0;
uint8_t TCP_DATA=0;
//uint8_t TCP_FETCH[30];
//uint8_t **TCP_DATA_BUFFER;  // 2D array to hold up to 10 strings
/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
void Initialize_Module(void);
void PROCESS_TCP_DATA(void);
static void R_MAIN_UserInit(void);
void FETCH_TCPDATA_AND_SEND(void);
extern void __delay_ms(unsigned int milliseconds);
uint8_t INIT_MODULE_TO_LISTEN_TCP(void);
uint8_t CHECK_MODULE_RESPONSE(uint8_t *RESPONSE);
void SPLIT_TCP_DATA(uint8_t *BUFFER);
void generate_at_command(uint8_t connection_id, uint8_t frame_size);
static void r_uart0_callback_receiveend(void);
//void split_and_store(const uint8_t *input, uint8_t *output, size_t max_output_size);
uint8_t SEND_TCP_REPLY(void);
void split_and_store(void) ;
//void allocate_buffer();
int m;
int n;

uint8_t data[] = {
    0x00, 0x01, 0x00, 0x01, 0x00, 0x10, 0x00, 0x2B,
    0x61, 0x29, 0xA1, 0x09, 0x06, 0x07, 0x60, 0x85,
    0x74, 0x05, 0x08, 0x01, 0x01, 0xA2, 0x03, 0x02,
    0x01, 0x00, 0xA3, 0x05, 0xA1, 0x03, 0x02, 0x01,
    0x00, 0xBE, 0x10, 0x04, 0x0E, 0x08, 0x00, 0x06,
    0x5F, 0x1F, 0x04, 0x00, 0x00, 0x00, 0x10, 0x03,
    0x40, 0x00, 0x07
};


uint8_t READ_RESF=0;
 void __delay_ms(unsigned int milliseconds) {
    volatile unsigned int i, j;
    for (i = 0; i < milliseconds; i++) {
        for (j = 0; j < 1000; j++) {
          //  __asm("nop");  // No operation, just waste some cycles
        }
    }
}

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    READ_RESF=RESF;
    R_MAIN_UserInit();
    R_UART0_Start();
    R_UART1_Start();
  
    P7&=~(1<<2);
    P7|=(1<<1);
    P7 |=(1<<3);
    __delay_ms(1000);
    __delay_ms(1000);
     P7&=~(1<<3);
    
    __delay_ms(500); 
    
    
 
    while (1U)
    {
    	R_WDT_Restart(); 
	
	
	if(MODULE_MODE==INIT_MODE)
	{
		
		TCP_INIT_STATUS= INIT_MODULE_TO_LISTEN_TCP();
		
	}
	   
     
        if(MODULE_MODE==TCP_MODE)
	{	
		if(DATA_RECIEVED == 1) //ENSURE DATA IS RECIVED
                {
			DATA_RECIEVED=0;
			TT0 |= _0001_TAU_CH0_STOP_TRG_ON;
                        TMMK00 = 1U;    /* disable INTTM00 interrupt */
                        TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
			TIMER_COUNT=0;
			
			
			
			 timer1_Stop();
			 TIMER1_COUNT=0;
			 START_TIMER=0;
			 
			 ///CONDITION FOR HANDLING DATAS FROM METER // 
               		if(METER_DATA==1&&TCP_DATA==0)
	      	        {
				FETCH_TCPDATA_AND_SEND();
				METER_DATA=4;
				
				
				
	       		}
			
	       		//CONDITION FOR HANDLING TCP DATA/////
			
	       		else if(METER_DATA==0&&TCP_DATA==1)
	       		{
	        		
                		DATA_RECIEVED=0;
				RX0_BUFFER[RX0_BUFFER_COUNT]='\0';
				METER_DATA=3;
				TCP_DATA=3;
				//
				// timer1_Stop();
			        
				split_and_store(); 
	       			
	       			if(RECIEVED_TCP==1)
	       			{
		    			RECIEVED_TCP=0;
	             			R_UART1_Send(TEMP_BUFFER, strlen(TEMP_BUFFER)-2);
					//R_UART1_Send(at_commands[AT_COMMAND_COUNT], strlen(at_commands[AT_COMMAND_COUNT])); 
					START_TIMER=0;
					for(n=0;n<=512;n++)
					RX1_BUFFER[n]=0;
					RX0_BUFFER_COUNT=0;
					//memset(RX1_BUFFER,0,sizeof(RX1_BUFFER));
					
	      			}
		
		
	       		}
	 
	      }

	      
	   TCP_INIT_STATUS=1;
	   TIMER1_COUNT=0;
           START_TIMER=0;
	   
	}
	
        ;
	
      }
      
      
      
      
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
uint8_t INIT_MODULE_TO_LISTEN_TCP(void) // Fix: Function name formatting (spaces not allowed)
{
    if (DATA_RECIEVED == 1) // Ensure proper spacing for readability
    {
	    
	RX0_BUFFER[RX0_BUFFER_COUNT]='\0';
        COMPARE_MATCH1=CHECK_MODULE_RESPONSE(RX0_BUFFER);
	if(COMPARE_MATCH1==1)
		{
        	AT_COMMAND_COUNT++; // Increment `TCP_INT_FLAG`
		COMPARE_MATCH1=0;
		}
        DATA_RECIEVED = 0; // Reset flag
        memset(RX0_BUFFER, 0, 200); // Clear buffer
        RX0_BUFFER_COUNT = 0; // Reset buffer count

        if (AT_COMMAND_COUNT<=22) // Ensure `TCP_INT_FLAG` is within valid range
       		 {
         	 R_UART0_Send(at_commands[AT_COMMAND_COUNT], strlen(at_commands[AT_COMMAND_COUNT])); // Send AT command
		 TCP_INIT_STATUS=0;
		 MODULE_MODE=0;
	
       		 }
	if(AT_COMMAND_COUNT>=22)
	{
	  TCP_INIT_STATUS=TCP_INITIALISED;
	  AT_COMMAND_COUNT=0;
	  MODULE_MODE=1;
	}
    }
   return TCP_INIT_STATUS;
}


//uint8_t CHECK_MODULE_RESPONSE(uint8_t *RESPONSE)
//{
//	RX0_BUFFER[RX0_BUFFER_COUNT]='\0';
//	for (BUF_FLAG = 0;BUF_FLAG < RX0_BUFFER_COUNT;BUF_FLAG++)
//        {
//            // Check if the current sequence matches "OK\r\n"
//            if(RESPONSE[BUF_FLAG] == 'O' && RESPONSE[BUF_FLAG+ 1] == 'K' && RESPONSE[BUF_FLAG+ 2] == '\r' && RESPONSE[BUF_FLAG + 3] == '\n')
//            {
//                return 1; // Match found, return 1
//            }
//	}

//    return 0; // No match found

//}

void FETCH_TCPDATA_AND_SEND(void)
{
	         uint8_t data_length=0;
		
		 DATA_RECIEVED=0;
		 METER_DATA=0;
		
		 RX1_BUFFER[RX1_BUFFER_COUNT]='\0';
		 data_length=RX1_BUFFER_COUNT;
		sprintf(at_command, "AT+QISEND=%u,%u\r\n", 11,51);//CREATE AT COMMAND FOR SENDING
		
		  R_UART0_Send(at_command, strlen(at_command));
		  __delay_ms(100);
		    //R_WDT_Restart(); 
		  R_UART0_Send(RX1_BUFFER, 51);
		  MODULE_MODE=1;
		 
		
	
}
void split_and_store(void)
{
     
    int i; 
    int temp_index=0;
    int data_intex=0;
    
    memset(TEMP_BUFFER,0,sizeof(TEMP_BUFFER));
    for(i=0;i<500;i++)
    {
	if(RX0_BUFFER[i]=='r'&&RX0_BUFFER[i+1]=='e'&&
	RX0_BUFFER[i+2]=='c'&&RX0_BUFFER[i+3]=='v')  
	{
          RECIEVED_TCP=1;
	  RECIEVED=1;
	  data_intex=i;
	  break;
	}
    }
    if(RECIEVED==1)
    {
	 for(i=data_intex;i<=512;i++)
	  {
		if((RX0_BUFFER[i]=='\n')&&(RECIEVED!=2))
		{
	         	RECIEVED=2;
			i++;
		}
		if(RECIEVED==2)
		{
	  		TEMP_BUFFER[temp_index]=RX0_BUFFER[i];
	  		temp_index++;
		}
	  }
           TEMP_BUFFER[temp_index]='\0';
           RECIEVED=0;
	   memset(RX0_BUFFER,0,sizeof(RX0_BUFFER));
	   data_intex=0;
	   temp_index=0;
     }
	
}

uint8_t CHECK_MODULE_RESPONSE(uint8_t *RESPONSE)
{
	
	
	switch (AT_COMMAND_COUNT)
	{
		case 0:
		{
			COMPARE_MATCH1=CHECK_OK_RESPONSE(RESPONSE);

			 break;
		}
		case 1:
		{
			COMPARE_MATCH1=Check_Common_Response(RESPONSE);

			 break;
		}
		case 2:
		{
			
			COMPARE_MATCH1=Check_Common_Response(RESPONSE);

			 break;
		}
		case 3:
		{
			
			COMPARE_MATCH1=Check_Common_Response(RESPONSE);

			 break;
		}
	        case 4:
		{
			COMPARE_MATCH1=Check_EDRX_Status(RESPONSE);
			
			break;
		}
		case 5:
		{
			COMPARE_MATCH1=Check_Common_Response(RESPONSE);

			 break;
		}
		case 6:
		{
			COMPARE_MATCH1=Check_Common_Response(RESPONSE);

			 break;
		}
		case 7:
		{
			COMPARE_MATCH1= Check_SIM_status(RESPONSE);

			 break;
		}
		case 8:
		{
			COMPARE_MATCH1=CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		case 9:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		 
		 case 10:
		{
			COMPARE_MATCH1= Ceck_Network_Reg_status(RESPONSE);
			 break;
		}
		 case 11:
		{
			COMPARE_MATCH1= Check_Common_Response(RESPONSE);
			 break;
		}
		 case 12:
		{
			COMPARE_MATCH1= Check_Common_Response(RESPONSE);
			 break;
		}
	         case 13:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		case 14:
		{
			COMPARE_MATCH1=Check_Signal_Quality(RESPONSE);
			 break;
		}
		case 15:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		case 16:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		case 17:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		case 18:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		case 19:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		case 20:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
		case 21:
		{
			COMPARE_MATCH1= CHECK_OK_RESPONSE(RESPONSE);
			 break;
		}
	
		
	}
	
	
	
    return COMPARE_MATCH1; // No match found

}



