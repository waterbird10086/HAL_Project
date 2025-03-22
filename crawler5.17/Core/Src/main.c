/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
//	int alg_Set[3] = {45,-25,0};
	int alg_Set[3] = {-145,200,0};
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM8_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);

	OLED_Init();  //初始化OLED
	usart1_Init();
//KEY_EXIT_Init();											//板子设计问题

	PID_Param_Init();
//	alg_Init();

	PCA_MG9XX_Init(60,90);
	alg_set_move_action(alg_Set);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//	OLED_ShowString(1, 1, "1HelloWorld!");
	printf("HelloWorld\r\n");
  while (1)
  {
		PS2Data();
		OLED_ShowString(3,1,"LX:     LY:");
		OLED_ShowString(4,1,"RX:     RY:");
		OLED_ShowSignedNum(3,4,COORD.LeftX,4);
		OLED_ShowSignedNum(3,12,COORD.LeftY,4);
		OLED_ShowSignedNum(4,4,COORD.RightX,4);
		OLED_ShowSignedNum(4,12,COORD.RightY,4);
//		Servo4_SetAngle(90);
//		Servo2_SetAngle(90);
//		Servo3_SetAngle(180);
		
//		PCA_MG9XX(0,90);
//		PCA_MG9XX(1,90);
//		PCA_MG9XX(2,180);
		
		int accel,direc;
		switch(MODE.MODEFLAT)
		{
			case(0):HAL_TIM_Base_Stop(&htim1);
							stop();
							break;
			case(1):HAL_TIM_Base_Stop(&htim1);
							stop();
							alg_move_run();
//							yoloServo();
							break;
			case(2):PS2Servo();
							break;
			case(3)://motor_speed(-150,-150);
							HAL_TIM_Base_Start_IT(&htim1);                  //开启定时器的中断
							accel = COORD.RightY/4;
							direc = COORD.RightX/5;
							PID.MotorA_Velocity_Target_Val=-accel+direc;
							PID.MotorB_Velocity_Target_Val=-accel-direc;
							break;
			case(4):	
//							PCA_MG9XX(0,90);
//							PCA_MG9XX(1,90);
//							PCA_MG9XX(2,180);
				alg_set_move_action(alg_Set);
							inverse_operation(-145,200,0);
							alg_move_run();
							break;
			case(5):HAL_TIM_Base_Stop(&htim1);
							stop();
							break;
			case(6):HAL_TIM_Base_Start_IT(&htim1);                  //开启定时器的中断
							step_run();
							break;
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
KEY KEY_t;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == KEY1_Pin)
    {
				KEY_t.KEY1_val = KEY1_Read;
				printf("KEY1");
				OLED_ShowString(2, 1, "KEY1!");
//        motor_speed(0,0);
    }
    else if(GPIO_Pin == KEY2_Pin)
    {
        KEY_t.KEY2_val = KEY2_Read;
    }
    else if(GPIO_Pin == KEY3_Pin)
    {
        KEY_t.KEY3_val = KEY3_Read;
    }
		else if(GPIO_Pin == KEY4_Pin)
    {
        KEY_t.KEY4_val = KEY4_Read;
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
