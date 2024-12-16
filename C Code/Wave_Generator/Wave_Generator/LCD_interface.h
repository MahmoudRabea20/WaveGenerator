/*
 * LCD_interface.h
 *
 *  Created on: Jul 19, 2023
 *      Author: top
 */

#include "ErrorState.h"
#include "stdTypes.h"

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

ES_t LCD_enuInit(void);
ES_t LCD_enuWriteCommand(u8 Copy_u8Command);
ES_t LCD_enuWriteData(u8 Copy_u8Data);
ES_t LCD_enuClear();
ES_t LCD_enuWriteString(const char* Copy_pchString);
ES_t LCD_enuWriteIntegerNumber(s32 Copy_s32IntegerNumber);
ES_t LCD_enuWriteFloatNumber(f64 Copy_f64FloatNumber);
ES_t LCD_enuReturnHome();
ES_t LCD_enuGoToXYPosition(u8 Copy_u8XPosition,u8 Copy_u8YPosition);
ES_t LCD_enuWriteSpecialCharacter(u8 Copy_Au8LetterArray[] ,u8 Copy_u8BlockNumber,u8 Copy_u8XPosition ,u8 Copy_u8YPosition);
ES_t LCD_enuDeleteCharacter(u8 Copy_u8ShiftedNumber);


#endif /* LCD_INTERFACE_H_ */
