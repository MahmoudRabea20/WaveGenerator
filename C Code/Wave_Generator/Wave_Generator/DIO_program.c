/*
 * DIO_program.c
 *
 *  Created on: Jul 18, 2023
 *      Author: top
 */

#include "ErrorState.h"
#include "stdTypes.h"

#include "DIO_private.h"
#include "DIO_configuration.h"
#include "DIO_interface.h"


ES_t DIO_enuSetPinDirection(u8 Copy_u8GroupNumber,u8 Copy_u8PinNumber,u8 Copy_u8PinDirection)
{
	ES_t Local_enuErrorState = ES_NOK;

	if((Copy_u8GroupNumber <= DIO_GROUP_D && Copy_u8GroupNumber >= DIO_GROUP_A) && (Copy_u8PinNumber >= DIO_PIN_0 && Copy_u8PinNumber <= DIO_PIN_7) && (Copy_u8PinDirection == DIO_INPUT || Copy_u8PinDirection == DIO_OUTPUT))
	{
		switch(Copy_u8GroupNumber)
		{
		case DIO_GROUP_A:
			DDRA &= ~(DIO_BIT_MASK << Copy_u8PinNumber );
			DDRA |= (Copy_u8PinDirection << Copy_u8PinNumber );
			break;
		case DIO_GROUP_B:
			DDRB &= ~(DIO_BIT_MASK << Copy_u8PinNumber );
			DDRB |= (Copy_u8PinDirection << Copy_u8PinNumber );
			break;
		case DIO_GROUP_C:
			DDRC &= ~(DIO_BIT_MASK << Copy_u8PinNumber );
			DDRC |= (Copy_u8PinDirection << Copy_u8PinNumber );
			break;
		case DIO_GROUP_D:
			DDRD &= ~(DIO_BIT_MASK << Copy_u8PinNumber );
			DDRD |= (Copy_u8PinDirection << Copy_u8PinNumber );
			break;
		}
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

ES_t DIO_enuSetPinValue(u8 Copy_u8GroupNumber,u8 Copy_u8PinNumber,u8 Copy_u8PinValue)
{
	ES_t Local_enuErrorState = ES_NOK;

	if((Copy_u8GroupNumber <= DIO_GROUP_D && Copy_u8GroupNumber >= DIO_GROUP_A) && (Copy_u8PinNumber >= DIO_PIN_0 && Copy_u8PinNumber <= DIO_PIN_7) && (Copy_u8PinValue == DIO_LOW_LEVEL || Copy_u8PinValue == DIO_HIGH_LEVEL))
	{
		switch(Copy_u8GroupNumber)
		{
		case DIO_GROUP_A:
			PORTA &= ~(DIO_BIT_MASK << Copy_u8PinNumber );
			PORTA |= (Copy_u8PinValue << Copy_u8PinNumber );
			break;
		case DIO_GROUP_B:
			PORTB &= ~(DIO_BIT_MASK << Copy_u8PinNumber );
			PORTB |= (Copy_u8PinValue << Copy_u8PinNumber );
			break;
		case DIO_GROUP_C:
			PORTC &= ~(DIO_BIT_MASK << Copy_u8PinNumber );
			PORTC |= (Copy_u8PinValue << Copy_u8PinNumber );
			break;
		case DIO_GROUP_D:
			PORTD &= ~(DIO_BIT_MASK << Copy_u8PinNumber );
			PORTD |= (Copy_u8PinValue << Copy_u8PinNumber );
			break;
		}
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

ES_t DIO_enuSetPortDirection(u8 Copy_u8GroupNumber,u8 Copy_u8PortDirection)
{
	ES_t Local_enuErrorState = ES_NOK;

	if((Copy_u8GroupNumber <= DIO_GROUP_D && Copy_u8GroupNumber >= DIO_GROUP_A) && (Copy_u8PortDirection >= DIO_SMALLEST_PORT_DIRECTION && Copy_u8PortDirection <= DIO_LARGEST_PORT_DIRECTION))
	{
		switch(Copy_u8GroupNumber)
		{
		case DIO_GROUP_A:
			DDRA = Copy_u8PortDirection;
			break;
		case DIO_GROUP_B:
			DDRB = Copy_u8PortDirection;
			break;
		case DIO_GROUP_C:
			DDRC = Copy_u8PortDirection;
			break;
		case DIO_GROUP_D:
			DDRD = Copy_u8PortDirection;
			break;
		}
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

ES_t DIO_enuSetPortValue(u8 Copy_u8GroupNumber,u8 Copy_u8PortValue)
{
	ES_t Local_enuErrorState = ES_NOK;

	if((Copy_u8GroupNumber <= DIO_GROUP_D && Copy_u8GroupNumber >= DIO_GROUP_A) && (Copy_u8PortValue >= DIO_SMALLEST_PORT_VALUE && Copy_u8PortValue <= DIO_LARGEST_PORT_VALUE))
	{
		switch(Copy_u8GroupNumber)
		{
		case DIO_GROUP_A:
			PORTA = Copy_u8PortValue;
			break;
		case DIO_GROUP_B:
			PORTB = Copy_u8PortValue;
			break;
		case DIO_GROUP_C:
			PORTC = Copy_u8PortValue;
			break;
		case DIO_GROUP_D:
			PORTD = Copy_u8PortValue;
			break;
		}
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

ES_t DIO_enuTogglePinValue(u8 Copy_u8GroupNumber,u8 Copy_u8PinNumber)
{
	ES_t Local_enuErrorState = ES_NOK;

	if((Copy_u8GroupNumber <= DIO_GROUP_D && Copy_u8GroupNumber >= DIO_GROUP_A) && (Copy_u8PinNumber >= DIO_PIN_0 && Copy_u8PinNumber <= DIO_PIN_7))
	{
		switch(Copy_u8GroupNumber)
		{
		case DIO_GROUP_A:
			PORTA ^= (DIO_BIT_MASK << Copy_u8PinNumber );
			break;
		case DIO_GROUP_B:
			PORTB ^= (DIO_BIT_MASK << Copy_u8PinNumber );
			break;
		case DIO_GROUP_C:
			PORTC ^= (DIO_BIT_MASK << Copy_u8PinNumber );
			break;
		case DIO_GROUP_D:
			PORTD ^= (DIO_BIT_MASK << Copy_u8PinNumber );
			break;
		}
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

u8 DIO_u8GetPinValue(u8 Copy_u8GroupNumber,u8 Copy_u8PinNumber)
{
	u8 Local_u8PinValue = 0 ;

	if((Copy_u8GroupNumber <= DIO_GROUP_D && Copy_u8GroupNumber >= DIO_GROUP_A) && (Copy_u8PinNumber >= DIO_PIN_0 && Copy_u8PinNumber <= DIO_PIN_7))
	{
		switch(Copy_u8GroupNumber)
		{
		case DIO_GROUP_A:
			Local_u8PinValue = (PINA >> Copy_u8PinNumber) & DIO_BIT_MASK;
			break;
		case DIO_GROUP_B:
			Local_u8PinValue = (PINB >> Copy_u8PinNumber) & DIO_BIT_MASK;
			break;
		case DIO_GROUP_C:
			Local_u8PinValue = (PINC >> Copy_u8PinNumber) & DIO_BIT_MASK;
			break;
		case DIO_GROUP_D:
			Local_u8PinValue = (PIND >> Copy_u8PinNumber) & DIO_BIT_MASK;
			break;
		}
	}
	else
	{
		Local_u8PinValue = OUT_OF_RANGE;
	}

	return Local_u8PinValue;
}

u8 DIO_u8GetPortValue(u8 Copy_u8GroupNumber)
{
	u8 Local_u8PORTValue = 0;

	if((Copy_u8GroupNumber <= DIO_GROUP_D && Copy_u8GroupNumber >= DIO_GROUP_A))
	{
		switch(Copy_u8GroupNumber)
		{
		case DIO_GROUP_A:
			Local_u8PORTValue = PINA;
			break;
		case DIO_GROUP_B:
			Local_u8PORTValue = PINB;
			break;
		case DIO_GROUP_C:
			Local_u8PORTValue = PINC;
			break;
		case DIO_GROUP_D:
			Local_u8PORTValue = PIND;
			break;
		}
	}
	else
	{
		// change the value of out_of_range more than once as it may be equal to the value of PIN
		Local_u8PORTValue = OUT_OF_RANGE;
	}

	return Local_u8PORTValue;
}
