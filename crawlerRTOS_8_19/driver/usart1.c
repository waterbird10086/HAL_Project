#include "usart1.h"

#include <stdio.h>
#include <string.h>

uint8_t rx_buffer[UART1_BUFFER_SIZE]; // ���ջ�����
uint16_t rx_index = 0; // ���ջ���������
int Point_data[3]={115,230,0};
char received_char;

char Serial_RxPacket[100];				//"@MSG\r\n"
uint8_t Serial_RxFlag;
//static char char_rx_buffer[64]; // ���ջ�������С����ʵ�����

typedef struct {
    int x;
    int y;
		int z;
		int pre;
} Point;

//�������պ���
void usart1_Init(void)
{
	HAL_UART1_Receive_IT;
//	alg_set_move_action(Point_data);
}

//int fputc(int ch,FILE *f)
//{
//	HAL_UART_Transmit(&huart1,(uint8_t*)&(ch),1,1000);
//	
//	return (ch);
//}

void process_coordinates(Point point) {
    // �����������ݵĺ�����������������д�ӡ�������ִ����������
//		if(MODE.MODEFLAT == 5)
//		{
//			printf("Received coordinates: x=%d, y=%d, pre=%d\r\n", point.x, point.y, point.pre);
//			alg_Yolo(point.x,point.y,point.pre);

//		}
//		else{
//			printf("Received coordinates: x=%d, y=%d, z=%d\r\n", point.x, point.y, point.z);
//			Point_data[0] = point.x;
//			Point_data[1] = point.y;
//			Point_data[2] = point.z;
//			alg_set_move_action(Point_data);
//			inverse_operation(point.x,point.y,point.z);
//		}
    
}

void usart1_process_data(uint8_t *data, uint16_t length)
{
    // ������Խ��յ������ݽ��д��������ӡ���������洢�ȵ�
    // ע�⣺���յ������ݳ���Ϊlength����������������'\n'
		if(strstr((char*)data, "LED1 ON\r\n"))
		{
			printf("LED1 is ON\r\n");
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
		}
		else if(strstr((char*)data, "LED1 OFF\r\n"))
		{
			printf("LED1 is OFF\r\n");
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);			
		}
		else if(strstr((char*)data, "LED2 ON\r\n"))
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);			
		}
//		else if(strstr((char*)data, "LED2 OFF\r\n"))
//		{
//			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);			
//		}
		
		char *ptr = (char*)data; // ������ת��Ϊ�ַ�ָ��
    int x, y, z;
    
    // �������ݸ�ʽΪ "x,y\r\n"
//    if (sscanf(ptr, "%d,%d,%d", &x, &y, &z) == 3) {
//        Point point = {x, y, z};
//        process_coordinates(point);
//    }
		
		if(sscanf(ptr,"%d %d %d", &x, &y, &z )== 3 )
		{
				Point point = {x, y, z};
        process_coordinates(point);
		}
		memset(rx_buffer, 0, UART1_BUFFER_SIZE);//�����������������ȫ����0
}


//void HAL_UART1_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//        if (rx_index < UART1_BUFFER_SIZE - 1) // ���������пռ�
//        {
//            if (rx_buffer[rx_index - 1] != 0XFE) // �����һ���ַ����ǽ�������
//            {
//                rx_buffer[rx_index++] = (uint8_t)(huart->Instance->DR & 0x00FF); // �����յ����ַ��洢����������
//            }
//            if(rx_buffer[rx_index - 1] == 0XFE)// �����һ���ַ��ǽ�������
//            {
//                // �Խ��յ������ݽ��д���
//                usart1_process_data(rx_buffer, rx_index - 1);
//            }		
////							if (received_char == 'E' && rx_index >= 7)
////							{
////									int x,y,z;
////									if (sscanf(char_rx_buffer, "FF %d %d %d FE", &x, &y, &z) == 3) {
////                    Point point = {x, y, z};
////                    process_coordinates(point);
////									}
////									memset(char_rx_buffer, 0, sizeof(char_rx_buffer)); // ��ս��ջ�����
////									rx_index = 0;
////							}
//        }
//        else // ����������
//        {
//            rx_index = 0; // ��ջ�����
//						memset(rx_buffer, 0, UART1_BUFFER_SIZE);
//        }
//				HAL_UART1_Receive_IT;//������һ�ν���	
//}

//void HAL_UART1_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//    static uint8_t rx_byte;
//    static uint8_t rx_state = 0; // ����״̬��0��ʾ�ȴ���ʼ�ֽڣ�1��ʾ�������ݣ�2��ʾ���ս����ֽ�
//    static uint8_t rx_data[3]; // �洢���յ�������
//    static uint8_t rx_count = 0; // �ѽ��յ����ݼ���
//		static uint8_t callup = 0;
//    
//    rx_byte = (uint8_t)(huart->Instance->DR & 0x00FF); // ��ȡ���յ����ֽ�
//    
//    if(rx_state == 0) {
//        if(rx_byte == 0xFF) {
//            rx_state = 1; // �����������״̬
//            rx_count = 0; // �������ݼ���
//        }
//				
//				else if(rx_byte == 0xFD)
//				{
//					callup = 1;
//				}
//				else if(rx_byte == 0xFC)
//				{
//					callup = 0;
//					OLED_ShowString(1,10,"OFF");
//					
////					inverse_operation(-145,300,0);
////					alg_move_run();

//				}
//					
//				
//    } else if(rx_state == 1) {
//        if(rx_byte == 0xFE) {
//            if(rx_count == 3 && callup == 1) { // �ж��Ƿ���յ�����������
//                // ������������յ�������
//                int x = rx_data[0];
//                int y = rx_data[1];
//                int z = rx_data[2];
//							
//								rx_buffer[0] = rx_data[0];
//								rx_buffer[1] = rx_data[1];
//								rx_buffer[2] = rx_data[2];
//							
//								OLED_ShowNum(4,1,rx_data[0],3);
//								OLED_ShowNum(4,5,rx_data[1],3);
//								OLED_ShowNum(4,10,rx_data[2],3);
//                Point point = {x, y, z};
//                process_coordinates(point);
//            }
//            rx_state = 0; // �ص��ȴ���ʼ�ֽ�״̬
//        } else {
//            // �������յ���ʮ�������ַ����洢
//            if(rx_count < 3) {
//                rx_data[rx_count++] = rx_byte;
//            }
//        }
//    }
//    
//    // ������һ�ν���
//    HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
//}

//void HAL_UART1_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//    static uint8_t RxState = 0;       // ���ڼ�¼����״̬
//    static uint8_t pRxPacket = 0;     // ��ǰ���յİ�λ��

//    // ȷ��ֻ�������� UART1 ���ж�
//    if (huart->Instance == USART1)
//    {
//        uint8_t RxData = (uint8_t)(huart->Instance->DR & 0x00FF);

//        switch (RxState)
//        {
//            case 0: // �ȴ���ͷ
//                if (RxData == '@' && Serial_RxFlag == 0)
//                {
//                    RxState = 1;
//                    pRxPacket = 0;
//										OLED_ShowString(1, 9, "1");
//                }
//                break;
//                
//            case 1: // ��������
//                if (RxData == '\r')
//                {
//                    RxState = 2;
//										OLED_ShowString(1, 10, "2");
//                }
//                else
//                {
//                    Serial_RxPacket[pRxPacket++] = RxData;
//                }
//                break;
//                
//            case 2: // �ȴ���β
//                if (RxData == '\n')
//                {
//                    Serial_RxPacket[pRxPacket] = '\0'; // ��ֹ�ַ�
//                    Serial_RxFlag = 1;
//                    RxState = 0;
//									OLED_ShowString(4, 1, Serial_RxPacket);
//									printf("%c",Serial_RxPacket[1]);
//                }
//                break;
//                
//            default:
//                RxState = 0;
//                break;
//        }
//				
//        // �������� UART �����ж�
//        HAL_UART_Receive_IT(huart, &RxData, 1);
//    }
//}

void HAL_UART1_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		__HAL_TIM_SET_COUNTER(&htim6,0);							//�����ʱ��7����ֵ	
		if(0 == RxCounter)											//��������ַ���ÿ֡���ݿ�ͷ��������ʱ��
		{
			__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);			//����жϱ�־λ
			HAL_TIM_Base_Start_IT(&htim6);							//����������ʱ��
		}
		RxBuffer[RxCounter] = RxTemp[0];							//�������ݷ����������
		RxCounter++;												//��������1
		HAL_UART_Receive_IT(&huart1,(uint8_t *)RxTemp, REC_LENGTH);	//����ʹ���ж�
	}
	if(huart->Instance == USART2)
	{
		__HAL_TIM_SET_COUNTER(&htim3,0);							//�����ʱ��7����ֵ	
		if(0 == RxCounter2)											//��������ַ���ÿ֡���ݿ�ͷ��������ʱ��
		{
			__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);			//����жϱ�־λ
			HAL_TIM_Base_Start_IT(&htim3);							//����������ʱ��
		}
		RxBuffer2[RxCounter2] = RxTemp2[0];							//�������ݷ����������
		RxCounter2++;												//��������1
		HAL_UART_Receive_IT(&huart2,(uint8_t *)RxTemp2, REC_LENGTH);	//����ʹ���ж�
	}
}


//void usart1_process_data(uint8_t *data, uint16_t length)
//{
//    char *ptr = (char*)data; // ������ת��Ϊ�ַ�ָ��
//    int x, y;
//    
//    // �������ݸ�ʽΪ "x,y\r\n"
//    if (sscanf(ptr, "%d,%d", &x, &y) == 2) {
//        Point point = {x, y};
//        process_coordinates(point);
//    }
//    
//    memset(rx_buffer, 0, UART1_BUFFER_SIZE); // ��ջ�����
//    rx_index = 0; // ��������
//}
