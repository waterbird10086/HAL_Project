#include "key.h"

void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  SW2_CLK_ENABLE();
  SW3_CLK_ENABLE();
  SW4_CLK_ENABLE();

  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = SW2_Pin|SW3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = SW4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SW4_GPIO_Port, &GPIO_InitStruct);
}

uint8_t key_scan(void)
{
	uint8_t key_vel = 0;
	if(SW2_Read == 0)
	  {
		  HAL_Delay(10);
		  if(SW2_Read == 0)
		  {
			key_vel = 1;
		  }
	  }
	  else if(SW3_Read == 0)
	  {
		  HAL_Delay(10);
		  if(SW3_Read == 0)
		  {
			key_vel = 2;
		  }
	  }
	  else if(SW4_Read == 0)
	  {
		  HAL_Delay(10);
		  if(SW4_Read == 0)
		  {
			key_vel = 3;
		  }
	  }
	  return key_vel;
}
