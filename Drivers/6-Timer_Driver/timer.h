 /******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.h
 *
 * Description: header file for the ARM Timer driver
 *
 * Author: Mohamed Sayed Shaaban
 *
 * Date: 13 / 8 /2023
 *******************************************************************************/
 
 /*****************************************************************************************************************************************
                                                      Includes
 *****************************************************************************************************************************************/
 

#include "std_types.h"

/*****************************************************************************************************************************************
                                                    Functions_Prototypes   
*****************************************************************************************************************************************/
 
/*
*Function_Name : timerInit 
*
*Description : this to initialize the timer to start count
*/

void timerInit(uint8 , uint32_t);


/*
*Function_Name : timerdeInit 
*
*Description : this to disable  the timer from count
*/

void timerdeInit(uint8);

/*
 * Function_Name:Timer1_setCallBack
 *
 * Description:
 *
 * to set the address of call back function the response
 * for handling the code of ISR
 */
void Timer_setCallBack(void(*a_ptr)(void));