/*
 * Math.c
 *
 *  Created on: Jul 27, 2021
 */

#include "Math.h"

// Define the number of decimal place to be rounded
#define ROUND 6
#define PI 3.141592654
// Display number to LCD
void DisplayNum(double lfNum)
{
  // Khai báo mảng kí tự xuất ra màn hình
  char result_arr[20] = {0};
  int index = 0;

  // lấy phần nguyên của số đưa vào
  int nNum = (int)lfNum;

  itoa(nNum, result_arr, 10);

  if(lfNum - nNum == 0)
  {
    LCD_Send_String(result_arr);
  }
  else
  {
    index = strlen(result_arr);
    result_arr[index] = '.';
    index ++;

    // lấy phần thập phân với độ chính xác ROUND chữ số sau dấu phẩy
    for(int i = 0; i < ROUND; i++)
    {
      lfNum = lfNum - nNum;
      lfNum = lfNum * 10;
      nNum = (int)lfNum;
      result_arr[index + i] =  nNum + 48;
    }
    LCD_Send_String(result_arr);
  }
}

// Start calculating in basic mode
void BasicCalculator()
{
  // Clear LCD
  LCD_Send_Cmd(0x01);
  LCD_Send_String("Basic Calculator");
  HAL_Delay(500);
  LCD_Send_Cmd(0x01);

  // Declare variables and flag
  double lfOperand1 = 0, lfOperand2 = 0, lfResult = 0;

  char oprd1_arr[10] = {0};
  char oprd2_arr[10] = {0};
  uint8_t oprd1_idx = 0;
  uint8_t oprd2_idx = 0;

  char temp_char = 0;
  char operator = 0;
  uint8_t LCD_Cnt = 0;
  bool isOperand2 = false;
  //Start while loop to get expression
  while(1)
  {
    // Get character from keypad
    temp_char = Keypad_ReadKey();
    HAL_Delay(20);
    if(temp_char == 'A')  temp_char = '+';
    else if(temp_char == 'B')  temp_char = '-';
    else if(temp_char == 'C')  temp_char = 'x';
    else if(temp_char == 'D')  temp_char = '/';
    else if(temp_char == '*')  temp_char = '.';
    else if(temp_char == '#')  break;

    if(temp_char == '+' || temp_char == '-' || temp_char == 'x' || temp_char == '/')
    {
      if(oprd1_idx != 0 && operator == 0)
      {
    	  operator = temp_char;
    	  isOperand2 = true;
    	  LCD_Send_Char(operator);
      }
    }

    if(isOperand2 == false && temp_char != operator)
    {
      LCD_Send_Char(temp_char);
      oprd1_arr[oprd1_idx] = temp_char;
      oprd1_idx++;
    }
    else if(isOperand2 == true && temp_char != operator)
    {
      LCD_Send_Char(temp_char);
      oprd2_arr[oprd2_idx] = temp_char;
      oprd2_idx++;
    }

    // If data length > 16, shift left the screen when display data
    LCD_Cnt++;
    if(LCD_Cnt > 16)  LCD_Send_Cmd(0x18);

  // End while loop
  }

  lfOperand1 = atof(oprd1_arr);
  lfOperand2 = atof(oprd2_arr);

  // Start calculate
  switch(operator)
  {
    case '+':
      lfResult = lfOperand1 + lfOperand2;
      break;
    case '-' :
      lfResult = lfOperand1 - lfOperand2;
      break;
    case 'x' :
      lfResult = lfOperand1 * lfOperand2;
      break;
    case '/' :
      lfResult = lfOperand1 / lfOperand2;
      if (lfOperand2 ==0)  { LCD_Send_String("MATH ERROR"); return; }
      break;
  }

  // If expression is more than 16 characters, shift right the screen before display result
  while(LCD_Cnt - 16 > 0)
  {
    LCD_Send_Cmd(0x1C);
    LCD_Cnt--;
  }

  HAL_Delay(50);
  LCD_Send_Cmd(0xC0);
  LCD_Send_Char('=');

  // Display result to LCD
  DisplayNum(lfResult);

  //End basic calculator
}

/* Advance calculator mode
 * A = lũy thừa
 * B = Căn bậc 2
 * C = Căn bậc 3
 * D = exp
 * */
void AdvanceCalculator(void)
{
  // Clear LCD
  LCD_Send_Cmd(0x01);
  LCD_Send_String("Advance Calculator");
  HAL_Delay(500);
  LCD_Send_Cmd(0x01);

  // Declare variables and flag
  double lfOperand1 = 0, lfOperand2 = 0, lfResult = 0;
  char oprd1_arr[10] = {0};
  char oprd2_arr[10] = {0};
  uint8_t oprd1_idx = 0;
  uint8_t oprd2_idx = 0;

  char operator = 0;
  char temp_char = 0;
  bool isOperand2 = false;
  //Start while loop to get expression
  while(1)
  {
    // Get character from keypad
    temp_char = Keypad_ReadKey();
    HAL_Delay(20);

    switch(temp_char)
    {
      case 'A':
        operator = temp_char;
        isOperand2 = true;
        LCD_Send_String("^(");
        break;
      case 'B':
        operator = temp_char;
        LCD_Send_String("sqrt(");
        break;
      case 'C':
        operator = temp_char;
        LCD_Send_String("cbrt(");
        break;
    }

    if(temp_char == 'D')  temp_char = '-';
    else if(temp_char == '*')  temp_char = '.';
    else if (temp_char == '#')  break;

    // Check the character read from keypad and store in operand array
    if(isOperand2 == false && temp_char != operator)
    {
      LCD_Send_Char(temp_char);
      oprd1_arr[oprd1_idx] = temp_char;
      oprd1_idx++;
    }
    else if(isOperand2 == true && temp_char != operator)
    {
      LCD_Send_Char(temp_char);
      oprd2_arr[oprd2_idx] = temp_char;
      oprd2_idx++;
    }

  // End while loop
  }

  lfOperand1 = atof(oprd1_arr);
  if(isOperand2 == true)  lfOperand2 = atof(oprd2_arr);

  switch (operator)
  {
    case 'A':
      lfResult = pow(lfOperand1, lfOperand2);
      break;
    case 'B':
      lfResult = sqrt(lfOperand1);
      break;
    case 'C':
      lfResult = cbrt(lfOperand1);
      break;
  }

  LCD_Send_Char(')');
  LCD_Send_Cmd(0xC0);
  LCD_Send_Char('=');

  DisplayNum(lfResult);
// End Advance Calculator
}

void TrigonometricCalculator(void)
{
  // Clear LCD
  LCD_Send_Cmd(0x01);
  LCD_Send_String("Trigonometric");
  LCD_Send_Cmd(0xC0);
  LCD_Send_String("Calculator");
  HAL_Delay(500);
  LCD_Send_Cmd(0x01);

  // Declare variables and flag
  double lfOperand = 0, lfResult = 0;
  char oprd_arr[10] = {0};
  uint8_t oprd_idx = 0;
  char operator = 0;
  char temp_char = 0;

  //Start while loop to get expression
  while(1)
  {
	// Get character from keypad
	temp_char = Keypad_ReadKey();
	HAL_Delay(20);

	switch(temp_char)
	{
	  case 'A':
		operator = temp_char;
		LCD_Send_String("sin(");
		break;
	  case 'B':
		operator = temp_char;
		LCD_Send_String("cos(");
		break;
	  case 'C':
		operator = temp_char;
		LCD_Send_String("tan(");
		break;
	  case 'D':
	    operator = temp_char;
	    LCD_Send_String("cot(");
	    break;
	}

	if(temp_char == '*')  temp_char = '.';
	else if (temp_char == '#')  break;

	if(temp_char != operator)
	{
      LCD_Send_Char(temp_char);
	  oprd_arr[oprd_idx] = temp_char;
	  oprd_idx++;
	}

  // End while loop
  }

  double degreeNum = atof(oprd_arr);
  // Convert degree to gradient
  lfOperand = (degreeNum * PI) / 180.0;

  switch (operator)
  {
	case 'A':
	  lfResult = sin(lfOperand);
	  break;
	case 'B':
	  lfResult = cos(lfOperand);
	  break;
	case 'C':
	  if(degreeNum == 90)
	  {
	    LCD_Send_Cmd(0x01);
	    LCD_Send_String("Math Error");
	    return;
	  }
	  lfResult = tan(lfOperand);
	  break;
	case 'D':
	  if(degreeNum == 0)
	  {
	    LCD_Send_Cmd(0x01);
	    LCD_Send_String("Math Error");
	    return;
	  }
	  lfResult = 1.0 / tan(lfOperand);
	  break;
  }

  LCD_Send_Char(')');
  LCD_Send_Cmd(0xC0);
  LCD_Send_Char('=');

  DisplayNum(lfResult);
}
/* Delete 1 character using '*'
if (temp_char == '*')
{
  dataIdx--;
  lcd_send_cmd(0x10);
  lcd_send_data(' ');
  lcd_send_cmd(0x10);
  continue;
}
*/

// View result, press 'B' to choose mode again
// press 'A' to continue in Basic mode
//  uint8_t LCD_cnt = 0;
//  while(1)
//  {
//    temp_char = Keypad_ReadKey();
//    if(temp_char == '#') {lcd_send_cmd(0x18); LCD_cnt++; }
//
//    else if(temp_char == '*' && LCD_cnt != 0) { lcd_send_cmd(0x1C); LCD_cnt--; }
//
//    else if(temp_char == 'A')
//    	BasicCalculator();
//    else if(temp_char == 'B')
//    	break;
//  }

