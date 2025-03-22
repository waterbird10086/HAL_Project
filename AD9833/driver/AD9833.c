#include "AD9833.h"

#include "stm32f1xx_hal.h"

#define SPI_HANDLE hspi2 // �޸�Ϊ��ʹ�õ�SPI������

void AD9833_WaveSeting(double Freq, unsigned int Freq_SFR, unsigned int WaveMode, unsigned int Phase)
{
    int frequence_LSB, frequence_MSB, Phs_data;
    double frequence_mid, frequence_DATA;
    long int frequence_hex;

    /*********************************����Ƶ�ʵ�16����ֵ***********************************/
    frequence_mid = 268435456 / 25; //�ʺ�25M����
    //���ʱ��Ƶ�ʲ�Ϊ25MHZ���޸ĸô���Ƶ��ֵ����λMHz ��AD9833���֧��25MHz
    frequence_DATA = Freq;
    frequence_DATA = frequence_DATA / 1000000;
    frequence_DATA = frequence_DATA * frequence_mid;
    frequence_hex = frequence_DATA; //���frequence_hex��ֵ��32λ��һ���ܴ�����֣���Ҫ��ֳ�����14λ���д���
    frequence_LSB = frequence_hex;   //frequence_hex��16λ�͸�frequence_LSB
    frequence_LSB = frequence_LSB & 0x3fff; //ȥ�������λ��16λ����ȥ����λ������14λ
    frequence_MSB = frequence_hex >> 14;     //frequence_hex��16λ�͸�frequence_HSB
    frequence_MSB = frequence_MSB & 0x3fff; //ȥ�������λ��16λ����ȥ����λ������14λ

    Phs_data = Phase | 0xC000; //��λֵ
    HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){0x01, 0x00}, 2, HAL_MAX_DELAY); //��λAD9833,��RESETλΪ1
    HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){0x21, 0x00}, 2, HAL_MAX_DELAY); //ѡ������һ��д�룬B28λ��RESETλΪ1

    if (Freq_SFR == 0) //���������õ�����Ƶ�ʼĴ���0
    {
        frequence_LSB = frequence_LSB | 0x4000;
        frequence_MSB = frequence_MSB | 0x4000;
        //ʹ��Ƶ�ʼĴ���0�������
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){frequence_LSB >> 8, frequence_LSB & 0xFF}, 2, HAL_MAX_DELAY); //L14��ѡ��Ƶ�ʼĴ���0�ĵ�14λ��������
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){frequence_MSB >> 8, frequence_MSB & 0xFF}, 2, HAL_MAX_DELAY); //H14 Ƶ�ʼĴ����ĸ�14λ��������
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){Phs_data >> 8, Phs_data & 0xFF}, 2, HAL_MAX_DELAY);         //������λ
    }
    if (Freq_SFR == 1) //���������õ�����Ƶ�ʼĴ���1
    {
        frequence_LSB = frequence_LSB | 0x8000;
        frequence_MSB = frequence_MSB | 0x8000;
        //ʹ��Ƶ�ʼĴ���1�������
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){frequence_LSB >> 8, frequence_LSB & 0xFF}, 2, HAL_MAX_DELAY); //L14��ѡ��Ƶ�ʼĴ���1�ĵ�14λ����
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){frequence_MSB >> 8, frequence_MSB & 0xFF}, 2, HAL_MAX_DELAY); //H14 Ƶ�ʼĴ���1Ϊ
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){Phs_data >> 8, Phs_data & 0xFF}, 2, HAL_MAX_DELAY);         //������λ
    }

    if (WaveMode == TRI_WAVE) //������ǲ�����
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){0x20, 0x02}, 2, HAL_MAX_DELAY);
    if (WaveMode == SQU_WAVE) //�����������
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){0x20, 0x28}, 2, HAL_MAX_DELAY);
    if (WaveMode == SIN_WAVE) //������Ҳ���
        HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t[]){0x20, 0x00}, 2, HAL_MAX_DELAY);
}

