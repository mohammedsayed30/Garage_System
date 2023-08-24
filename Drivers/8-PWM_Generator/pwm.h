 /******************************************************************************
 *
 * Module: PWM_Model_0
 *
 * File Name: pwm.h
 *
 * Description: Header file for the ARM pwm model 0 generator driver
 *
 * Author: Mohamed Sayed Shaaban
 *
 * Date : 24/8/2023
 *******************************************************************************/

#include "std_types.h"
/*
*Fumction_Name : PWM_Init
*
*Description : Initalize PWM Module 0 to connect the servo on PB6 Pin
*/
void PWM_Init(void);
 
 
/*
*Fumction_Name : Servo_SetAngle
*
*Description : Set the Required angle for Servo Motor
*/
void Servo_SetAngle(uint16);