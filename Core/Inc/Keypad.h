/*
 * Keypad.h
 *
 *  Created on: Jul 26, 2021
 *      Author: Hoan Nguyen
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include "stm32f4xx_hal.h"

void Keypad_Init(void);
char Keypad_ReadKey(void);

#endif /* INC_KEYPAD_H_ */
