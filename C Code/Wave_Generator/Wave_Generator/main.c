

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "BIT_MATH.h"
#include "ErrorState.h"
#include "stdTypes.h"

#include "UART_interface.h"
#include "DIO_interface.h"

#include "LCD_interface.h"

void SinWave(void);
void SquareWave(void);
void StaircaseWave(void);
void TriangularWave(void);
u8 Convert_To_Number(u8 Copy_u8Letter);

void main(void) {
	
	u8 Local_u8ReceivedData = 0;
	UART_enuInit();
	LCD_enuInit();
	DDRC=255;	
	DDRB=255;
	

	while(1)
	{
		
		UART_enuReceiveData(&Local_u8ReceivedData);

		switch(Local_u8ReceivedData)
		{
			case 'i':
			SinWave();
			break;
			case 'q':
			SquareWave();
			break;
			case 'r':
			TriangularWave();
			break;
			case 't':
			StaircaseWave();
			break;
			default:
			break;

		}

	}


	
	
}

void SinWave()
{
	
	float angle, value;
		u8 Local_u8FrequencyValue = 0;
		u8 Local_u8Amplitude =0;
		u8 Local_u8ReceivedData = 0;
		


		//Receive the Frequency of signal
		UART_enuReceiveData( &Local_u8ReceivedData );
		Local_u8FrequencyValue = Local_u8FrequencyValue * 10 + Convert_To_Number(Local_u8ReceivedData );
		UART_enuReceiveData( &Local_u8ReceivedData );
		Local_u8FrequencyValue = Local_u8FrequencyValue * 10 + Convert_To_Number(Local_u8ReceivedData );
		LCD_enuWriteIntegerNumber(Local_u8FrequencyValue);
		LCD_enuWriteString(" ");

		//Receive the Amplitude of the signal
		
		UART_enuReceiveData( &Local_u8ReceivedData );
		Local_u8Amplitude = Local_u8Amplitude * 10 + Convert_To_Number(Local_u8ReceivedData );
		LCD_enuWriteIntegerNumber(Local_u8Amplitude);
		
		
		u8 i=0;
		UART_enuSendData('<');
		while(i<2)
		{
			
			UART_enuSendData('3');
			UART_enuSendData(')');
			UART_enuSendData('.');
			UART_enuSendData('%');
			
			UART_enuSendData('s');
			UART_enuSendData('i');
			UART_enuSendData('n');
			UART_enuSendData('e');
			
			
			i++;
			
		}
	
	
	
	if(Local_u8Amplitude == 2)
	{
		while(1)
		{
			
			
			for (angle = 0; angle <= 360; angle += 10) {
				// Convert angle to radians
				float radianAngle = angle * M_PI / 180.0;

				// Calculate analog output value using the equation: Value = 5 + 5 * sin(angle)
				value = Local_u8Amplitude + Local_u8Amplitude * sin(radianAngle);

				// Map the analog value to the DAC resolution
				uint8_t dacValue = (uint8_t)(value * 255 / 10.0);

				// Output the analog value to DAC
				PORTC = dacValue;
				_delay_ms(99);
			}
		
		}
	
	}
	else 
	{
		while(1)
		{
			
			
			for (angle = 0; angle <= 360; angle += 10) {
				// Convert angle to radians
				float radianAngle = angle * M_PI / 180.0;

				// Calculate analog output value using the equation: Value = 5 + 5 * sin(angle)
				value = 5 + 5 * sin(radianAngle);

				// Map the analog value to the DAC resolution
				uint8_t dacValue = (uint8_t)(value * 255 / 10.0);

				// Output the analog value to DAC
				PORTC = dacValue;
				_delay_ms(11);
			}
			
		}
		
	}

		
	

}




void SquareWave()
{
	u8 Local_u8FrequencyValue = 0;
	u8 Local_u8Amplitude =0;
	u8 Local_u8ReceivedData = 0;
	


	//Receive the Frequency of signal
	UART_enuReceiveData( &Local_u8ReceivedData );
	Local_u8FrequencyValue = Local_u8FrequencyValue * 10 + Convert_To_Number(Local_u8ReceivedData );
	UART_enuReceiveData( &Local_u8ReceivedData );
	Local_u8FrequencyValue = Local_u8FrequencyValue * 10 + Convert_To_Number(Local_u8ReceivedData );
	LCD_enuWriteIntegerNumber(Local_u8FrequencyValue);
	LCD_enuWriteString(" ");

	//Receive the Amplitude of the signal
	
	UART_enuReceiveData( &Local_u8ReceivedData );
	Local_u8Amplitude = Local_u8Amplitude * 10 + Convert_To_Number(Local_u8ReceivedData );
	LCD_enuWriteIntegerNumber(Local_u8Amplitude);
	LCD_enuWriteString(" ");
	UART_enuReceiveData( &Local_u8ReceivedData );
	Local_u8Amplitude = Local_u8Amplitude * 10 + Convert_To_Number(Local_u8ReceivedData );
	LCD_enuWriteIntegerNumber(Local_u8Amplitude);
	LCD_enuWriteString(" ");
	UART_enuReceiveData( &Local_u8ReceivedData );
	Local_u8Amplitude = Local_u8Amplitude * 10 + Convert_To_Number(Local_u8ReceivedData );
	LCD_enuWriteIntegerNumber(Local_u8Amplitude);
	
	
	UART_enuSendData('<');
	UART_enuSendData('3');
	UART_enuSendData('1');
	UART_enuSendData('5');
	UART_enuSendData('!');
	UART_enuSendData('2');
	UART_enuSendData('%');
	
	
		
	if(Local_u8FrequencyValue == 51)
	{
		while(1)
		{
			PORTC=Local_u8Amplitude;
			_delay_ms(10);
			PORTC=0;
			_delay_ms(10);
		}				
	}	
		
	else if(Local_u8FrequencyValue == 99)
	{
		while(1)
		{
			PORTC=Local_u8Amplitude;
			_delay_ms(5);
			PORTC=0;
			_delay_ms(5);
		}
	}
	else
	{
		while(1)
		{
			PORTC=Local_u8Amplitude;
			_delay_ms(10);
			PORTC=0;
			_delay_ms(10);
		}
	}
		

	
}

void StaircaseWave(void)
{
	u8 Local_u8FrequencyValue = 0;
	u8 Local_u8Amplitude =0;
	u8 Local_u8ReceivedData = 0;
	
	//Receive the Amplitude of the signal
	
	UART_enuReceiveData( &Local_u8ReceivedData );
	Local_u8Amplitude = Local_u8Amplitude * 10 + Convert_To_Number(Local_u8ReceivedData );
	LCD_enuWriteIntegerNumber(Local_u8Amplitude);
	LCD_enuWriteString(" ");
	UART_enuReceiveData( &Local_u8ReceivedData );
	Local_u8Amplitude = Local_u8Amplitude * 10 + Convert_To_Number(Local_u8ReceivedData );
	LCD_enuWriteIntegerNumber(Local_u8Amplitude);
	LCD_enuWriteString(" ");
	UART_enuReceiveData( &Local_u8ReceivedData );
	Local_u8Amplitude = Local_u8Amplitude * 10 + Convert_To_Number(Local_u8ReceivedData );
	LCD_enuWriteIntegerNumber(Local_u8Amplitude);
	
	UART_enuSendData('<');
		
		UART_enuSendData('3');
		UART_enuSendData('4');
		UART_enuSendData('!');
		UART_enuSendData(')');
		UART_enuSendData('2');
		UART_enuSendData('#');
		UART_enuSendData('!');
		UART_enuSendData('3');
		UART_enuSendData('%');
		

	
	
	while(1)
	{
		
	
	PORTC = 0x00;
	_delay_ms(5);
	PORTC = Local_u8Amplitude-190;
	_delay_ms(5);
	PORTC = Local_u8Amplitude - 125;
	_delay_ms(5);
	PORTC = Local_u8Amplitude - 60;
	_delay_ms(5);
	PORTC = Local_u8Amplitude;
	_delay_us(100);
	}
}

void TriangularWave()
{
		u8 Local_u8FrequencyValue = 0;
		u8 Local_u8Amplitude =0;
		u8 Local_u8ReceivedData = 0;
		

		//Receive the Amplitude of the signal
		
		UART_enuReceiveData( &Local_u8ReceivedData );
		Local_u8Amplitude = Local_u8Amplitude * 10 + Convert_To_Number(Local_u8ReceivedData );
		LCD_enuWriteIntegerNumber(Local_u8Amplitude);
		LCD_enuWriteString(" ");
		UART_enuReceiveData( &Local_u8ReceivedData );
		Local_u8Amplitude = Local_u8Amplitude * 10 + Convert_To_Number(Local_u8ReceivedData );
		LCD_enuWriteIntegerNumber(Local_u8Amplitude);
		LCD_enuWriteString(" ");
		UART_enuReceiveData( &Local_u8ReceivedData );
		Local_u8Amplitude = Local_u8Amplitude * 10 + Convert_To_Number(Local_u8ReceivedData );
		LCD_enuWriteIntegerNumber(Local_u8Amplitude);
		
		
		UART_enuSendData('<');
		UART_enuSendData('4');
		UART_enuSendData('2');
		UART_enuSendData(')');
		UART_enuSendData('!');
		UART_enuSendData('.');
		UART_enuSendData(',');
		UART_enuSendData('%');

	while(1)
	{
		
		for(u8 Local_u8Iterator1=0;Local_u8Iterator1<Local_u8Amplitude;Local_u8Iterator1++) PORTC = Local_u8Iterator1;
		for(u8 Local_u8Iterator2=Local_u8Amplitude;Local_u8Iterator2>0;Local_u8Iterator2--) PORTC = Local_u8Iterator2;

		//_delay_ms(1);
	}
}

u8 Convert_To_Number(u8 Copy_u8Letter)
{
	if(Copy_u8Letter >= 65 &&  Copy_u8Letter <= 70)
	{
		return (Copy_u8Letter - 55 );
	}
	else if(Copy_u8Letter == 48)
	{
		return 0;
	}
	else
	{
		return ( Copy_u8Letter - 48 ) ;
	}

	
}

