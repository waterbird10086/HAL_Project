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
extern int alg_Set[5];
extern int sign_Set[5];
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define KEY_1 (1<<1)
#define KEY_2 (1<<2)
#define KEY_3 (1<<3)
#define KEY_4 (1<<4)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t key1_flag = 0;
uint8_t key2_flag = 0;
uint8_t key3_flag = 0;
uint8_t key4_flag = 0;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId OLED_TaskHandle;
osThreadId KEY_TaskHandle;
osThreadId myTask_KEYHandle;
osThreadId mode_TaskHandle;
osThreadId U1_TaskHandle;
osThreadId U2_TaskHandle;
osTimerId myTimer01Handle;
osTimerId mode1TimerHandle;
osSemaphoreId myBinarySem01Handle;
osSemaphoreId myBinarySem02Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void mode1(void);
void mode2(void);
void mode3(void);
void RxBuffer_set(void);
void RxBuffer_set2(void);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartOLED_Task(void const * argument);
void StartKEY_Task(void const * argument);
void StartmyTask_KEY(void const * argument);
void Startmode_Task(void const * argument);
void StartU1_Task(void const * argument);
void StartU2_Task(void const * argument);
void Callback01(void const * argument);
void mode1Callback(void const * argument);

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

  /* Create the timer(s) */
  /* definition and creation of myTimer01 */
  osTimerDef(myTimer01, Callback01);
  myTimer01Handle = osTimerCreate(osTimer(myTimer01), osTimerPeriodic, NULL);

  /* definition and creation of mode1Timer */
  osTimerDef(mode1Timer, mode1Callback);
  mode1TimerHandle = osTimerCreate(osTimer(mode1Timer), osTimerPeriodic, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
	osTimerStart(myTimer01Handle,100);
	osTimerStart(mode1TimerHandle,50);
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of OLED_Task */
  osThreadDef(OLED_Task, StartOLED_Task, osPriorityLow, 0, 128);
  OLED_TaskHandle = osThreadCreate(osThread(OLED_Task), NULL);

  /* definition and creation of KEY_Task */
  osThreadDef(KEY_Task, StartKEY_Task, osPriorityNormal, 0, 128);
  KEY_TaskHandle = osThreadCreate(osThread(KEY_Task), NULL);

  /* definition and creation of myTask_KEY */
  osThreadDef(myTask_KEY, StartmyTask_KEY, osPriorityNormal, 0, 128);
  myTask_KEYHandle = osThreadCreate(osThread(myTask_KEY), NULL);

  /* definition and creation of mode_Task */
  osThreadDef(mode_Task, Startmode_Task, osPriorityNormal, 0, 128);
  mode_TaskHandle = osThreadCreate(osThread(mode_Task), NULL);

  /* definition and creation of U1_Task */
  osThreadDef(U1_Task, StartU1_Task, osPriorityNormal, 0, 128);
  U1_TaskHandle = osThreadCreate(osThread(U1_Task), NULL);

  /* definition and creation of U2_Task */
  osThreadDef(U2_Task, StartU2_Task, osPriorityNormal, 0, 128);
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

/* USER CODE BEGIN Header_StartOLED_Task */
/**
* @brief Function implementing the OLED_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartOLED_Task */
void StartOLED_Task(void const * argument)
{
  /* USER CODE BEGIN StartOLED_Task */
  /* Infinite loop */
  for(;;)
  {
//		if(key1_flag)
//		{
//			OLED_ShowString(2,1,"K1");
//		}
//		else if(key2_flag)
//		{
//			OLED_ShowString(2,1,"K2");
//		}
//		else if(key3_flag)
//		{
//			OLED_ShowString(2,1,"K3");
//		}
//		else if(key4_flag)
//		{
//			OLED_ShowString(2,1,"K4");
//		}
//		else
//		{
//			OLED_ShowString(2,1,"  ");
//		}
		OLED_ShowString(1,1,"MODE:");
		OLED_ShowNum(1,6,MODE.MODEFLAT,1);
////		OLED_ShowString(2,1,"LX:     LY:");
////		OLED_ShowString(3,1,"RX:     RY:");
////		OLED_ShowSignedNum(2,4,COORD.LeftX,4);
////		OLED_ShowSignedNum(2,12,COORD.LeftY,4);
////		OLED_ShowSignedNum(3,4,COORD.RightX,4);
////		OLED_ShowSignedNum(3,12,COORD.RightY,4);

		OLED_ShowSignedNum(2,4,PID.MotorA_Velocity_Target_Val,4);
		OLED_ShowSignedNum(2,12,PID.MotorB_Velocity_Target_Val,4);
//		
//		OLED_ShowNum(4,1,alg_Set[0],3);
//		OLED_ShowNum(4,5,alg_Set[1],3);
//		OLED_ShowNum(4,9,alg_Set[2],3);
//		OLED_ShowNum(4,13,alg_Set[3],3);
//		OLED_ShowNum(1,13,alg_Set[4],3);
  }
  /* USER CODE END StartOLED_Task */
}

/* USER CODE BEGIN Header_StartKEY_Task */
/**
* @brief Function implementing the KEY_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartKEY_Task */
void StartKEY_Task(void const * argument)
{
  /* USER CODE BEGIN StartKEY_Task */
  /* Infinite loop */
  for(;;)
  {
    if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==0)
    {
        osDelay(10);
        if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==0)
        {
            osThreadSuspendAll();
            printf("KEY1按下 \n");
            osThreadResumeAll();
            osSignalSet(myTask_KEYHandle,KEY_1);
            //xTaskNotifyGive(myTask01Handle);  //FreeRtos源码函数
            while(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==0)
            {
                osDelay(10);
            }
        }
    }
		
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==0)
    {
        osDelay(10);
        if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==0)
        {
            osThreadSuspendAll();
            printf("KEY2按下 \n");
            osThreadResumeAll();
            osSignalSet(myTask_KEYHandle,KEY_2);
            //xTaskNotifyGive(myTask01Handle);  //FreeRtos源码函数
            while(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==0)
            {
                osDelay(10);
            }
        }
    }
				
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==0)
    {
        osDelay(10);
        if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==0)
        {
            osThreadSuspendAll();
            printf("KEY3按下 \n");
            osThreadResumeAll();
            osSignalSet(myTask_KEYHandle,KEY_3);
            //xTaskNotifyGive(myTask01Handle);  //FreeRtos源码函数
            while(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==0)
            {
                osDelay(10);
            }
        }
    }
				
		if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==0)
    {
        osDelay(10);
        if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==0)
        {
            osThreadSuspendAll();
            printf("KEY4按下 \n");
            osThreadResumeAll();
            osSignalSet(myTask_KEYHandle,KEY_4);
            //xTaskNotifyGive(myTask01Handle);  //FreeRtos源码函数
            while(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==0)
            {
                osDelay(10);
            }
        }
    }
      osDelay(1);
  }
  /* USER CODE END StartKEY_Task */
}

/* USER CODE BEGIN Header_StartmyTask_KEY */
/**
* @brief Function implementing the myTask_KEY thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartmyTask_KEY */
void StartmyTask_KEY(void const * argument)
{
  /* USER CODE BEGIN StartmyTask_KEY */
	osEvent event;
  /* Infinite loop */
  for(;;)
  {
		event=osSignalWait(KEY_1|KEY_2|KEY_3|KEY_4,osWaitForever);
		key1_flag = 0;
		key2_flag = 0;
		key3_flag = 0;
		key4_flag = 0;
		if(event.value.signals&KEY_1)
		{
				key1_flag = 1;
		}
		else if(event.value.signals&KEY_2)
		{
				key2_flag = 1;
		}
		else if(event.value.signals&KEY_3)
		{
				key3_flag = 1;
		}
		else if(event.value.signals&KEY_4)
		{
				key4_flag = 1;
		}

    osDelay(1);
  }
  /* USER CODE END StartmyTask_KEY */
}

/* USER CODE BEGIN Header_Startmode_Task */
/**
* @brief Function implementing the mode_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Startmode_Task */
void Startmode_Task(void const * argument)
{
  /* USER CODE BEGIN Startmode_Task */
  /* Infinite loop */
  for(;;)
  {
//		osTimerStop(mode1TimerHandle);
		
    osDelay(1);
  }
  /* USER CODE END Startmode_Task */
}

/* USER CODE BEGIN Header_StartU1_Task */
/**
* @brief Function implementing the U1_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartU1_Task */
void StartU1_Task(void const * argument)
{
  /* USER CODE BEGIN StartU1_Task */
  /* Infinite loop */
  for(;;)
  {
		/********************************************************************************/  
		osSemaphoreWait(myBinarySem01Handle,100);						//等待二值信号量
		if(RxFlag == 1)													//数据接收完成
		{
			RxBuffer_set();
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
  /* USER CODE END StartU1_Task */
}

/* USER CODE BEGIN Header_StartU2_Task */
/**
* @brief Function implementing the U2_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartU2_Task */
void StartU2_Task(void const * argument)
{
  /* USER CODE BEGIN StartU2_Task */
  /* Infinite loop */
  for(;;)
  {
		/********************************************************************************/  
		osSemaphoreWait(myBinarySem02Handle,100);						//等待二值信号量
		if(RxFlag2 == 1)													//数据接收完成
		{
			RxBuffer_set2();
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
  /* USER CODE END StartU2_Task */
}

/* Callback01 function */
void Callback01(void const * argument)
{
  /* USER CODE BEGIN Callback01 */
	PS2Data();
//  printf("\n定时器%d\n",osKernelSysTick());
  /* USER CODE END Callback01 */
}

/* mode1Callback function */
void mode1Callback(void const * argument)
{
  /* USER CODE BEGIN mode1Callback */
	switch(MODE.MODEFLAT)
		{
			case(0):
							break;
			case(1):mode1();
							break;
			case(2):mode2();
							break;
			case(3):mode3();
							break;
			case(4):
							break;
			case(5):
							break;
			case(6):
							break;
		}
  /* USER CODE END mode1Callback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

int32_t encoderA = 0,encoderB = 0;
uint8_t i2=0,a=0;
encoder_InitTypedef speed;
void mode1(void)
{
	int accel,direc;
	
	speed.encoderA = Read_SPEEDA();
	__HAL_TIM_SetCounter(&htim2, 0);														//清空计数值
	
	speed.encoderB = Read_SPEEDB();
	__HAL_TIM_SetCounter(&htim4, 0);														//清空计数值
	
	printf("%d,%d\r\n" , speed.encoderA , speed.encoderB );//输出转速
	
	accel = COORD.RightY;
	direc = COORD.RightX;
	PID.MotorA_Velocity_Target_Val=-accel-direc;
	PID.MotorB_Velocity_Target_Val=-accel+direc;
	
//	step_run();
	
	motor_speed(VelocityRing_MOTORA_Control(),VelocityRing_MOTORB_Control());								//PID
}

extern int alg_flag=1,slow_flag = 0;
extern int alg[3] = {200,280,0};

void mode2(void)
{
//	inverse_operation(alg_Set[0],alg_Set[1],alg_Set[2]);
	int X,Y,pre,d,g;
	X = alg_Set[0];
	Y = alg_Set[1];
	pre = alg_Set[2];
	d = alg_Set[3];
	g = alg_Set[4];
	
	
	int free = 10;
	
	if(alg_flag==1)
	{
		alg[0] = alg[0]+320*(1-pre/100)/16/free;
		alg[1] = alg[1]-(Y-240)/g*25/free;
		alg[2] = alg[2]-(X-320)/d*75/free;
		
		inverse_operation(alg[0],alg[1],alg[2]);
		alg_move_run();
		
		if(pre>10)
		{
			slow_flag = 1;
			
		}
		alg_flag = 0;
	}
	if (slow_flag == 1){
		int Xpre,Ypre;
		Xpre = X/640*100;
		Ypre = Y/480*100;
		if(Xpre<45)
		{
			alg[2] = alg[2] - 1; 
		}
		if(Xpre>55){
			alg[2] = alg[2] + 1; 
		}
//		if(Ypre<45)
//		{
//			alg[1] = alg[1] + 2; 
//		}
//		if(Ypre>55){
//			alg[1] = alg[1] - 2; 
//		}		
		inverse_operation(alg[0],alg[1],alg[2]);
		alg_move_run();
		
		slow_flag = 0;
}
	
	
	for(int m = 0; m<5; m++)							//打印接收数组存储的内容
		printf("%d",alg_Set[m]);
	
}

int Angle_A=90,Angle_B=90,Angle_C=90;

void mode3(void)
{
	alg[0] = 200;
	alg[1] = 280;
	alg[2] = 0;
	
	Angle_A=Angle_A+COORD.RightX*0.01;
	if(Angle_A>=180)Angle_A=180;
	if(Angle_A<=0)Angle_A=0;
	PCA_MG9XX(0,Angle_A);

	Angle_B=COORD.RightY*0.01+Angle_B;
	if(Angle_B>=120)Angle_B=120;
	if(Angle_B<=90)Angle_B=90;
	PCA_MG9XX(1,Angle_B);

	Angle_C=COORD.LeftY*0.01+Angle_C;
	if(Angle_C>=100)Angle_C=100;
	if(Angle_C<=60)Angle_C=60;
	PCA_MG9XX(2,Angle_C);

}

void RxBuffer_set(void)
{
  static uint8_t Rxnum = 5;     // 位数
	
	// 去掉开头的 '@' 字符
    char *data = RxBuffer + 1;  

    // 检查数据长度是否符合预期
    if (strlen(data) < 15) {
        printf("数据长度不足。\n");
    }

    // 解析数据
    int values[5];
    sscanf(data, "%3d%3d%3d%3d%3d", &values[0], &values[1], &values[2],&values[3], &values[4]);

    // 保存到 alg_Set[3]
    alg_Set[0] = values[0];
    alg_Set[1] = values[1];
    alg_Set[2] = values[2];
		alg_Set[3] = values[3];
		alg_Set[4] = values[4];
		alg_flag = 1;
		
	for(int m = 0; m<Rxnum; m++)							//打印接收数组存储的内容
				printf("%d",alg_Set[m]);
}

#define MAX_VALUES 7  // 假设最多有10个值

void RxBuffer_set2(void)
{

    int count = 0;  // Counter for the number of values processed

    // Tokenize the input string using ':' as the delimiter
    char *token = strtok(RxBuffer2, ":");
    while (token != NULL && count < MAX_VALUES) {
        // Remove any trailing newline character
        char *newline = strchr(token, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }

        // Convert the token to an integer and store it in the sign_Set array
        sign_Set[count] = atoi(token);

        // Display the number on the OLED screen
        

        // Move to the next token
        token = strtok(NULL, ":");
        count++;
    }

    // If the maximum number of values is reached, display a message
    if (count >= MAX_VALUES) {
        OLED_ShowNum(4, 14, 0, 1);
			count = 0;
    }
		
		OLED_ShowNum(3, 1,sign_Set[4], 2);
		OLED_ShowNum(3, 4,sign_Set[5], 2);
		OLED_ShowNum(3, 8,sign_Set[6], 2);
		
		if(sign_Set[6] == 5)
		{
			    PID.MotorA_Velocity_Target_Val = 0;
					PID.MotorB_Velocity_Target_Val = 0;
		}
		
}
/* USER CODE END Application */

