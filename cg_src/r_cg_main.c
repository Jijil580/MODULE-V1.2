/*--------------------------------------------------------------------------------------------------------/
FIRWARE VERSION: MOD_FW_V1
date           : sept 2024 
----------------------------------------------------------------------------------------------------------*/

   /*header files
   --------------*/
   
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_tau.h"
#include "r_cg_wdt.h"
#include "r_cg_sau.h"
#include <stdio.h>
#include <stdlib.h>
#include "r_cg_sau.h"
#include "string.h"
#include "quecktel.h"
#include "r_cg_userdefine.h"
#include "simstatus.h"
#include "networkstatus.h"
#include "operatorstatus.h"


#define WAIT_TIME1 750//300000
#define WAIT_TIME2 600//30000
#define MODULE_INIT_TIME 100//20000
#define SECONDS_30  (TIMER_COUNT==60)
  /*global variables*/
  
uint8_t TCP_CLOSE[]="AT+QICLOSE=1\r";
uint8_t QISTATE[]="AT+QISTATE\r";
volatile uint16_t data_length=0;
uint8_t TEMP_BUFFER[512];
uint8_t RECIEVED=0;
uint8_t RECIEVED_TCP=0;
long int TIMER_COUNT;
long int TIMER1_COUNT;
extern uint8_t TCP_INIT_STATUS;
uint8_t at_command[30];
uint8_t BUF_FLAG=0;
int temp_index=0;
int data_intex=0;
int RETRY_COUNT=0;
uint8_t MODULE_MODE=0;
uint8_t TCP_DATA_PROCESSED=0;
uint8_t TCP_DATA=0;
uint8_t buffer_Count;
extern unsigned long int WAIT_COUNT;
uint8_t   DATA_RECIEVEING=0;
uint8_t size_atcommand=0;
 /*FUNCTION DECLARATION*/
 
void TURN_ON_MODULE(void);
void Initialize_Module(void);
void Network_Check_Activity(void);
void CHECK_MODULE_STATUS(uint8_t *RESPONSE);
uint8_t WAIT_RECEPTION_TO_COMPLETE(void);
static void R_MAIN_UserInit(void);
void FETCH_METERDATA_AND_SEND(void);
extern void __delay_ms(unsigned int milliseconds);
uint8_t INIT_MODULE_TO_TCP_LISTENMODE(void);
void generate_at_command(uint8_t connection_id, uint8_t frame_size);
uint8_t WAIT_RECEPTION_TO_COMPLETE(void);
void FETCH_TCP_DATA(void) ;
uint16_t calculate_data_length(void);
void Check_QIstate(void);

uint8_t READ_RESF;
 void __delay_ms(unsigned int milliseconds) {
    volatile unsigned int i, j;
    for (i = 0; i < milliseconds; i++) {
        for (j = 0; j < 1000; j++) {
          
        }
    }
}

/*----------------------------------------------------------------------------------------------------------------------/
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
-----------------------------------------------------------------------------------------------------------------------*/
void main(void)
{
	
    	R_MAIN_UserInit();
        TURN_ON_MODULE();
	//R_TAU0_Channel1_Start();
        //R_TAU0_Channel0_Start();
	while (1U)
    	{

		R_WDT_Restart();
		//Network_Check_Activity();
		if(MODULE_MODE==INIT_MODE&&DATA_RECIEVED==1)
		{       
		/*INIT MODE*/
		    
		        if(WAIT_COUNT==0)
			{
				WAIT_COUNT=1;
				WAIT_RECEPTION_TO_COMPLETE();
			}
			if(WAIT_COUNT>=MODULE_INIT_TIME)
			{
				 R_TAU0_Channel0_Stop();
		         	 WAIT_COUNT=0;
		         	 TCP_INIT_STATUS= INIT_MODULE_TO_TCP_LISTENMODE();
			}
		}
	   
     
        	if(MODULE_MODE==TCP_MODE)
		{	
		/*TCP LISTNER MODE*/  
			if(DATA_RECIEVED == 1) //ENSURE DATA IS RECIVED
                	{
			   		
               				if(METER_REPLIED)
	      	        		{
				 	/*data recieved over meter*/
					         if(WAIT_COUNT==0)
						{       DATA_RECIEVEING=1;
							WAIT_COUNT=1;
							WAIT_RECEPTION_TO_COMPLETE();
						}
				           	if(RECEPTION_COMPLETED_FROM_METER)
				            	{
							//DI();
							R_TAU0_Channel0_Stop();
						    	DATA_RECIEVED=0;
					               	WAIT_COUNT=0;
							FETCH_METERDATA_AND_SEND();
							METER_DATA=1;
					    	}
	       				}
	       				else if(GURUX_COMMAND)
	       				{
	        		      	/**data recieved over TCP**/ 
					
					        if(WAIT_COUNT==0)
						{       DATA_RECIEVEING=1;
							WAIT_COUNT=1;
							WAIT_RECEPTION_TO_COMPLETE();
						}
					     	if(RECEPTION_COMPLETED_FROM_MODULE)
				               	{     
							R_TAU0_Channel0_Stop();
							DATA_RECIEVED=0;
					         	WAIT_COUNT=0;
                					DATA_RECIEVED=0;
							RX0_BUFFER[RX0_BUFFER_COUNT]='\0';
							FETCH_TCP_DATA(); //extract data 
	       		         	
	       						if(RECIEVED_TCP==1)
	       						{
							/*valid data with length*/
		    						RECIEVED_TCP=0;
	             						R_UART1_Send(TEMP_BUFFER,temp_index-3);
								RX0_BUFFER_COUNT=0;
								DATA_RECIEVEING=0;
								
	      						}
					       	}
		
	       			 	
					}
				
			
	       		}
			//if data recievd end
	
		}//if tcp mode end;

		
		
//		if(SECONDS_30&&DATA_RECIEVED==0)
//		{ 
//		     MODULE_MODE=CHECK_MODE;
//		     TIMER_COUNT=0;
//		     R_UART0_Send(THIRTY_SECONDS_CHECKS[AT_COMMAND_COUNT], strlen(THIRTY_SECONDS_CHECKS[AT_COMMAND_COUNT]));
//		}
//		if(MODULE_MODE==CHECK_MODE&&DATA_RECIEVED==1)
//		{
//			 if(WAIT_COUNT==0)
//			{
//				WAIT_COUNT=1;
//				WAIT_RECEPTION_TO_COMPLETE();
//			}
//			//CHECK_MODULE_STATUS(RX0_BUFFER);//R_UART0_Send(THIRTY_SECONDS_CHECKS[AT_COMMAND_COUNT], strlen(THIRTY_SECONDS_CHECKS[AT_COMMAND_COUNT]));
//			if(WAIT_COUNT>=MODULE_INIT_TIME)
//			{
//				 R_TAU0_Channel0_Stop();
//		         	 WAIT_COUNT=0;
//		         	 CHECK_MODULE_STATUS(RX0_BUFFER);
//			}
		        
//		}
	
	
      	}//while loop end
   
}//main end

/*-------------------------------------------------------------------------------------------------------------------/
* Function Name: INIT_MODULE_TO_TCP_LISTENMODE
* Description  : This function sends necessary AT commands to make the module in "TCPLISTNER MODE"
* Arguments    : None
* Return Value : RETURNS 0 0R 1
--------------------------------------------------------------------------------------------------------------------*/
uint8_t INIT_MODULE_TO_TCP_LISTENMODE(void) 
{
	if (DATA_RECIEVED == 1) 
    	{
	    
		RX0_BUFFER[RX0_BUFFER_COUNT]='\0';
        	COMPARE_MATCH1=CHECK_MODULE_RESPONSE(RX0_BUFFER);
		if(COMPARE_MATCH1==1)
		{
        		AT_COMMAND_COUNT++; // Increment `TCP_INT_FLAG`
			COMPARE_MATCH1=0;
		}
		else
		RETRY_COUNT++;
		
        	DATA_RECIEVED = 0; // Reset flag
        	memset(RX0_BUFFER, 0, 200); // Clear buffer
        	RX0_BUFFER_COUNT = 0; // Reset buffer count

        	if (AT_COMMAND_COUNT<=22) 
       		{       if(RETRY_COUNT==10)
		        {
		        AT_COMMAND_COUNT=0;
			RETRY_COUNT=0;
			}
         	 	R_UART0_Send(at_commands[AT_COMMAND_COUNT], strlen(at_commands[AT_COMMAND_COUNT])); // Send AT command
		 	TCP_INIT_STATUS=0;
		 	MODULE_MODE=0;
       		}
		if(AT_COMMAND_COUNT>=22)
		{
	 	 	TCP_INIT_STATUS=TCP_INITIALISED;
	 	 	AT_COMMAND_COUNT=0;
		 	MODULE_MODE=1;
		        METER_DATA=1;
		}
    	}
	return TCP_INIT_STATUS;
}
/*-------------------------------------------------------------------------------------------------------------------/
* Function Name: FETCH_METERDATA_AND_SEND
* Description  : This function sends data recieved from meter over tcp
* Arguments    : None
* Return Value :none
--------------------------------------------------------------------------------------------------------------------*/
void FETCH_METERDATA_AND_SEND(void)
{
        
	DATA_RECIEVED=0;
	data_length=0;
	data_length=RX1_BUFFER_COUNT;
	sprintf(at_command, "AT+QISEND=%u,%u\r\n", 11,data_length);//CREATE AT COMMAND FOR SEND over TCP
	size_atcommand=sizeof(at_command);
	R_UART0_Send(at_command,size_atcommand);
	DATA_RECIEVED=1;
	
	
}
/*-------------------------------------------------------------------------------------------------------------------/
* Function Name: FETCH_TCP_DATA
* Description  : This function extracts the data part recieved over tcp
* Arguments    : None
* Return Value :none
--------------------------------------------------------------------------------------------------------------------*/
void FETCH_TCP_DATA(void)
{
	int i; 
	temp_index=0;
        data_intex=0;
    	
    	memset(TEMP_BUFFER,0,sizeof(TEMP_BUFFER));
    	for(i=0;i<512;i++)
    	{
		if(RX0_BUFFER[i]=='r'&&RX0_BUFFER[i+1]=='e'&&
		RX0_BUFFER[i+2]=='c'&&RX0_BUFFER[i+3]=='v')  //check wheather the data is recieved
		{
          		RECIEVED_TCP=1;
	  		RECIEVED=1;
	  		data_intex=i;
			memset(RX1_BUFFER,0,sizeof(RX1_BUFFER)-1);
	  		
		}
		if(RX0_BUFFER[i]=='f'&&RX0_BUFFER[i+1]=='u'&&
		RX0_BUFFER[i+2]=='l'&&RX0_BUFFER[i+3]=='l')  // check "incoming full" if true reinit tcplistenmode
		{
          		MODULE_MODE=0;//*INIT mode
	  		AT_COMMAND_COUNT=21;//at command_count for listen mode
			DATA_RECIEVED=1;
	  		memset(RX0_BUFFER,0,sizeof(RX0_BUFFER));
			
		}
		if(RX0_BUFFER[i]=='c'&&RX0_BUFFER[i+1]=='l'&&
		RX0_BUFFER[i+2]=='0'&&RX0_BUFFER[i+3]=='s'&&RX0_BUFFER[i+4]=='e'&&RX0_BUFFER[i+5]=='d')  // check "tcp closed" if true reinit tcplistenmode
		{
          		MODULE_MODE=0;//*INIT mode
	  		AT_COMMAND_COUNT=21;//at command_count for listen mode
	  		//break;
			DATA_RECIEVED=1;
			memset(RX0_BUFFER,0,sizeof(RX0_BUFFER));
			break;
		}
		if(RX0_BUFFER[i]=='E'&&RX0_BUFFER[i+1]=='R'&&
		RX0_BUFFER[i+2]=='R'&&RX0_BUFFER[i+3]=='0'&&RX0_BUFFER[i+4]=='R')  // check "ERROR" if true reinit tcplistenmode
		{
          		MODULE_MODE=0;//*INIT mode
	  		AT_COMMAND_COUNT=1;//at command_count for listen mode
	  		//break;
			DATA_RECIEVED=1;
			memset(RX0_BUFFER,0,sizeof(RX0_BUFFER)-1);
		}
		if(RX0_BUFFER[i]=='S'&&RX0_BUFFER[i+1]=='E'&&
		RX0_BUFFER[i+2]=='N'&&RX0_BUFFER[i+3]=='D')  // check "ERROR" if true reinit tcplistenmode
		{
          		MODULE_MODE=1;//*INIT mode
	  		memset(RX0_BUFFER,0,sizeof(RX0_BUFFER)-1);
		}
		
		
		if(RX0_BUFFER[i]=='>')
		{
			R_UART0_Send(RX1_BUFFER,data_length);
			MODULE_MODE=1;
	                METER_DATA=1;
	                DATA_RECIEVEING=0;
	                RX1_BUFFER_COUNT=0;
			memset(RX0_BUFFER,0,sizeof(RX0_BUFFER));
		}
//		if(RX0_BUFFER[i]=='S'&&RX0_BUFFER[i+1]=='E'&&
//		RX0_BUFFER[i+2]=='N'&&RX0_BUFFER[i+3]=='D') 
//		{
		   
//		}
		
		
    	}
    	if(RECIEVED==1)
    	{
	 	for(i=data_intex;i<=RX0_BUFFER_COUNT;i++)
	  	{
			if((RX0_BUFFER[i]=='\n')&&(RECIEVED!=2))
			{
	         		RECIEVED=2;
				i++;
			}
		        if(RECIEVED==2)
			{
	  			TEMP_BUFFER[temp_index]=RX0_BUFFER[i];//storing data to temp buffer
	  			temp_index++;
			}
	  	}
           	TEMP_BUFFER[temp_index]='\0';
           	RECIEVED=0;
	   	memset(RX0_BUFFER,0,sizeof(RX0_BUFFER));
	   	data_intex=0;
	  	//temp_index=0;
     	}
	
}

/*-------------------------------------------------------------------------------------------------------------------/
* Function Name: WAIT_RECEPTION_TO_COMPLETE
* Description  : This function wait until data reception complete
* Arguments    : none
* Return Value :return  1
--------------------------------------------------------------------------------------------------------------------*/
uint8_t WAIT_RECEPTION_TO_COMPLETE(void)
{
	
	R_TAU0_Channel0_Start();
	return 1;
	
}
void TURN_ON_MODULE(void)
{
	P7&=~(1<<2);     //MODULE RESET
    	P7|=(1<<1);      //MODULE ON
    	P7 |=(1<<3);     //POWERKEY ON
    	__delay_ms(1000);//2S delay between POWERKEY ON&POWERKEY OFF 
    	__delay_ms(1000);
     	P7&=~(1<<3); //POWERKEY OFF
    	__delay_ms(500);
}
//void CHECK_MODULE_STATUS(uint8_t *RESPONSE)
//{
//	switch(AT_COMMAND_COUNT)
//        {
//		case 0:
//			COMPARE_MATCH1=Check_QISTATE(RESPONSE);
//			AT_COMMAND_COUNT++;
//			R_UART0_Send(THIRTY_SECONDS_CHECKS[AT_COMMAND_COUNT], strlen(THIRTY_SECONDS_CHECKS[AT_COMMAND_COUNT]));    
//			break;
//		case 1:
//			COMPARE_MATCH1=Check_Signal_Quality(RESPONSE); //
//			AT_COMMAND_COUNT++;
//			R_UART0_Send(THIRTY_SECONDS_CHECKS[AT_COMMAND_COUNT], strlen(THIRTY_SECONDS_CHECKS[AT_COMMAND_COUNT])); 
//			break;
//		case 2:
//			COMPARE_MATCH1=Check_Network_Reg_status(RESPONSE);
//			AT_COMMAND_COUNT=0;
//			if(COMPARE_MATCH1==1)
//			{
//			MODULE_MODE=TCP_MODE;
//			DATA_RECIEVED=0;
//			AT_COMMAND_COUNT=0;
//			}
//			break;
//	}
//	RX0_BUFFER_COUNT=0;
	
//	if(COMPARE_MATCH1==0)
//	{
//		AT_COMMAND_COUNT=0;
//		MODULE_MODE=INIT_MODE;
//		R_UART0_Send(TCP_CLOSE, strlen(TCP_CLOSE));
//		DATA_RECIEVED=1;
//	}

//}
static void R_MAIN_UserInit(void)
{
        READ_RESF=RESF;    //reset flag register
    	EI();
    	R_UART0_Start();
    	R_UART1_Start();
}
void Check_QIstate(void)
{
	if(DATA_RECIEVED==1)
	{
		if(WAIT_COUNT==0)
		{
			WAIT_COUNT=1;
			WAIT_RECEPTION_TO_COMPLETE();
		}
		if(WAIT_COUNT>=MODULE_INIT_TIME)
		{
			WAIT_COUNT=0;
			R_UART0_Send(QISTATE,sizeof(QISTATE));
			COMPARE_MATCH1=Check_QISTATE(RX0_BUFFER);
			if(COMPARE_MATCH1==1)
			{
			  R_UART0_Send(TCP_CLOSE,sizeof(TCP_CLOSE));
			}
			else if(COMPARE_MATCH1==0)
			{
				MODULE_MODE=0;
				DATA_RECIEVED=1;
			}
		}
		
	}
	
}

uint16_t calculate_data_length(void)
{
	uint16_t l=0;
	for(l=0;RX1_BUFFER[l]<sizeof(RX1_BUFFER)-1;l++)
	{
		if(RX1_BUFFER[l]==0&&RX1_BUFFER[l+1]==0&&
		   RX1_BUFFER[l+2]==0&&RX1_BUFFER[l+3]==0&&
		   RX1_BUFFER[l+4]==0&&RX1_BUFFER[l+5]==0&&
		   RX1_BUFFER[l+6]==0&&RX1_BUFFER[l+7]==0&&
		   RX1_BUFFER[l+8]==0&&RX1_BUFFER[l+9]==0&&
		   RX1_BUFFER[l+10]==0)
		{
		  	return l;
			
		}
	}
	return l;
}
void Network_Check_Activity(void)
{
                if( DATA_RECIEVED==0)
			 DATA_RECIEVEING=0;
				
		if(SECONDS_30&&DATA_RECIEVED==0&&DATA_RECIEVEING==0)
		{
		   	MODULE_MODE=CHECK_MODE;
		   	DATA_RECIEVED=1;
		}
		
		
		if(MODULE_MODE==CHECK_MODE)
		{
			Check_QIstate();
			DATA_RECIEVED=1;
		}	
}
