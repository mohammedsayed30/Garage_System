 /******************************************************************************
 *
 * Module: PWM_Model_0
 *
 * File Name: pwm.c
 *
 * Description: Source file for the ARM pwm model 0 generator driver
 *
 * Author: Mohamed Sayed Shaaban
 *
 *Date : 24/8/2023
 *******************************************************************************/
 
 
#include <stdint.h>
#include "pwm.h"
#include "tm4c123gh6pm.h"  // Include the TM4C123GH6PM microcontroller header file
/*
*Fumction_Name : PWM_Init
*
*Description : Initalize PWM Module 0 to connect the servo on PB6 Pin
*/
void PWM_Init(void)
{
	uint32_t delay;
    SYSCTL_RCGCPWM_R |= 0x01;       // Enable PWM Module 0 clock
    SYSCTL_RCGCGPIO_R |= 0x02;      // Enable GPIO Port B clock
    delay=1;
    GPIO_PORTB_AFSEL_R |= 0x40;     // Enable alternate function for PB6
    GPIO_PORTB_PCTL_R |= 0x04000000; // Configure PB6 as PWM0 output pin

    PWM0_CTL_R  = 0x00000000;        // Disable PWM0 Generator 0
    PWM0_0_GENA_R = 0x0000008C;     // Set PWM0 Generator 0, PWM output when counter matches comparator A
    PWM0_0_LOAD_R = 16000 - 1;      // Set PWM period (16 MHz / 16000 = 1 kHz)
    PWM0_0_CMPA_R = 14500 - 1;       // Set initial pulse width (Example: 1.5 ms for 90-degree position)

    PWM0_CTL_R |= 0x00000001;       // Enable PWM0 Generator 0
    PWM0_ENABLE_R |= 0x00000001;    // Enable PWM0 Output 0
}
/*
*Fumction_Name : Servo_SetAngle
*
*Description : Set the Required angle for Servo Motor
*/
void Servo_SetAngle(uint16 angle)
{
    uint16_t pulseWidth = (angle * 1600 / 180) + 400;  // Calculate pulse width based on the desired angle

    PWM0_0_CMPA_R = (16000-pulseWidth )- 1;  // Update the pulse width in the comparator A register
}

