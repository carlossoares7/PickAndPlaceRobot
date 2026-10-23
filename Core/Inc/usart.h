/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "adc.h"
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */

/********************************************************** DEFINES ************************************************************************/

#define BFFTX_SIZE  256
#define BUFFRX_SIZE 256
#define CR_CHAR     13
#define LF_CHAR     10
#define MINIMUM_ANGLE 0
#define MAXIMUM_ANGLE 180


/********************************************************   END DEFINES   ******************************************************************/

typedef enum
{
   READY,
   BUSY,
   STAND_BY

}robotStatus_e;


typedef enum
{
	NO_DATA,
	JOINTS,
	ANGLES

}usartTxmode_e;

typedef enum{
	NONE,
	PICK,
	PLACE

}robotClawmode_e;


typedef struct{

	  char       *InData;
	  char       BffTx[BFFTX_SIZE];
	  char       cirBff[BUFFRX_SIZE];
      uint8_t    frameRxNumber;
	  uint8_t    TxAmount;
	  uint8_t    actNumber;
	  uint8_t    txData;
	  uint8_t    TxPosition;
	  uint8_t    startRxBuffer;
	  uint8_t    BffTxSz;                           // tamanho do buffer de transmissão
	  uint32_t   Tick;
	  int        btAngle;

  }uartData_t;

typedef struct{

	int X;
	int Y;
	int Z;

}robotAngle_t;

typedef struct{

	int rawX1;
	int rawX2;
	int rawX3;
	int rawX4;
	int actX1;
	int actX2;
	int actX3;
	int actX4;
	int newX1;
	int newX2;
	int newX3;
	int newX4;

}robotJoint_t;

typedef struct{

	robotStatus_e   robotStatus;
	robotAngle_t    robotAngle;
	robotJoint_t    robotJoint;
	usartTxmode_e   usartTxmode;
	robotClawmode_e robotClawmode;
	uint8_t         selfTestPWM;
	uint8_t         angleChange;
	uint8_t         endOpFlag;

}robotData_t;
 /************************************************************ END STRUCTS  ****************************************************************/

 /******************************************************   FUNCTIONS PROTOTYPES   **********************************************************/



  /* Receiver Function */
  void USART_Receiver(USART_TypeDef *USARTx);

  /* Monta um buffer circular */
  void rxBuffer(USART_TypeDef *USARTx, char data);


  void rxHandler(USART_TypeDef *USARTx, char *inData);

  void txBilder(USART_TypeDef *USARTx);

  void TxRxITCaller(USART_TypeDef *USARTx);



  extern uartData_t uartData;

  extern robotData_t robotData;

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

