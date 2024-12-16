/*
 * LCD_program.c
 *
 *  Created on: Jul 19, 2023
 *      Author: top
 */

#include <util/delay.h>
#include "ErrorState.h"
#include "stdTypes.h"

#include "DIO_interface.h"

#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_configuration.h"

static void SendHalfDataPort(u8 Copy_u8Data)
{
	u8 Local_Au8DataPins[4]={LCD_DATA_PIN4,LCD_DATA_PIN5,LCD_DATA_PIN6,LCD_DATA_PIN7};
	u8 Local_u8Iterator ;

	for(Local_u8Iterator = 0 ; Local_u8Iterator < 4 ;Local_u8Iterator++ )
	{
		DIO_enuSetPinValue(LCD_DATA_GRP , Local_Au8DataPins[Local_u8Iterator],(Copy_u8Data >> Local_u8Iterator) & 1);
	}

}

static void SendEnablePulse()
{
	DIO_enuSetPinValue(LCD_EN_GRP,LCD_EN_PIN,DIO_HIGH_LEVEL);

	/* Wait */
	_delay_ms(2);

	DIO_enuSetPinValue(LCD_EN_GRP,LCD_EN_PIN,DIO_LOW_LEVEL);

}


ES_t LCD_enuSetAllDirection()
{
	ES_t Local_enuErrorState = ES_OK;

	/* Control Direction */
	DIO_enuSetPinDirection(LCD_RS_GRP,LCD_RS_PIN,DIO_OUTPUT);
	DIO_enuSetPinDirection(LCD_RW_GRP,LCD_RW_PIN,DIO_OUTPUT);
	DIO_enuSetPinDirection(LCD_EN_GRP,LCD_EN_PIN,DIO_OUTPUT);

	/* Data Direction */
#if LCD_MODE == LCD_EIGHT_BIT
	DIO_enuSetPortDirection(LCD_DATA_GRP,0xff);

#elif LCD_MODE == LCD_FOUR_BIT
	DIO_enuSetPinDirection(LCD_DATA_GRP,LCD_DATA_PIN4,DIO_OUTPUT);
	DIO_enuSetPinDirection(LCD_DATA_GRP,LCD_DATA_PIN5,DIO_OUTPUT);
	DIO_enuSetPinDirection(LCD_DATA_GRP,LCD_DATA_PIN6,DIO_OUTPUT);
	DIO_enuSetPinDirection(LCD_DATA_GRP,LCD_DATA_PIN7,DIO_OUTPUT);

#endif
	return Local_enuErrorState;
}

ES_t LCD_enuInit(void)
{
	ES_t Local_enuErrorState = ES_OK;

	LCD_enuSetAllDirection();

	/* Wait after VDD rises to 4.5V  */
	_delay_ms(40);

#if LCD_MODE == LCD_EIGHT_BIT

	/* Function Set */
	LCD_enuWriteCommand(0b00111000);

#elif LCD_MODE == LCD_FOUR_BIT

	/* Function Set */
	SendHalfDataPort(0b0010);
	SendEnablePulse();
	SendHalfDataPort(0b0010);
	SendEnablePulse();
	SendHalfDataPort(0b1100);
	SendEnablePulse();

#else
	Error : " The configuration is wrong "
#endif

	/* Display Control */
	LCD_enuWriteCommand(0b00001111);

	/* Display Clear */
	LCD_enuClear();



	return Local_enuErrorState;
}

ES_t LCD_enuWriteCommand(u8 Copy_u8Command)
{
	ES_t Local_enuErrorState = ES_OK;

	/* Set RS to zero for writing command */
	DIO_enuSetPinValue(LCD_RS_GRP,LCD_RS_PIN,DIO_LOW_LEVEL);

	/* Set RW to zero for writing */
	DIO_enuSetPinValue(LCD_RW_GRP,LCD_RW_PIN,DIO_LOW_LEVEL);

#if LCD_MODE == LCD_EIGHT_BIT

	/* Write command to data pins */
	DIO_enuSetPortValue(LCD_DATA_GRP,Copy_u8Command);

	/*Set enable pulse */
	SendEnablePulse();

#elif LCD_MODE == LCD_FOUR_BIT

	/* Write higher command to data pins */
	SendHalfDataPort(Copy_u8Command >> 4);

	/*Set enable pulse */
	SendEnablePulse();

	/* Write lower command to data pins */
	SendHalfDataPort(Copy_u8Command);

	/*Set enable pulse */
	SendEnablePulse();

#endif



	return Local_enuErrorState;


}

ES_t LCD_enuClear()
{
	ES_t Local_enuErrorState = ES_OK;

	LCD_enuWriteCommand(0b00000001);

	/* Wait */
	_delay_ms(2);

	return Local_enuErrorState;
}

ES_t LCD_enuWriteData(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState = ES_OK;

	/* Set RS to one for writing data */
	DIO_enuSetPinValue(LCD_RS_GRP,LCD_RS_PIN,DIO_HIGH_LEVEL);

	/* Set RW to zero for writing */
	DIO_enuSetPinValue(LCD_RW_GRP,LCD_RW_PIN,DIO_LOW_LEVEL);

#if LCD_MODE == LCD_EIGHT_BIT

	/* Write data to data pins */
	DIO_enuSetPortValue(LCD_DATA_GRP,Copy_u8Data);

	/*Set enable pulse */
	SendEnablePulse();

#elif LCD_MODE == LCD_FOUR_BIT

	/* Write higher data to data pins */
	SendHalfDataPort(Copy_u8Data >> 4);

	/*Set enable pulse */
	SendEnablePulse();

	/* Write lower data to data pins */
	SendHalfDataPort(Copy_u8Data);

	/*Set enable pulse */
	SendEnablePulse();

#endif

	return Local_enuErrorState;

}

ES_t LCD_enuWriteString(const char* Copy_pchString)
{
	ES_t Local_enuErrorState = ES_NOK;
	u8 Local_u8Counter = 0;

	if(Copy_pchString != NULL )
	{
		while(Copy_pchString[Local_u8Counter] != '\0')
		{
			LCD_enuWriteData(Copy_pchString[Local_u8Counter]);
			Local_u8Counter++;
		}
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t LCD_enuWriteIntegerNumber(s32 Copy_s32IntegerNumber)
{
	ES_t Local_enuErrorState = ES_OK;
	u32 Local_u32OppositedNumber = 0;
	u8 Local_u8CurrentDigit = 0;

	if(Copy_s32IntegerNumber < 0)
	{
		LCD_enuWriteData('-');
		Copy_s32IntegerNumber *= -1;
	}

	while(Copy_s32IntegerNumber != 0)
	{
		Local_u32OppositedNumber = Local_u32OppositedNumber * 10 +  Copy_s32IntegerNumber % 10 ;
		Copy_s32IntegerNumber /= 10;
	}

	do
	{
		Local_u8CurrentDigit = Local_u32OppositedNumber % 10;
		LCD_enuWriteData(Local_u8CurrentDigit + 48);
		Local_u32OppositedNumber /= 10;
	}while(Local_u32OppositedNumber != 0);


	return Local_enuErrorState;
}

ES_t LCD_enuWriteFloatNumber(f64 Copy_f64FloatNumber)
{
	ES_t Local_enuErrorState = ES_OK;
	u64 Local_u64IntegerNumber = 0;
	u8 Local_u8Decimal = 0;

	if(Copy_f64FloatNumber < 0)
	{
		LCD_enuWriteData('-');
		Copy_f64FloatNumber *= -1;
	}

	Local_u64IntegerNumber = Copy_f64FloatNumber;
	Local_u8Decimal = (Copy_f64FloatNumber - (f64)Local_u64IntegerNumber) * 100;

	LCD_enuWriteIntegerNumber(Local_u64IntegerNumber);
	LCD_enuWriteData('.');
	LCD_enuWriteIntegerNumber(Local_u8Decimal);

	return Local_enuErrorState;
}

ES_t LCD_enuReturnHome()
{
	ES_t Local_enuErrorState = ES_OK;

	LCD_enuWriteCommand(0b00000010);

	return Local_enuErrorState;
}

ES_t LCD_enuGoToXYPosition(u8 Copy_u8XPosition,u8 Copy_u8YPosition)
{
	ES_t Local_enuErrorState = ES_NOK;
	u8 Local_u8DDRAMAddress;

	if( Copy_u8YPosition == 0 || Copy_u8YPosition == 1)
	{

		Local_u8DDRAMAddress = Copy_u8XPosition + Copy_u8YPosition * 0x40 ;
		Local_u8DDRAMAddress = Local_u8DDRAMAddress | (LCD_BIT_MASK << 7 );
		LCD_enuWriteCommand(Local_u8DDRAMAddress);


		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

ES_t LCD_enuWriteSpecialCharacter(u8 Copy_Au8LetterArray[] ,u8 Copy_u8BlockNumber,u8 Copy_u8XPosition ,u8 Copy_u8YPosition)
{
	ES_t Local_enuErrorState = ES_NOK;
	u8 Local_u8CGRAMAddress;
	u8 Local_u8Iterator;

	/* Calculate the starting address in CGRAM */
	Local_u8CGRAMAddress = Copy_u8BlockNumber * LCD_u8BLOCKBYTES ;
	Local_u8CGRAMAddress = Local_u8CGRAMAddress | (LCD_BIT_MASK << 6 );
	//Local_u8CGRAMAddress = Local_u8CGRAMAddress & (~(LCD_BIT_MASK << 7 ));

	/* Set CGRAM address command */
	LCD_enuWriteCommand(Local_u8CGRAMAddress);

	/* Draw the pattern inside CGRAM */
	for(Local_u8Iterator = 0 ; Local_u8Iterator < 8 ; Local_u8Iterator ++)
	{
		LCD_enuWriteData(Copy_Au8LetterArray[Local_u8Iterator] );
	}

	/* Go back to DDRAM to display the pattern */
	LCD_enuGoToXYPosition(Copy_u8XPosition,Copy_u8YPosition);

	/* Display the drawn pattern */
	LCD_enuWriteData(Copy_u8BlockNumber);

	return Local_enuErrorState;
}

ES_t LCD_enuDeleteCharacter(u8 Copy_u8ShiftedNumber)
{
	ES_t Local_enuErrorState = ES_OK;

	for(u8 Local_u8Iterator = 0 ; Local_u8Iterator < Copy_u8ShiftedNumber ; Local_u8Iterator ++)
	{
		LCD_enuWriteCommand(0x10);
	}
	LCD_enuWriteData(' ');
	LCD_enuWriteCommand(0x10);

	return Local_enuErrorState;
}
