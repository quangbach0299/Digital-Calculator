/*
 * I2C_LCD.h
 *
 *  Created on: Jul 25, 2021
 *      Author: Hoan Nguyen
 */

#ifndef INC_I2C_LCD_H_
#define INC_I2C_LCD_H_

#include "stm32f4xx_hal.h"

void LCD_Init (void);   // initialize lcd

void LCD_Send_Cmd (char cmd);  // send command to the lcd

void LCD_Send_Char (char data);  // send data to the lcd

void LCD_Send_String (char *str);  // send string to the lcd

void LCD_Put_Cur(int row, int col);  // put cursor at the entered position row (0 or 1), col (0-15);

void LCD_Clear (void);


#endif /* INC_I2C_LCD_H_ */
