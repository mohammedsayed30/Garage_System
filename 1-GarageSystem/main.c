 /**********************************************************************************************************************************
 *
 * Module: Garage System
 *
 * File Name: main
 *
 * Description: Source file for the Garage System 
 *
 * Author: Mohamed Sayed Shaaban
 *
 * Date : 23/8/2023
 **********************************************************************************************************************************/
 
 /*********************************************************************************************************************************
                                              File Includes
 *********************************************************************************************************************************/
#include "gpio.h" 
#include "timer.h"               //to use timer for pwm
#include "LCD.h"                //to display the avaliable Parking or Not
#include "systick_timer.h"      //to use delay function
#include "pwm.h"                //to used pwm signal for servo
#include "std_types.h"
#include "tm4c123gh6pm.h"      //to use microcontroller's Registers 
 /*********************************************************************************************************************************
                                               defines
**********************************************************************************************************************************/
#define MAX_CARS_NUM                       10
#define TIMER1A                            1
#define CAR_SWITCH_PORT                    PORTF_ID
#define CAR_ENTER_SWITCH                   PIN0_ID            /*act as PIR sensor to sense that a car enter*/
#define CAR_EXIT_SWITCH                    PIN4_ID            /*act as PIR sensor to sense that a car exit*/
#define CAR_ENTER_LIGHT                    PIN1_ID            /*give light when a car enter*/
#define CAR_EXIT_LIGHT                     PIN2_ID            /*give light when a car exit*/
 
/*********************************************************************************************************************************
                                              global Variables & defines
*********************************************************************************************************************************/


uint8  car_nums = 0; 

/*********************************************************************************************************************************
                                              Application (Garage System)
*********************************************************************************************************************************/

/*
*Function : Turn the leds off after two second from entering or exitin a car
*
*This is The (Called Back Function) That called by timer handler
*/
void turn_leds_off(void){
	GPIO_writePin(CAR_SWITCH_PORT,CAR_ENTER_LIGHT,LOGIC_LOW);   //turn off the CAR_ENTER_LIGHT indicator
	GPIO_writePin(CAR_SWITCH_PORT,CAR_EXIT_LIGHT,LOGIC_LOW);    //turn off the CAR_EXIT_LIGHT indicator
	Servo_SetAngle(0);                                     //close the gate                              
}

int main(void)
{
	GPIO_initPort(PORTF_ID);     //For switches and leds
	GPIO_initPort(PORTD_ID);    //for LCD RS&EN Pins
	GPIO_initPort(PORTA_ID);   //for LCD
	Timer_setCallBack(turn_leds_off);  //set callBack function
	GPIO_setupPinDirection(CAR_SWITCH_PORT ,CAR_ENTER_SWITCH ,PIN_INPUT);    //setup switch0 as input pin
	GPIO_setupPinDirection(CAR_SWITCH_PORT ,CAR_EXIT_SWITCH ,PIN_INPUT);    //setup switch4 as input pin
	GPIO_setupPinDirection(CAR_SWITCH_PORT ,CAR_ENTER_LIGHT ,PIN_OUTPUT);   //setup LED1 as input pin
	GPIO_setupPinDirection(CAR_SWITCH_PORT ,CAR_EXIT_LIGHT ,PIN_OUTPUT);   //setup LED1 as input pin
	LCD_init();                                                            //initalize the LCD
	systicktimerDelay_Double(10);                                         //delay 20msec untile the LCD Initializes
	PWM_Init();                                    //inialize the servo motor(gate)
	Servo_SetAngle(0);               //to used pwm signal for servo                                                //zero degree              
	systicktimerDelay_Double(5);                                         //delay
	LCD_displayString("There is : 0 Cars");
	LCD_moveCursor(2,1);
	LCD_displayString("Garage has a Space");
	while(1){
		if(GPIO_readPin(CAR_SWITCH_PORT,CAR_ENTER_SWITCH) == 0 && car_nums < MAX_CARS_NUM ){
			//mean the button pressed (act as IPR Sensor detect a car
			car_nums++;          //increase the number of cars that exist in the garage
			GPIO_writePin(CAR_SWITCH_PORT,CAR_ENTER_LIGHT,LOGIC_HIGH);
			timerInit(0,24000000);       //after this time the CAR_ENTER_LIGHT will turn of
      Servo_SetAngle(90);			  //open the gate for 
			while(GPIO_readPin(CAR_SWITCH_PORT,CAR_ENTER_SWITCH) == 0);      //untile leave the switch
	  }
		if(GPIO_readPin(CAR_SWITCH_PORT,CAR_EXIT_SWITCH) == 0 && car_nums > 0 ){
			//mean the button pressed (act as IPR Sensor detect a car
			car_nums--;          //increase the number of cars that exist in the garage
			GPIO_writePin(CAR_SWITCH_PORT,CAR_EXIT_LIGHT,LOGIC_HIGH);
			timerInit(0,24000000);       //after this time the CAR_ENTER_LIGHT will turn of
      Servo_SetAngle(90);			  //open the gate for 
			while(GPIO_readPin(CAR_SWITCH_PORT,CAR_EXIT_SWITCH) == 0);      //untile leave the switch
	  }
		if(car_nums == MAX_CARS_NUM){                 //this mean the garage is FULL
				LCD_displayString("There is : 10 Cars");
				LCD_moveCursor(2,1);
				LCD_displayString("Garage Is FULL");
		}
		else{                            //there is a space for others Cars 
				LCD_displayString("There is : Cars");
			  LCD_moveCursor(1,11);
			  LCD_displayCharacter(car_nums+48); 
	      LCD_moveCursor(2,1);
	      LCD_displayString("Garage has a Space");
		}
  }
}


 
 
 
 