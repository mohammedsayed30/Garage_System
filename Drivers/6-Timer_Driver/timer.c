 /******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.c
 *
 * Description: Source file for the ARM Timer driver
 *
 * Author: Mohamed Sayed Shaaban
 *
 * Date: 13 / 8 /2023
 *******************************************************************************/
 
 /*****************************************************************************************************************************************
                                                      Includes
 *****************************************************************************************************************************************/
 
#include "timer.h"
#include "gpio.h"
#include "tm4c123gh6pm.h"
#include "common_macros.h"

/************************************************************
 *                  Global Variables
 ***********************************************************/
/* Global variables to hold the address of the
 * call back function in the application
 */
static volatile void (*g_callBackPtr)(void) =NULL_PTR;
/*****************************************************************************************************************************************
                                                    Functions_Prototypes   
*****************************************************************************************************************************************/

/*
*Function_Name : ISR
*
*Description : this Function will execute when the time is out for only timer 0
*/
void TIMER0A_Handler(void){
	TIMER0_ICR_R = TIMER_ICR_TATOCINT;
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)();
	}

}	
 
 
 
 
/*
*Function_Name : timerInit 
*
*Description : this to initialize the timer to start count with the required mode
*/

void timerInit(uint8 timer_num, uint32_t count){
	uint32_t delay;
	switch(timer_num){
		case 0 :
		SET_BIT(SYSCTL_RCGCTIMER_R ,timer_num);  //enable the clock to timer0
		delay =1;
		CLEAR_BIT(TIMER0_CTL_R,0);         //disable the timer0 A    
		TIMER0_CFG_R = 0;                //use 32bit timer
		SET_BIT(TIMER0_TAMR_R,1);            //periodic Mode bit 0
		CLEAR_BIT(TIMER0_TAMR_R,0);          //periodic Mode bit 1
		CLEAR_BIT(TIMER0_TAMR_R,4);          //count down
		TIMER0_TAILR_R = count;        //load the count value 
		TIMER0_TAPR_R = 0;
		SET_BIT(TIMER0_ICR_R,0);             //clear the flag
		SET_BIT(TIMER0_IMR_R,0);         //to enable interrupts
		SET_BIT(NVIC_EN0_R,19);             //enable IQR
		SET_BIT(TIMER0_CTL_R,0);          //enable the timer0 A to start count
		break;
		case 1:
		SET_BIT(SYSCTL_RCGCTIMER_R ,timer_num);  //enable the clock to timer0
		delay =1;
		CLEAR_BIT(TIMER1_CTL_R,0);         //disable the timer0 A    
		TIMER1_CFG_R = 0;                //use 32bit timer
		SET_BIT(TIMER1_TAMR_R,1);            //periodic Mode bit 0
		CLEAR_BIT(TIMER0_TAMR_R,0);          //periodic Mode bit 1
		CLEAR_BIT(TIMER0_TAMR_R,4);          //count down
		TIMER1_TAILR_R = count;        //load the count value 
		TIMER1_TAPR_R = 0;
		SET_BIT(TIMER1_ICR_R,0);             //clear the flag
		SET_BIT(TIMER1_IMR_R,0);         //to enable interrupts
		SET_BIT(NVIC_EN0_R,21);             //enable IQR
		SET_BIT(TIMER1_CTL_R,0);          //enable the timer0 A to start count
		break;
		case 2:
		SET_BIT(SYSCTL_RCGCTIMER_R ,timer_num);  //enable the clock to timer0
		delay =1;
		CLEAR_BIT(TIMER2_CTL_R,0);         //disable the timer0 A    
		TIMER2_CFG_R = 0;                //use 32bit timer
		SET_BIT(TIMER2_TAMR_R,1);            //periodic Mode bit 0
		CLEAR_BIT(TIMER2_TAMR_R,0);          //periodic Mode bit 1
		CLEAR_BIT(TIMER2_TAMR_R,4);          //count down
		TIMER2_TAILR_R = count;        //load the count value 
		TIMER2_TAPR_R = 0;
		SET_BIT(TIMER2_ICR_R,0);             //clear the flag
		SET_BIT(TIMER2_IMR_R,0);         //to enable interrupts
		SET_BIT(NVIC_EN0_R,23);             //enable IQR
		SET_BIT(TIMER2_CTL_R,0);          //enable the timer0 A to start count
		break;
		case 3:
		SET_BIT(SYSCTL_RCGCTIMER_R ,timer_num);  //enable the clock to timer0
		delay =1;
		CLEAR_BIT(TIMER3_CTL_R,0);         //disable the timer0 A    
		TIMER3_CFG_R = 0;                //use 32bit timer
		SET_BIT(TIMER3_TAMR_R,1);            //periodic Mode bit 0
		CLEAR_BIT(TIMER3_TAMR_R,0);          //periodic Mode bit 1
		CLEAR_BIT(TIMER3_TAMR_R,4);          //count down
		TIMER3_TAILR_R = count;        //load the count value 
		TIMER3_TAPR_R = 0;
		SET_BIT(TIMER3_ICR_R,0);             //clear the flag
		SET_BIT(TIMER3_IMR_R,0);         //to enable interrupts
		SET_BIT(NVIC_EN1_R,3);             //enable IQR
		SET_BIT(TIMER3_CTL_R,0);          //enable the timer0 A to start count
		break;
		case 4:
		SET_BIT(SYSCTL_RCGCTIMER_R ,timer_num);  //enable the clock to timer0
		delay =1;
		CLEAR_BIT(TIMER4_CTL_R,0);         //disable the timer0 A    
		TIMER4_CFG_R = 0;                //use 32bit timer
		SET_BIT(TIMER4_TAMR_R,1);            //periodic Mode bit 0
		CLEAR_BIT(TIMER4_TAMR_R,0);          //periodic Mode bit 1
		CLEAR_BIT(TIMER4_TAMR_R,4);          //count down
		TIMER4_TAILR_R = count;        //load the count value 
		TIMER4_TAPR_R = 0;
		SET_BIT(TIMER4_ICR_R,0);             //clear the flag
		SET_BIT(TIMER4_IMR_R,0);         //to enable interrupts
		SET_BIT(NVIC_EN0_R,5);             //enable IQR
		SET_BIT(TIMER4_CTL_R,0);          //enable the timer0 A to start count 
		break;
		case 5:
		SET_BIT(SYSCTL_RCGCTIMER_R ,timer_num);  //enable the clock to timer0
		delay =1;
		CLEAR_BIT(TIMER0_CTL_R,0);         //disable the timer0 A    
		TIMER5_CFG_R = 0;                //use 32bit timer
		SET_BIT(TIMER5_TAMR_R,1);            //periodic Mode bit 0
		CLEAR_BIT(TIMER5_TAMR_R,0);          //periodic Mode bit 1
		CLEAR_BIT(TIMER5_TAMR_R,4);          //count down
		TIMER5_TAILR_R = count;        //load the count value 
		TIMER5_TAPR_R = 0;
		SET_BIT(TIMER5_ICR_R,0);             //clear the flag
		SET_BIT(TIMER5_IMR_R,0);         //to enable interrupts
		SET_BIT(NVIC_EN0_R,7);             //enable IQR
		SET_BIT(TIMER5_CTL_R,0);          //enable the timer0 A to start count 
		break;			
	}	
}





/*
*Function_Name : timerdeInit 
*
*Description : this to disable  the timer from count
*/

void timerdeInit(uint8 timer_num){
	switch(timer_num){
		case 0 :
		CLEAR_BIT(TIMER0_CTL_R,0);         //disable the timer0 A
        CLEAR_BIT(TIMER0_CTL_R,8);         //disable the timer0 B    
		case 1:
		CLEAR_BIT(TIMER1_CTL_R,0);         //disable the timer0 A
        CLEAR_BIT(TIMER1_CTL_R,8);         //disable the timer0 B     
		break;
		case 2:
		CLEAR_BIT(TIMER2_CTL_R,0);         //disable the timer0 A
        CLEAR_BIT(TIMER2_CTL_R,8);         //disable the timer0 B     
		break;
		case 3:
		CLEAR_BIT(TIMER3_CTL_R,0);         //disable the timer0 A
        CLEAR_BIT(TIMER3_CTL_R,8);         //disable the timer0 B    
		case 4:
		CLEAR_BIT(TIMER4_CTL_R,0);         //disable the timer0 A
        CLEAR_BIT(TIMER4_CTL_R,8);         //disable the timer0 B     
		break;
		case 5:
		CLEAR_BIT(TIMER5_CTL_R,0);         //disable the timer0 A
        CLEAR_BIT(TIMER5_CTL_R,8);         //disable the timer0 B    			
	}	
}

/*
 * Function_Name:Timer1_setCallBack
 *
 * Description:
 *
 * to set the address of call back function the response
 * for handling the code of ISR
 */
void Timer_setCallBack(void(*a_ptr)(void)){
	/*
	 * set the address of the
	 * call back function in the application
	 */
	g_callBackPtr = a_ptr;
}