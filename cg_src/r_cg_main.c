/*--------------------------------------------------------------------------------------------------------/
FIRWARE VERSION: MOD_FW_V1
OWNER          : JIJIL SADANANDAN
date           : sept 2024 
----------------------------------------------------------------------------------------------------------*/

   /*header files
   --------------*/
   
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

  /*global variables*/
  
uint8_t TCP_CLOSE[]="AT+QICLOSE=1\r";
uint8_t TEMP_BUFFER[512];
uint8_t RECIEVED=0;
uint8_t RECIEVED_TCP=0;
long int TIMER_COUNT;
long int TIMER1_COUNT;
extern uint8_t COMPARE_MATCH1=0;
extern uint8_t TCP_INIT_STATUS;
uint8_t at_command[30];
uint8_t BUF_FLAG=0;
uint8_t AT_COMMAND_COUNT=0;
uint8_t MODULE_MODE=0;
uint8_t TCP_DATA_PROCESSED=0;
uint8_t TCP_DATA=0;
uint8_t buffer_Count;
unsigned long int WAIT_COUNT=0;

 /*FUNCTION DECLARATION*/
 
void Initialize_Module(void);
static void R_MAIN_UserInit(void);
void FETCH_METERDATA_AND_SEND(void);
extern void __delay_ms(unsigned int milliseconds);
uint8_t INIT_MODULE_TO_TCP_LISTENMODE(void);
uint8_t CHECK_MODULE_RESPONSE(uint8_t *RESPONSE);
void generate_at_command(uint8_t connection_id, uint8_t frame_size);
uint8_t WAIT_RECEPTION_TO_COMPLETE(void);
void FETCH_TCP_DATA(void) ;




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
	READ_RESF=RESF;    //reset flag register
    	R_MAIN_UserInit();
    	R_UART0_Start();
    	R_UART1_Start();
  
    	P7&=~(1<<2);     //MODULE RESET
    	P7|=(1<<1);      //MODULE ON
    	P7 |=(1<<3);     //POWERKEY ON
    	__delay_ms(1000);//2S delay between POWERKEY ON&POWERKEY OFF 
    	__delay_ms(1000);//POWERKEY OFF
     	P7&=~(1<<3);
    	__delay_ms(500);
	while (1U)
    	{
    		R_WDT_Restart();
		if(MODULE_MODE==INIT_MODE&&DATA_RECIEVED==1)
		{       
		/*INIT MODE*/
			WAIT_RECEPTION_TO_COMPLETE();
			if(WAIT_COUNT>300000)
				{
		         	WAIT_COUNT=0;
		         	TCP_INIT_STATUS= INIT_MODULE_TO_TCP_LISTENMODE();
				}
		}
	   
     
        	if(MODULE_MODE==TCP_MODE)
		{	
		/*TCP LISTNER MODE*/  
			if(DATA_RECIEVED == 1) //ENSURE DATA IS RECIVED
                	{
		        	WAIT_RECEPTION_TO_COMPLETE();	
				if(WAIT_COUNT>300000)
				{
			   		DATA_RECIEVED=0;
					WAIT_COUNT=0;
               				if(METER_DATA==1&&TCP_DATA==0)
	      	        		{
				 	/*data recieved over meter*/
						FETCH_METERDATA_AND_SEND();
						METER_DATA=4;
				
	       				}
	       				else if(METER_DATA==0&&TCP_DATA==1)
	       				{
	        		      	/**data recieved over TCP**/
                				DATA_RECIEVED=0;
						RX0_BUFFER[RX0_BUFFER_COUNT]='\0';
						FETCH_TCP_DATA(); //extract data 
	       		         	
	       					if(RECIEVED_TCP==1)
	       					{
						/*valid data with length*/
		    					RECIEVED_TCP=0;
	             					R_UART1_Send(TEMP_BUFFER, strlen(TEMP_BUFFER)-2);
							for(buffer_Count=0;buffer_Count<=512;buffer_Count++)//Clear buffer
							RX1_BUFFER[buffer_Count]=0;
							RX0_BUFFER_COUNT=0;
	      					}
		
		
	       			 	}
			}
			
	       	}//if data recievd end

	    
	
	}//if tcp mode end
	
        ;
	
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
        	DATA_RECIEVED = 0; // Reset flag
        	memset(RX0_BUFFER, 0, 200); // Clear buffer
        	RX0_BUFFER_COUNT = 0; // Reset buffer count

        	if (AT_COMMAND_COUNT<=22) 
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
/*-------------------------------------------------------------------------------------------------------------------/
* Function Name: FETCH_METERDATA_AND_SEND
* Description  : This function sends data recieved from meter over tcp
* Arguments    : None
* Return Value :none
--------------------------------------------------------------------------------------------------------------------*/
void FETCH_METERDATA_AND_SEND(void)
{
        uint8_t data_length=0;
	DATA_RECIEVED=0;
	METER_DATA=0;
	RX1_BUFFER[RX1_BUFFER_COUNT]='\0';
	data_length=RX1_BUFFER_COUNT;
	sprintf(at_command, "AT+QISEND=%u,%u\r\n", 11,data_length);//CREATE AT COMMAND FOR SEND over TCP
	R_UART0_Send(at_command, strlen(at_command));
	__delay_ms(100);
	R_UART0_Send(RX1_BUFFER, data_length);
	MODULE_MODE=1;
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
    	int temp_index=0;
    	int data_intex=0;
    	memset(TEMP_BUFFER,0,sizeof(TEMP_BUFFER));
    	for(i=0;i<500;i++)
    	{
		if(RX0_BUFFER[i]=='r'&&RX0_BUFFER[i+1]=='e'&&
		RX0_BUFFER[i+2]=='c'&&RX0_BUFFER[i+3]=='v')  //check wheather the data is recieved
		{
          		RECIEVED_TCP=1;
	  		RECIEVED=1;
	  		data_intex=i;
	  		break;
		}
		if(RX0_BUFFER[i]=='f'&&RX0_BUFFER[i+1]=='u'&&
		RX0_BUFFER[i+2]=='l'&&RX0_BUFFER[i+3]=='l')  // check "incoming full" if true 
		{
          		MODULE_MODE=0;//*INIT mode
	  		AT_COMMAND_COUNT=21;//at command_count for listen mode
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
	  			TEMP_BUFFER[temp_index]=RX0_BUFFER[i];//storing data to temp buffer
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
/*-------------------------------------------------------------------------------------------------------------------/
* Function Name: CHECK_MODULE_RESPONSE
* Description  : This function checks the response is matching as expected from the module
* Arguments    : response
* Return Value :return 0 or 1
--------------------------------------------------------------------------------------------------------------------*/
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
/*-------------------------------------------------------------------------------------------------------------------/
* Function Name: WAIT_RECEPTION_TO_COMPLETE
* Description  : This function wait until data reception complete
* Arguments    : none
* Return Value :return  1
--------------------------------------------------------------------------------------------------------------------*/
uint8_t WAIT_RECEPTION_TO_COMPLETE()
{
	
	WAIT_COUNT++;

	return 1;
	
}
static void R_MAIN_UserInit(void)
{
   
    EI();
   
}

