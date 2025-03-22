#include "main.h"

/*引脚配置*/
#define SCL_Pin GPIO_PIN_10
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_11
#define SDA_GPIO_Port GPIOB
#define PCA_W_SCL(x) HAL_GPIO_WritePin(GPIOB, SCL_Pin, (GPIO_PinState)(x))
#define PCA_W_SDA(x) HAL_GPIO_WritePin(GPIOB, SDA_Pin, (GPIO_PinState)(x))

/*引脚初始化*/
void PCA_I2C_Init(void)
{

	// 使能GPIOC的时钟和复用功能的时钟
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_AFIO_CLK_ENABLE();


	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
//	HAL_GPIO_WritePin(GPIOB, SCL_Pin | SDA_Pin, GPIO_PIN_SET);

	/*Configure GPIO pins : PBPin PBPin */
	GPIO_InitStruct.Pin = SCL_Pin | SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	PCA_W_SCL(1);
	PCA_W_SDA(1);
}

/**
 * @brief  I2C开始
 * @param  无
 * @retval 无
 */
void PCA_I2C_Start(void)
{
	PCA_W_SDA(1);
	PCA_W_SCL(1);
	PCA_W_SDA(0);
	PCA_W_SCL(0);
}

/**
 * @brief  I2C停止
 * @param  无
 * @retval 无
 */
void PCA_I2C_Stop(void)
{
	PCA_W_SDA(0);
	PCA_W_SCL(1);
	PCA_W_SDA(1);
}

/**
 * @brief  I2C发送一个字节
 * @param  Byte 要发送的一个字节
 * @retval 无
 */
void PCA_I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		PCA_W_SDA(Byte & (0x80 >> i));
		PCA_W_SCL(1);
		PCA_W_SCL(0);
	}
	PCA_W_SDA(1);//释放SDA总线
	PCA_W_SCL(1); //额外的一个时钟，不处理应答信号
	PCA_W_SCL(0);
}


