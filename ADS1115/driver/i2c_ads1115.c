// i2c_ads1115.c

#include "i2c_ads1115.h"
#include "usart.h"
#include "stdlib.h"

/**
  * @brief  配置ADS1115寄存器。
  * @param  ads1115_I2cHandle: ADS1115的I2C句柄。
  * @param  pointADD: 配置的点地址。
  * @param  configH: 配置的高字节。
  * @param  configL: 配置的低字节。
  * @retval None
  */
void ads1115_config_register(I2C_HandleTypeDef ads1115_I2cHandle, uint8_t pointADD, uint8_t configH, uint8_t configL)
{
    uint8_t reg_data[3] = {pointADD, configH, configL};
    while (HAL_I2C_Master_Transmit(&ads1115_I2cHandle, ADS1115_WRITE_ADDRESS, reg_data, 3, 1000) != HAL_OK)
    {
        if (HAL_I2C_GetError(&ads1115_I2cHandle) != HAL_I2C_ERROR_AF)
        {
            printf("ads1115 配置寄存器错误！！！\r\n");
        }
    }
}

/**
  * @brief  从ADS1115读取数据。
  * @param  ads1115_I2cHandle: ADS1115的I2C句柄。
  * @retval 从ADS1115读取的数据。
  */
int16_t ads1115_read_data(I2C_HandleTypeDef ads1115_I2cHandle)
{
    int16_t data;
    uint8_t rx_data[2] = {0};

    while (HAL_I2C_Master_Transmit(&ads1115_I2cHandle, ADS1115_WRITE_ADDRESS, 0x00, 1, 1000) != HAL_OK)
    {
        if (HAL_I2C_GetError(&ads1115_I2cHandle) != HAL_I2C_ERROR_AF)
        {
            printf("ads1115 Config Register error!!!\r\n");
        }
    }

    while (HAL_I2C_Master_Receive(&ads1115_I2cHandle, ADS1115_READ_ADDRESS, rx_data, 2, 1000) != HAL_OK)
    {
        if (HAL_I2C_GetError(&ads1115_I2cHandle) != HAL_I2C_ERROR_AF)
        {
            printf("ads1115 Config Register error!!!\r\n");
        }
    }

    data = rx_data[0] * 256 + rx_data[1];
    return data;
}

/**
  * @brief  将ADC数据转换为电压值。
  * @param  ads1115_I2cHandle: ADS1115的I2C句柄。
  * @param  pointADD: 配置的点地址。
  * @param  configH: 配置的高字节。
  * @param  configL: 配置的低字节。
  * @retval 从ADC数据转换的电压值。
  */
double ads1115_get_voltage_val(I2C_HandleTypeDef ads1115_I2cHandle, uint8_t pointADD, uint8_t configH, uint8_t configL)
{
    double val;
    int16_t ad_val;

    ads1115_config_register(ads1115_I2cHandle, pointADD, configH, configL);
    HAL_Delay(10);
    ad_val = ads1115_read_data(ads1115_I2cHandle);
    if ((ad_val == 0x7FFF) | (ad_val == 0X8000)) // 检查是否超出范围
    {
        ad_val = 0;
        printf("ads1115 read data error!!!\r\n");
    }

    switch ((0x0E & configH) >> 1) // 分辨率对应的范围
    {
    case (0x00):
        val = (double)ad_val * 187.5 / 1000000.0;
        break;
    case (0x01):
        val = (double)ad_val * 125 / 1000000.0;
        break;
    case (0x02):
        val = (double)ad_val * 62.5 / 1000000.0;
        break;
    case (0x03):
        val = (double)ad_val * 31.25 / 1000000.0;
        break;
    case (0x04):
        val = (double)ad_val * 15.625 / 1000000.0;
        break;
    case (0x05):
        val = (double)ad_val * 7.8125 / 1000000.0;
        break;
    }
    return val;
}
