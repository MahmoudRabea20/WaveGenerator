/*
 * UART_interface.h
 *
 *  Created on: Jul 30, 2023
 *      Author: top
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

ES_t UART_enuInit(void);
ES_t UART_enuReceiveData(u8* Copy_u8ReceivedData);
ES_t UART_enuSendData(u8 Copy_u8Data);


#endif /* UART_INTERFACE_H_ */
