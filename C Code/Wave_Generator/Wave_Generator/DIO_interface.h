/*
 * DIO_interface.h
 *
 *  Created on: Jul 18, 2023
 *      Author: top
 */

#include "ErrorState.h"
#include "stdTypes.h"

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


ES_t DIO_enuSetPinDirection(u8 Copy_u8GroupNumber,u8 Copy_u8PinNumber,u8 Copy_u8PinDirection);
ES_t DIO_enuSetPinValue(u8 Copy_u8GroupNumber,u8 Copy_u8PinNumber,u8 Copy_u8PinValue);
ES_t DIO_enuSetPortDirection(u8 Copy_u8GroupNumber,u8 Copy_u8PortDirection);
ES_t DIO_enuSetPortValue(u8 Copy_u8GroupNumber,u8 Copy_u8PortValue);
ES_t DIO_enuTogglePinValue(u8 Copy_u8GroupNumber,u8 Copy_u8PinNumber);
u8   DIO_u8GetPinValue(u8 Copy_u8GroupNumber,u8 Copy_u8PinNumber);
u8   DIO_u8GetPortValue(u8 Copy_u8GroupNumber);

#define DIO_GROUP_A    0
#define DIO_GROUP_B    1
#define DIO_GROUP_C    2
#define DIO_GROUP_D    3

#define DIO_PIN_0      0
#define DIO_PIN_1      1
#define DIO_PIN_2	   2
#define DIO_PIN_3      3
#define DIO_PIN_4      4
#define DIO_PIN_5      5
#define DIO_PIN_6      6
#define DIO_PIN_7      7

#define DIO_LOW_LEVEL  0
#define DIO_HIGH_LEVEL 1

#define DIO_INPUT	   0
#define DIO_OUTPUT     1

#define DIO_PORT_OUTPUT 0xff
#define DIO_PORT_INPUT  0x0

#define DIO_FLOAT	   0
#define DIO_PULL_UP	   1



#endif /* DIO_INTERFACE_H_ */
