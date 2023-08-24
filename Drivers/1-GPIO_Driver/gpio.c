 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: Source file for the ARM GPIO driver
 *
 * Author: Mohamed Sayed Shaaban
 *
 *******************************************************************************/

#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "tm4c123gh6pm.h"

uint32_t delay;              //dump variable



/* Function_Name : GPIO_initPort
 * Description :
 * Initialize the Port to run as GPIO
 * 
 */
void GPIO_initPort(uint8 port_num){
	switch(port_num){
		case PORTA_ID:
		   SYSCTL_RCGCGPIO_R |= 0x01;      //enable clock for port A pins
	     delay =1;
		   GPIO_PORTA_LOCK_R = 0x4C4F434B;        //to enable you to write in this port
		   GPIO_PORTA_DEN_R = 0xFF;            //enables digital pins
		   GPIO_PORTA_CR_R = 0x1F;
		   GPIO_PORTA_AMSEL_R = 0;              //no analog
		   GPIO_PORTA_AFSEL_R = 0;              //1 means this port is I/O PORT  alternate function(uart,)
		   GPIO_PORTA_PCTL_R = 0;               //port control
		   break;
        case PORTB_ID:
		   SYSCTL_RCGCGPIO_R |= 0x02;      //enable clock for port A pins
	       delay =1;
		   GPIO_PORTB_LOCK_R = 0x4C4F434B;        //to enable you to write in this port
		   GPIO_PORTB_DEN_R = 0xFF;            //enables digital pins
		   GPIO_PORTB_CR_R = 0x1F;
		   GPIO_PORTB_AMSEL_R = 0;              //no analog
		   GPIO_PORTB_PCTL_R = 0;               //port control
		   GPIO_PORTB_AFSEL_R = 0;              //0 means this port is I/O PORT Not alternate function(uart,)
		   break;
		case PORTC_ID:
		   SYSCTL_RCGCGPIO_R |= 0x04;      //enable clock for port A pins
		   delay =1;
		   GPIO_PORTB_LOCK_R = 0x4C4F434B;
		   GPIO_PORTC_DEN_R = 0xFF;            //enables digital pins
		   GPIO_PORTC_CR_R = 0x1F;
		   GPIO_PORTC_AMSEL_R = 0;              //no analog
		   GPIO_PORTC_PCTL_R = 0;               //port control
		   GPIO_PORTC_AFSEL_R = 0;	
           break;
		case PORTD_ID:
		   SYSCTL_RCGCGPIO_R |= 0x08;      //enable clock for port A pins
		   delay =1;
		   GPIO_PORTD_LOCK_R = 0x4C4F434B;
		   GPIO_PORTD_DEN_R = 0xFF;            //enables digital pins
		   GPIO_PORTD_CR_R = 0x1F;
		   GPIO_PORTD_AMSEL_R = 0;              //no analog
		   GPIO_PORTD_PCTL_R = 0;               //port control
		   GPIO_PORTD_AFSEL_R = 0;
           break;
		case PORTE_ID:
		   SYSCTL_RCGCGPIO_R |= 0x10;      //enable clock for port A pins
		   delay =1;
		   GPIO_PORTE_LOCK_R = 0x4C4F434B;
		   GPIO_PORTE_DEN_R = 0xFF;            //enables digital pins
		   GPIO_PORTE_CR_R = 0x1F;
		   GPIO_PORTE_AMSEL_R = 0;              //no analog
		   GPIO_PORTE_PCTL_R = 0;               //port control
		   GPIO_PORTE_AFSEL_R = 0; 
       break;
    case PORTF_ID:
			SYSCTL_RCGCGPIO_R |= 0x00000020;  // 1) activate clock for Port F
			delay = SYSCTL_RCGCGPIO_R;        // allow time for clock to start
			GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
			GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
			// only PF0 needs to be unlocked, other bits can't be locked
			GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
			GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
			GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
			GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
			GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
			GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0
            break;		   
		
	}
	
	
	
}


/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin direction as required */
		switch(port_num)
		{
		case PORTA_ID:	
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTA_DIR_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTA_DIR_R,pin_num);
			}
			break;
		case PORTB_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTB_DIR_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTB_DIR_R,pin_num);
			}
			break;
		case PORTC_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTC_DIR_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTC_DIR_R,pin_num);
			}
			break;
		case PORTD_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTD_DIR_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTD_DIR_R,pin_num);
			}
			break;

		case PORTE_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTE_DIR_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTE_DIR_R,pin_num);
			}
			break;
		case PORTF_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTF_DIR_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTF_DIR_R,pin_num);
			}
			break;
		}
	}
}

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Write the pin value as required */
		switch(port_num)
		{
		case PORTA_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTA_DATA_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTA_DATA_R,pin_num);
			}
			break;
		case PORTB_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTB_DATA_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTB_DATA_R,pin_num);
			}
			break;
		case PORTC_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTC_DATA_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTC_DATA_R,pin_num);
			}
			break;
		case PORTD_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTD_DATA_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTD_DATA_R,pin_num);
			}
			break;
		case PORTE_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTE_DATA_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTE_DATA_R,pin_num);
			}
			break;
		case PORTF_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTF_DATA_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTF_DATA_R,pin_num);
			}
			break;
		}
	}
}

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	uint8 pin_value = LOGIC_LOW;

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the pin value as required */
		switch(port_num)
		{
		case PORTA_ID:
			if(BIT_IS_SET(GPIO_PORTA_DATA_R,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORTB_ID:
			if(BIT_IS_SET(GPIO_PORTB_DATA_R,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORTC_ID:
			if(BIT_IS_SET(GPIO_PORTC_DATA_R,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORTD_ID:
			if(BIT_IS_SET(GPIO_PORTA_DATA_R,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORTE_ID:
			if(BIT_IS_SET(GPIO_PORTA_DATA_R,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORTF_ID:
			if(BIT_IS_SET(GPIO_PORTF_DATA_R,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		}
	}

	return pin_value;
}

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the port direction as required */
		switch(port_num)
		{
		case PORTA_ID:
			GPIO_PORTA_DIR_R = direction;
			break;
		case PORTB_ID:
			GPIO_PORTB_DIR_R = direction;
			break;
		case PORTC_ID:
			GPIO_PORTC_DIR_R = direction;
			break;
		case PORTD_ID:
			GPIO_PORTD_DIR_R = direction;
			break;
		case PORTE_ID:
			GPIO_PORTE_DIR_R = direction;
			break;
		case PORTF_ID:
			GPIO_PORTF_DIR_R = direction;
			break;
		}
	}
}

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Write the port value as required */
		switch(port_num)
		{
		case PORTA_ID:
			GPIO_PORTA_DATA_R = value;
			break;
		case PORTB_ID:
			GPIO_PORTB_DATA_R = value;
			break;
		case PORTC_ID:
			GPIO_PORTC_DATA_R = value;
			break;
		case PORTD_ID:
			GPIO_PORTD_DATA_R = value;
			break;
		case PORTE_ID:
			GPIO_PORTE_DATA_R = value;
			break;
		case PORTF_ID:
			GPIO_PORTF_DATA_R = value;
			break;
		}
	}
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num)
{
	uint8 value = LOGIC_LOW;

	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the port value as required */
		switch(port_num)
		{
		case PORTA_ID:
			value = GPIO_PORTA_DATA_R;
			break;
		case PORTB_ID:
			value = GPIO_PORTB_DATA_R;
			break;
		case PORTC_ID:
			value = GPIO_PORTC_DATA_R;
			break;
		case PORTD_ID:
			value = GPIO_PORTD_DATA_R;
			break;
		case PORTE_ID:
			value = GPIO_PORTE_DATA_R;
			break;
		case PORTF_ID:
			value = GPIO_PORTF_DATA_R;
			break;
		}
	}

	return value;
}
