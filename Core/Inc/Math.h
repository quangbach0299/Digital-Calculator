/*
 * Math.h
 *
 *  Created on: Jul 27, 2021
 */

#ifndef INC_MATH_H_
#define INC_MATH_H_

// Include libraries
#include "stm32f4xx_hal.h"
#include "I2C_LCD.h"
#include "Keypad.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// Function prototypes
void DisplayNum(double lfNum);
void BasicCalculator(void);
void AdvanceCalculator(void);
void TrigonometricCalculator(void);

#endif /* INC_MATH_H_ */
