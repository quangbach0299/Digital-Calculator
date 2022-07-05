#include "Keypad.h"

#define NUMROWS 4
#define NUMCOLS 4

char KeyMap[NUMROWS][NUMCOLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};



// Configure GPIO pins as keypad's pins
// RowPins: PA0, PA2, PA4, PA6
uint32_t RowPins[NUMROWS] = {GPIO_PIN_0, GPIO_PIN_2, GPIO_PIN_4, GPIO_PIN_6};

// ColPins: PC4, PB0, PB2, PE8
GPIO_TypeDef *ColPort[NUMCOLS] = {GPIOC, GPIOB, GPIOB, GPIOE};
uint32_t ColPins[NUMCOLS] = {GPIO_PIN_4, GPIO_PIN_0, GPIO_PIN_2, GPIO_PIN_8};

void Keypad_Init(void)
{
  HAL_GPIO_WritePin(GPIOA, ColPins[0], GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, ColPins[1], GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, ColPins[2], GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, ColPins[3], GPIO_PIN_SET);
}

char Keypad_ReadKey(void)
{
  char keyValue = 0;
  while(keyValue == 0)
  {
	  for(int colum = 0; colum < NUMCOLS; colum++)
	  {
	    HAL_GPIO_WritePin(ColPort[colum], ColPins[colum], GPIO_PIN_RESET);
	    for(int row = 0; row < NUMROWS; row++)
	    {
	      if(HAL_GPIO_ReadPin(GPIOA, RowPins[row]) == 0)
	      {
	        HAL_Delay(50);// debound
	        while(HAL_GPIO_ReadPin(GPIOA, RowPins[row])==0) {}
	        keyValue = KeyMap[row][colum];
	        return keyValue;
	      }
	    }
	    HAL_GPIO_WritePin(ColPort[colum], ColPins[colum], GPIO_PIN_SET);
	  }

  }

  return 0;
}

