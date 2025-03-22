#include "soft_IIC.h"

/**
 * @file     softwareiic.c
 * @brief    ������STM32 HAL�⼰CUBEMX���ɹ��̵����ģ��IIC
 * @version  V1.0.0
 * @author   Sundea
 * @date     2023/5/8
 */

/**
 * @brief IIC��ʱ
 * @param  ��
 * @return ��
 */
void IIC_Delay(uint8_t time)
{
    uint32_t i = time * 800; // �û������Լ���MCUʱ�ӽ������ñ���

    while (i--)
    {
        ;
    }
}

/**
 * @brief IIC��ʼ��
 * @param  ��
 * @return ��
 */
void Soft_IIC_Init(void)
{
    IIC_SDA_H();
    IIC_SCL_H();
}

/**
 * @brief SDA�����������ģʽ
 * @param  ��
 * @return ��
 */
static void Soft_IIC_Output(void)
{
    GPIO_InitTypeDef SOFT_IIC_GPIO_STRUCT;
    SOFT_IIC_GPIO_STRUCT.Mode = GPIO_MODE_OUTPUT_PP;
    SOFT_IIC_GPIO_STRUCT.Pin = IIC_SDA_PIN;
    SOFT_IIC_GPIO_STRUCT.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(IIC_SDA_PORT, &SOFT_IIC_GPIO_STRUCT);
}

/**
 * @brief SDA������������ģʽ
 * @param  ��
 * @return ��
 */
static void Soft_IIC_Input(void)
{
    GPIO_InitTypeDef SOFT_IIC_GPIO_STRUCT;
    SOFT_IIC_GPIO_STRUCT.Mode = GPIO_MODE_INPUT;
    SOFT_IIC_GPIO_STRUCT.Pin = IIC_SDA_PIN;
    SOFT_IIC_GPIO_STRUCT.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(IIC_SDA_PORT, &SOFT_IIC_GPIO_STRUCT);
}

/**
 * @brief IIC��ʼ�ź�
 * @param  ��
 * @return ��
 */
void Soft_IIC_Start(void)
{
    Soft_IIC_Output();
    IIC_SCL_L();
    IIC_SDA_H();
    IIC_SCL_H();
    IIC_Delay(IIC_DELAY_TIME);
    IIC_SDA_L();
    IIC_Delay(IIC_DELAY_TIME);
    IIC_SCL_L();
}

/**
 * @brief IICֹͣ�ź�
 * @param  ��
 * @return ��
 */
void Soft_IIC_Stop(void)
{
    Soft_IIC_Output();
    IIC_SCL_L();
    IIC_SDA_L();
    IIC_SCL_H();
    IIC_Delay(IIC_DELAY_TIME);
    IIC_SDA_H();
    IIC_Delay(IIC_DELAY_TIME);
}

/**
 * @brief IICӦ���ź�
 * @param  ��
 * @return ��
 */
void Soft_IIC_ACK(void)
{
    Soft_IIC_Output();
    IIC_SCL_L();
    IIC_SDA_L();
    IIC_Delay(IIC_DELAY_TIME);
    IIC_SCL_H();
    IIC_Delay(IIC_DELAY_TIME);
    IIC_SCL_L();
}

/**
 * @brief IIC��Ӧ���ź�
 * @param  ��
 * @return ��
 */
void Soft_IIC_NACK(void)
{
    Soft_IIC_Output();
    IIC_SCL_L();
    IIC_SDA_H();
    IIC_Delay(IIC_DELAY_TIME);
    IIC_SCL_H();
    IIC_Delay(IIC_DELAY_TIME);
}

/**
 * @brief IIC�ȴ�Ӧ���ź�
 * @param  ��
 * @return 0��Ӧ��  1��Ӧ��
 */
uint8_t Soft_IIC_Wait_ACK(void)
{
    uint8_t wait;
    Soft_IIC_Output();
    IIC_SDA_H();
    Soft_IIC_Input();
    IIC_SCL_H();
    IIC_Delay(IIC_DELAY_TIME);
    while (HAL_GPIO_ReadPin(IIC_SDA_PORT, IIC_SDA_PIN))
    {
        wait++;
        if (wait > 200)
        {
            Soft_IIC_Stop();
            return 0;
        }
    }
    IIC_SCL_L();
    return 1;
}

/**
 * @brief IICд����1
 * @param  ��
 * @return ��
 */
void Soft_IIC_Write_High(void)
{
    IIC_SCL_L();
    IIC_SDA_H();
    IIC_Delay(IIC_DELAY_TIME);
    IIC_SCL_H();
    IIC_Delay(IIC_DELAY_TIME);
    IIC_SCL_L();
}

/**
 * @brief IICд����0
 * @param  ��
 * @return ��
 */
void Soft_IIC_Write_Low(void)
{
    IIC_SCL_L();
    IIC_SDA_L();
    IIC_Delay(IIC_DELAY_TIME);
    IIC_SCL_H();
    IIC_Delay(IIC_DELAY_TIME);
    IIC_SCL_L();
}

/**
 * @brief IICд�뵥������
 * @param  ��
 * @return Ӧ���ź�, 0��Ӧ�� 1��Ӧ��
 */
uint8_t Soft_IIC_Write_Byte(uint8_t Byte)
{
    uint8_t i;
    Soft_IIC_Output();
    for (i = 0x80; i != 0; i >>= 1)
    {
        if (Byte & i)
        {
            Soft_IIC_Write_High();
        }
        else
        {
            Soft_IIC_Write_Low();
        }
    }
    return (Soft_IIC_Wait_ACK());
}

/**
 * @brief IIC��һ������
 * @param  ACK:Ӧ�� NACK:��Ӧ��
 * @return ���ض���������
 */
uint8_t Soft_IIC_Recv_Byte(ACK_STATUS ack_sta)
{
    uint8_t data = 0, i;
    Soft_IIC_Input();
    IIC_SCL_H();
    IIC_Delay(IIC_DELAY_TIME);
    for (i = 0x80; i != 0; i >>= 1)
    {
        if (HAL_GPIO_ReadPin(IIC_SDA_PORT, IIC_SDA_PIN) == 1)
        {
            data |= i;
        }
        IIC_Delay(IIC_DELAY_TIME);
        IIC_SCL_L();
        IIC_Delay(IIC_DELAY_TIME);
        IIC_SCL_H();
        IIC_Delay(IIC_DELAY_TIME);
    }
    if (ack_sta == ACK)
    {
        Soft_IIC_ACK();
    }
    else
    {
        Soft_IIC_NACK();
    }
    return data;
}

