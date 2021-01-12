/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_1_Pin GPIO_PIN_0
#define LED_1_GPIO_Port GPIOC
#define LED_2_Pin GPIO_PIN_1
#define LED_2_GPIO_Port GPIOC
#define LED_3_Pin GPIO_PIN_2
#define LED_3_GPIO_Port GPIOC
#define LED_4_Pin GPIO_PIN_3
#define LED_4_GPIO_Port GPIOC
#define SPI1_NCS_Pin GPIO_PIN_4
#define SPI1_NCS_GPIO_Port GPIOA
#define SPI1_NCS_EXTI_IRQn EXTI4_IRQn
#define LED_5_Pin GPIO_PIN_4
#define LED_5_GPIO_Port GPIOC
#define LED_6_Pin GPIO_PIN_5
#define LED_6_GPIO_Port GPIOC
#define Matrix_R0_Pin GPIO_PIN_0
#define Matrix_R0_GPIO_Port GPIOB
#define Matrix_G0_Pin GPIO_PIN_1
#define Matrix_G0_GPIO_Port GPIOB
#define Matrix_B0_Pin GPIO_PIN_2
#define Matrix_B0_GPIO_Port GPIOB
#define Matrix_D_Pin GPIO_PIN_10
#define Matrix_D_GPIO_Port GPIOB
#define Matrix_CLK_Pin GPIO_PIN_12
#define Matrix_CLK_GPIO_Port GPIOB
#define Matrix_LAT_Pin GPIO_PIN_13
#define Matrix_LAT_GPIO_Port GPIOB
#define Matrix_OE_Pin GPIO_PIN_14
#define Matrix_OE_GPIO_Port GPIOB
#define LED_7_Pin GPIO_PIN_6
#define LED_7_GPIO_Port GPIOC
#define LED_8_Pin GPIO_PIN_7
#define LED_8_GPIO_Port GPIOC
#define LED_0_Pin GPIO_PIN_8
#define LED_0_GPIO_Port GPIOC
#define LED_CLK_Pin GPIO_PIN_10
#define LED_CLK_GPIO_Port GPIOC
#define Matrix_C_Pin GPIO_PIN_3
#define Matrix_C_GPIO_Port GPIOB
#define Matrix_B_Pin GPIO_PIN_4
#define Matrix_B_GPIO_Port GPIOB
#define Matrix_A_Pin GPIO_PIN_5
#define Matrix_A_GPIO_Port GPIOB
#define Matrix_E_Pin GPIO_PIN_6
#define Matrix_E_GPIO_Port GPIOB
#define Matrix_B1_Pin GPIO_PIN_7
#define Matrix_B1_GPIO_Port GPIOB
#define Matrix_G1_Pin GPIO_PIN_8
#define Matrix_G1_GPIO_Port GPIOB
#define Matrix_R1_Pin GPIO_PIN_9
#define Matrix_R1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
