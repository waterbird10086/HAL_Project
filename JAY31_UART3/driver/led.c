#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable开启时钟 */
	LED1_CLK_ENABLE();

	/*Configure GPIO pin : PtPin 设置参数*/
	GPIO_InitStruct.Pin = LED1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

//	/* GPIO Ports Clock Enable开启时钟 */
//	LED1_CLK_ENABLE();

//	/*Configure GPIO pin : PtPin 设置参数*/
//	GPIO_InitStruct.Pin = LED1_Pin;
//	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);
	
}
