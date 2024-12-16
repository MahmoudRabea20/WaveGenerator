/*
 * LCD_configuration.h
 *
 *  Created on: Jul 19, 2023
 *      Author: top
 */

#ifndef LCD_CONFIGURATION_H_
#define LCD_CONFIGURATION_H_

/* LCD_MODE : 1- LCD_EIGHT_BIT
 *            2- LCD_FOUR_BIT
 * */

#define LCD_MODE      LCD_FOUR_BIT

          /* Control Pins */
#define LCD_RS_GRP        DIO_GROUP_A
#define LCD_RW_GRP        DIO_GROUP_A
#define LCD_EN_GRP        DIO_GROUP_A

#define LCD_RS_PIN        DIO_PIN_1
#define LCD_RW_PIN        DIO_PIN_2
#define LCD_EN_PIN        DIO_PIN_3

          /* Data Pins */
#define LCD_DATA_GRP      DIO_GROUP_A
#define LCD_DATA_PIN0     DIO_PIN_0
#define LCD_DATA_PIN1     DIO_PIN_1
#define LCD_DATA_PIN2     DIO_PIN_2
#define LCD_DATA_PIN3     DIO_PIN_3
#define LCD_DATA_PIN4     DIO_PIN_4
#define LCD_DATA_PIN5     DIO_PIN_5
#define LCD_DATA_PIN6     DIO_PIN_6
#define LCD_DATA_PIN7     DIO_PIN_7


#endif /* LCD_CONFIGURATION_H_ */
