#include "AD9833.h"

#include "stm32f1xx_hal.h"

#define SPI_HANDLE hspi2 // 修改为您使用的SPI外设句柄

void AD9833_WaveSeting(double Freq, unsigned int Freq_SFR, unsigned int WaveMode, unsigned int Phase)
{
    int frequence_LSB, frequence_MSB, Phs_data;
    double frequence_mid, frequence_DATA;
    long int frequence_hex;

    /*********************************计算频率的16进制值***********************************/
    frequence_mid = 268435456 / 25; //适合25M晶振
    //如果时钟频率不为25MHZ，修改该处的频率值，单位MHz ，AD9833最大支持25MHz
    frequence_DATA = Freq;
    frequence_DATA = frequence_DATA / 1000000;
    frequence_DATA = frequence_DATA * frequence_mid;
    frequence_hex = frequence_DATA; //这个frequence_hex的值是32位的一个很大的数字，需要拆分成两个14位进行处理；
    frequence_LSB = frequence_hex;   //frequence_hex低16位送给frequence_LSB
    frequence_LSB = frequence_LSB & 0x3fff; //去除最高两位，16位数换去掉高位后变成了14位
    frequence_MSB = frequence_hex >> 14;     //frequence_hex高16位送给frequence_HSB
    frequence_MSB = frequence_MSB & 0x3fff; //去除最高两位，16位数换去掉高位后变成了14位

    Phs_data = Phase | 0xC000; //相位值
    HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){0x01, 0x00}, 2, HAL_MAX_DELAY); //复位AD9833,即RESET位为1
    HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){0x21, 0x00}, 2, HAL_MAX_DELAY); //选择数据一次写入，B28位和RESET位为1

    if (Freq_SFR == 0) //把数据设置到设置频率寄存器0
    {
        frequence_LSB = frequence_LSB | 0x4000;
        frequence_MSB = frequence_MSB | 0x4000;
        //使用频率寄存器0输出波形
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){frequence_LSB >> 8, frequence_LSB & 0xFF}, 2, HAL_MAX_DELAY); //L14，选择频率寄存器0的低14位数据输入
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){frequence_MSB >> 8, frequence_MSB & 0xFF}, 2, HAL_MAX_DELAY); //H14 频率寄存器的高14位数据输入
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){Phs_data >> 8, Phs_data & 0xFF}, 2, HAL_MAX_DELAY);         //设置相位
    }
    if (Freq_SFR == 1) //把数据设置到设置频率寄存器1
    {
        frequence_LSB = frequence_LSB | 0x8000;
        frequence_MSB = frequence_MSB | 0x8000;
        //使用频率寄存器1输出波形
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){frequence_LSB >> 8, frequence_LSB & 0xFF}, 2, HAL_MAX_DELAY); //L14，选择频率寄存器1的低14位输入
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){frequence_MSB >> 8, frequence_MSB & 0xFF}, 2, HAL_MAX_DELAY); //H14 频率寄存器1为
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){Phs_data >> 8, Phs_data & 0xFF}, 2, HAL_MAX_DELAY);         //设置相位
    }

    if (WaveMode == TRI_WAVE) //输出三角波波形
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){0x20, 0x02}, 2, HAL_MAX_DELAY);
    if (WaveMode == SQU_WAVE) //输出方波波形
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){0x20, 0x28}, 2, HAL_MAX_DELAY);
    if (WaveMode == SIN_WAVE) //输出正弦波形
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){0x20, 0x00}, 2, HAL_MAX_DELAY);
}

