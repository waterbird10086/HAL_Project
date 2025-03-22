/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "stdio.h"
#include <string.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId U1_TaskHandle;
osThreadId U2_TaskHandle;
osSemaphoreId myBinarySem01Handle;
osSemaphoreId myBinarySem02Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void U1_Task02(void const * argument);
void U2_TaskStart(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of myBinarySem01 */
  osSemaphoreDef(myBinarySem01);
  myBinarySem01Handle = osSemaphoreCreate(osSemaphore(myBinarySem01), 1);

  /* definition and creation of myBinarySem02 */
  osSemaphoreDef(myBinarySem02);
  myBinarySem02Handle = osSemaphoreCreate(osSemaphore(myBinarySem02), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of U1_Task */
  osThreadDef(U1_Task, U1_Task02, osPriorityNormal, 0, 128);
  U1_TaskHandle = osThreadCreate(osThread(U1_Task), NULL);

  /* definition and creation of U2_Task */
  osThreadDef(U2_Task, U2_TaskStart, osPriorityIdle, 0, 128);
  U2_TaskHandle = osThreadCreate(osThread(U2_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	HAL_UART_Receive_IT(&huart1,(uint8_t *)RxTemp, REC_LENGTH);
	HAL_UART_Receive_IT(&huart2,(uint8_t *)RxTemp2, REC_LENGTH);
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_U1_Task02 */
/**
* @brief Function implementing the U1_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_U1_Task02 */
void U1_Task02(void const * argument)
{
  /* USER CODE BEGIN U1_Task02 */
  /* Infinite loop */
  for(;;)
  {
    /********************************************************************************/  
		osSemaphoreWait(myBinarySem01Handle,100);						//等待二值信号量
		if(RxFlag == 1)													//数据接收完成
		{
			for(int i = 0; i<RxCounter; i++)							//打印接收数组存储的内容
				printf("%c",RxBuffer[i]);	
					 printf("\r\n");											//打印完成换行
			RxFlag = 0;													//接收标志清零
			RxCounter = 0;												//接收计数清零
			memset(RxBuffer ,0, MAX_REC_LENGTH);						//清空接收数组
		}
		/********************************************************************************/
    osDelay(1);
  }
  /* USER CODE END U1_Task02 */
}

/* USER CODE BEGIN Header_U2_TaskStart */
/**
* @brief Function implementing the U2_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_U2_TaskStart */
void U2_TaskStart(void const * argument)
{
  /* USER CODE BEGIN U2_TaskStart */
  /* Infinite loop */
  for(;;)
  {
		/********************************************************************************/  
		osSemaphoreWait(myBinarySem02Handle,100);						//等待二值信号量
		if(RxFlag2 == 1)													//数据接收完成
		{
			for(int i = 0; i<RxCounter2; i++)							//打印接收数组存储的内容
				printf("%c",RxBuffer2[i]);	
					 printf("\r\n");											//打印完成换行
			RxFlag2 = 0;													//接收标志清零
			RxCounter2 = 0;												//接收计数清零
			memset(RxBuffer2 ,0, MAX_REC_LENGTH);						//清空接收数组
		}
		/********************************************************************************/
    osDelay(1);
  }
  /* USER CODE END U2_TaskStart */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

