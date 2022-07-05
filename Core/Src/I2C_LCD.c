
/** Put this in the src folder **/

#include "I2C_LCD.h"
extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly

#define SLAVE_ADDRESS_LCD 0x4E // change this according to ur setup

void LCD_Send_Cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
	HAL_Delay(10);
}

void LCD_Send_Char (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
	HAL_Delay(10);
}

void LCD_Clear (void)
{
	LCD_Send_Cmd (0x80);
	for (int i=0; i<70; i++)
	{
		LCD_Send_Char (' ');
	}
}

void LCD_Put_Cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    LCD_Send_Cmd (col);
}


void LCD_Init (void)
{
  // 4 bit initialisation
  LCD_Send_Cmd (0x33); /* set 4-bits interface */
  HAL_Delay(10);
  LCD_Send_Cmd (0x32);
  HAL_Delay(50);

  // dislay initialisation
  LCD_Send_Cmd (0x28); /* start to set LCD function */
  HAL_Delay(50);
  LCD_Send_Cmd (0x01); /* clear display */
  HAL_Delay(50);
  LCD_Send_Cmd (0x06); /* set entry mode */
  HAL_Delay(50);
  LCD_Send_Cmd (0x0D); /* set display to on */
  HAL_Delay(50);
  LCD_Send_Cmd (0x80); /* move cursor to home and set data address to 0 */
  HAL_Delay(50);
}

void LCD_Send_String (char *str)
{
	while (*str) LCD_Send_Char (*str++);
}
