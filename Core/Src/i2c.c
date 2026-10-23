/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    i2c.c
  * @brief   This file provides code for the configuration
  *          of the I2C instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "i2c.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

I2C_HandleTypeDef hi2c1;

/* I2C1 init function */
void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00100F17;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */
    LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_PCLK1);

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB7     ------> I2C1_SDA
    PB8     ------> I2C1_SCL
    */
    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF6_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB7     ------> I2C1_SDA
    PB8     ------> I2C1_SCL
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8);

  /* USER CODE BEGIN I2C1_MspDeInit 1 */

  /* USER CODE END I2C1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void oledInit(void){

	   if (ssd1306_Init(&hi2c1) != 0) {
	        Error_Handler();
	      }
	      HAL_Delay(50);

	      ssd1306_Fill(Black);
	      ssd1306_UpdateScreen(&hi2c1);

	      HAL_Delay(50);

	      // Write data to local screenbuffer
	      ssd1306_SetCursor(0, 0);
	      ssd1306_WriteString("ROBOT", Font_11x18, White);

	      ssd1306_SetCursor(0, 36);
	      ssd1306_WriteString("CONTROL", Font_11x18, White);


	      // Copy all data from local screenbuffer to the screen
	      ssd1306_UpdateScreen(&hi2c1);
	      HAL_Delay(1000);
	      ssd1306_Fill(Black);

  }


void showData(void)
{
	char bff[50];

	if(robotData.usartTxmode == JOINTS)
	  {
		  //ssd1306_Fill(Black);
	      ssd1306_UpdateScreen(&hi2c1);
          snprintf(bff,50,"X1: %d",robotData.robotJoint.actX1);
	      ssd1306_SetCursor(0, 8);
	      ssd1306_WriteString(bff, Font_7x10, White);

	      snprintf(bff,50,"X2: %d",robotData.robotJoint.actX2);
	      ssd1306_SetCursor(0,17);
	      ssd1306_WriteString(bff, Font_7x10, White);

	      snprintf(bff,50,"X3: %d",robotData.robotJoint.actX3);
	      ssd1306_SetCursor(0,28);
	      ssd1306_WriteString(bff, Font_7x10, White);

	      snprintf(bff,50,"X4: %d",robotData.robotJoint.actX4);
	     	      ssd1306_SetCursor(0,38);
	     	      ssd1306_WriteString(bff, Font_7x10, White);

	  }
	else if(robotData.usartTxmode == ANGLES)
	  {
		  ssd1306_Fill(Black);
	      ssd1306_UpdateScreen(&hi2c1);
	      snprintf(bff,50,"X: %d",robotData.robotAngle.X);
	      ssd1306_SetCursor(0, 8);
	      ssd1306_WriteString(bff, Font_7x10, White);

	      snprintf(bff,50,"Y: %d",robotData.robotAngle.Y);
	      ssd1306_SetCursor(0,17);
	      ssd1306_WriteString(bff, Font_7x10, White);

	      snprintf(bff,50,"Z: %d",robotData.robotAngle.Z);
	      ssd1306_SetCursor(0,28);
	      ssd1306_WriteString(bff, Font_7x10, White);

	  }
	if(robotData.usartTxmode == NO_DATA)
		  {




		  }


}
/* USER CODE END 1 */
