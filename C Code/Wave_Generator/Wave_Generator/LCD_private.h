/*
 * LCD_private.h
 *
 *  Created on: Jul 19, 2023
 *      Author: top
 */

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_



#define LCD_EIGHT_BIT               8
#define LCD_FOUR_BIT                4
#define LCD_BIT_MASK                1
#define LCD_u8BLOCKBYTES            8

static void SendHalfDataPort(u8 Copy_u8Data);
static void SendEnablePulse();


#endif /* LCD_PRIVATE_H_ */
