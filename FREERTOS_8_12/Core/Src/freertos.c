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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct
{
	uint32_t var1;
	uint32_t var2;
	uint8_t var3;
}Amail_TypeDef;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

osMailQId myosMailQId;

/* USER CODE END Variables */
osThreadId Task_KEYHandle;
osThreadId myTask01Handle;
osThreadId myTask02Handle;
osMessageQId myQueue01Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartTask_KEY(void const * argument);
void StartTask01(void const * argument);
void StartTask02(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

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

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  osMailQDef(mail,32,Amail_TypeDef);
	myosMailQId=osMailCreate(osMailQ(mail),NULL);
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of myQueue01 */
  osMessageQDef(myQueue01, 16, uint32_t);
  myQueue01Handle = osMessageCreate(osMessageQ(myQueue01), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Task_KEY */
  osThreadDef(Task_KEY, StartTask_KEY, osPriorityNormal, 0, 128);
  Task_KEYHandle = osThreadCreate(osThread(Task_KEY), NULL);

  /* definition and creation of myTask01 */
  osThreadDef(myTask01, StartTask01, osPriorityNormal, 0, 128);
  myTask01Handle = osThreadCreate(osThread(myTask01), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityBelowNormal, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartTask_KEY */
/**
* @brief Function implementing the Task_KEY thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_KEY */
void StartTask_KEY(void const * argument)
{
  /* USER CODE BEGIN StartTask_KEY */
  /* Infinite loop */
  Amail_TypeDef *pTMail;
  uint32_t ProducerValue1=0;
  uint32_t ProducerValue2=0;
  uint8_t ProducerValue3=0;
  for(;;)
  {
    if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin)==0)
    {
        osDelay(10);
        if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin)==0)
        {
            osThreadSuspendAll();
            printf("KEY按下\n"); 
            osThreadResumeAll();
            pTMail=osMailAlloc(myosMailQId,osWaitForever);
            pTMail->var1=ProducerValue1;
            pTMail->var2=ProducerValue2;
            pTMail->var3=ProducerValue3;
            if(osMailPut(myosMailQId,pTMail)==osOK)
            {
                ProducerValue1++;
                ProducerValue2+=2;
                ProducerValue3+=3;
            }
            while(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin)==0)
            {
                osDelay(10);
            }
        }
    }
      osDelay(1);
  }
  /* USER CODE END StartTask_KEY */
}

/* USER CODE BEGIN Header_StartTask01 */
/**
* @brief Function implementing the myTask01 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask01 */
void StartTask01(void const * argument)
{
  /* USER CODE BEGIN StartTask01 */
  /* Infinite loop */
  osEvent event;
  Amail_TypeDef *pRmail;
  for(;;)
  {
      event=osMailGet(myosMailQId,osWaitForever);
      if(event.status==osEventMail)
      {
          pRmail=event.value.p;
          printf("%d %d %d \n",pRmail->var1,pRmail->var2,pRmail->var3);
          osMailFree(myosMailQId,pRmail); //将分配的内存给清除
      }
      osDelay(1);
  }
  /* USER CODE END StartTask01 */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
//  osEvent event;
//  DataGroup *myDataGroup_r;
  for(;;)
  {
//      event=osMessageGet(myQueue01Handle,osWaitForever);
//      if(event.status==osEventMessage) //判断是否是消息队列
//      {
//          myDataGroup_r=event.value.p;
//          osThreadSuspendAll();
//          printf("任务2接受的数据： %d\n",myDataGroup_r->var1);
//          printf("任务2接受的数据： %d\n",myDataGroup_r->var2);
//          printf("任务2接受的数据： %d\n",myDataGroup_r->var3);
//          osThreadResumeAll();
//      }
    osDelay(1);
  }
  /* USER CODE END StartTask02 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

