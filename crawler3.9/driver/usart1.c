#include "usart1.h"

#include <stdio.h>
#include <string.h>

uint8_t rx_buffer[UART1_BUFFER_SIZE]; // 接收缓冲区
uint16_t rx_index = 0; // 接收缓冲区索引
int Point_data[3]={115,230,0};
char received_char;
//static char char_rx_buffer[64]; // 接收缓冲区大小适配实际情况

typedef struct {
    int x;
    int y;
		int z;
		int pre;
} Point;

//启动接收函数
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
    // 处理坐标数据的函数，可以在这里进行打印、保存或执行其他操作
		if(MODE.MODEFLAT == 5)
		{
			printf("Received coordinates: x=%d, y=%d, pre=%d\r\n", point.x, point.y, point.pre);
			alg_Yolo(point.x,point.y,point.pre);

		}
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
    // 在这里对接收到的数据进行处理，例如打印、解析、存储等等
    // 注意：接收到的数据长度为length，不包括结束符号'\n'
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
		
		char *ptr = (char*)data; // 将数据转换为字符指针
    int x, y, z;
    
    // 假设数据格式为 "x,y\r\n"
//    if (sscanf(ptr, "%d,%d,%d", &x, &y, &z) == 3) {
//        Point point = {x, y, z};
//        process_coordinates(point);
//    }
		
		if(sscanf(ptr,"%d %d %d", &x, &y, &z )== 3 )
		{
				Point point = {x, y, z};
        process_coordinates(point);
		}
		memset(rx_buffer, 0, UART1_BUFFER_SIZE);//将缓冲区里面的数据全部清0
}


//void HAL_UART1_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//        if (rx_index < UART1_BUFFER_SIZE - 1) // 缓冲区还有空间
//        {
//            if (rx_buffer[rx_index - 1] != 0XFE) // 如果上一个字符不是结束符号
//            {
//                rx_buffer[rx_index++] = (uint8_t)(huart->Instance->DR & 0x00FF); // 将接收到的字符存储到缓冲区中
//            }
//            if(rx_buffer[rx_index - 1] == 0XFE)// 如果上一个字符是结束符号
//            {
//                // 对接收到的数据进行处理
//                usart1_process_data(rx_buffer, rx_index - 1);
//            }		
////							if (received_char == 'E' && rx_index >= 7)
////							{
////									int x,y,z;
////									if (sscanf(char_rx_buffer, "FF %d %d %d FE", &x, &y, &z) == 3) {
////                    Point point = {x, y, z};
////                    process_coordinates(point);
////									}
////									memset(char_rx_buffer, 0, sizeof(char_rx_buffer)); // 清空接收缓冲区
////									rx_index = 0;
////							}
//        }
//        else // 缓冲区已满
//        {
//            rx_index = 0; // 清空缓冲区
//						memset(rx_buffer, 0, UART1_BUFFER_SIZE);
//        }
//				HAL_UART1_Receive_IT;//启动下一次接收	
//}

void HAL_UART1_RxCpltCallback(UART_HandleTypeDef *huart)
{
    static uint8_t rx_byte;
    static uint8_t rx_state = 0; // 接收状态，0表示等待起始字节，1表示接收数据，2表示接收结束字节
    static uint8_t rx_data[3]; // 存储接收到的数据
    static uint8_t rx_count = 0; // 已接收的数据计数
		static uint8_t callup = 0;
    
    rx_byte = (uint8_t)(huart->Instance->DR & 0x00FF); // 读取接收到的字节
    
    if(rx_state == 0) {
        if(rx_byte == 0xFF) {
            rx_state = 1; // 进入接收数据状态
            rx_count = 0; // 重置数据计数
        }
				
				else if(rx_byte == 0xFD)
				{
					callup = 1;
				}
				else if(rx_byte == 0xFC)
				{
					callup = 0;
					OLED_ShowString(1,10,"OFF");
					
//					inverse_operation(-145,300,0);
//					alg_move_run();

				}
					
				
    } else if(rx_state == 1) {
        if(rx_byte == 0xFE) {
            if(rx_count == 3 && callup == 1) { // 判断是否接收到了三个数据
                // 解析并处理接收到的数据
                int x = rx_data[0];
                int y = rx_data[1];
                int z = rx_data[2];
								OLED_ShowNum(2,1,rx_data[0],3);
								OLED_ShowNum(2,5,rx_data[1],3);
								OLED_ShowNum(2,10,rx_data[2],3);
                Point point = {x, y, z};
                process_coordinates(point);
            }
            rx_state = 0; // 回到等待起始字节状态
        } else {
            // 解析接收到的十六进制字符并存储
            if(rx_count < 3) {
                rx_data[rx_count++] = rx_byte;
            }
        }
    }
    
    // 启动下一次接收
    HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
}





//void usart1_process_data(uint8_t *data, uint16_t length)
//{
//    char *ptr = (char*)data; // 将数据转换为字符指针
//    int x, y;
//    
//    // 假设数据格式为 "x,y\r\n"
//    if (sscanf(ptr, "%d,%d", &x, &y) == 2) {
//        Point point = {x, y};
//        process_coordinates(point);
//    }
//    
//    memset(rx_buffer, 0, UART1_BUFFER_SIZE); // 清空缓冲区
//    rx_index = 0; // 重置索引
//}
