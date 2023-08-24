/*****************************************************************************************************************************************************

MODEL         : Source File For Systick Timer Driver

File Name     : systick_timer.c

Author        : Mohammed Sayed 

Date Creation : 8/5/2023

*******************************************************************************************************************************************************/



/*********************************************************************************************************************************************
                                                     Files Include
**********************************************************************************************************************************************/

#include "systick_timer.h"     //to use the prototypes of Functions
#include "gpio.h"             //to use the GPIO driver to write and read from Timer's registers
#include "tm4c123gh6pm.h"     //to use the definition of Registers of this timer
#include "std_types.h"
#include "common_macros.h"
/*********************************************************************************************************************************************
                                                     Functions_Definitions
**********************************************************************************************************************************************/

/*
**Function_Name : systicktimerDelay
**
**Description : to use as delay for 0 ms - 1000 millisecond
*/

void systicktimerDelay(uint32_t delay_ms){
	NVIC_ST_CTRL_R |=(1<<2);                 //using System clock
	NVIC_ST_CTRL_R &=~(1<<1);               //disable the Interrupt
	NVIC_ST_CTRL_R |=(1<<0);              //Enable the systick_timer to operate
  NVIC_ST_RELOAD_R = delay_ms * 16000;  //to convert to counts (16000000 = 1 second) with 16 MHZ	
	while((BIT_IS_SET(NVIC_ST_CTRL_R,16)==0));        //waiting until the counter reach to zero
	NVIC_ST_CURRENT_R=0;                    //write any value to this register to clear count flag
}

/*
**Function_Name : systicktimerDelay
**
**Description : to use as delay for 0 ms - 1000 millisecond
*/

void systicktimerDelay_Double(uint32_t delay_ms){
	uint8 flag=1;           //used to break the while loop
	while(flag){
		
		if(delay_ms>1000){
		   delay_ms-=1000;
		   systicktimerDelay(1000);                 //equal one Second
		}
		else{
			systicktimerDelay(delay_ms);
			flag=0;	                      //to break the loop		
		}
		
	}
	NVIC_ST_CTRL_R &=~(1<<0);   //stop the counter after finishing the required delay
	
}
