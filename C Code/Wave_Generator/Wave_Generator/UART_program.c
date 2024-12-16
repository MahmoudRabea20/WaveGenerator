/*
 * UART_program.c
 *
 *  Created on: Jul 30, 2023
 *      Author: top
 */

#include "ErrorState.h"
#include "stdTypes.h"
#include "BIT_MATH.h"

#include "UART_register.h"
#include "UART_interface.h"

ES_t UART_enuInit(void)
{
	ES_t Local_enuErrorState = ES_OK;
	u8 Local_u8UCSRCVal=0;

	/* Set bit 7 for UCSRC*/
	SET_BIT(Local_u8UCSRCVal,UCSRC_URSEL);

	/* Set Character Size = 8-bit */
	SET_BIT(Local_u8UCSRCVal,UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCVal,UCSRC_UCSZ1);

	/* Send val to register */
	UCSRC = Local_u8UCSRCVal;

	/*Baud Rate (bps) = 9600 */
	UBRRL = 6;

	/* Enable Receive */
	SET_BIT(UCSRB,UCSRB_RXEN);

	/* Enable Transmitter */
	SET_BIT(UCSRB,UCSRB_TXEN);

	return Local_enuErrorState;
}

ES_t UART_enuReceiveData(u8* Copy_u8ReceivedData)
{
	ES_t Local_enuErrorState = ES_OK;

	while( ( (UCSRA >> UCSRA_RXC) & (1) ) == 0  );//wait until receive data

	*Copy_u8ReceivedData = UDR;

	return Local_enuErrorState;
}

ES_t UART_enuSendData(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState = ES_OK;

	while( ( ( UCSRA >> UCSRA_UDRE) & (1) ) == 0 ); // wait until UDR is empty

	UDR = Copy_u8Data;

	return Local_enuErrorState;
}
