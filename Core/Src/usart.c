/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "robot_control.h"
uartData_t uartData = {0};
robotData_t robotData ={0};
/* USER CODE END 0 */

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK1);

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);
  /**USART1 GPIO Configuration
  PC4   ------> USART1_TX
  PC5   ------> USART1_RX
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USART1 DMA Init */

  /* USART1_RX Init */
  LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMAMUX_REQ_USART1_RX);

  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_LOW);

  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_CIRCULAR);

  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);

  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);

  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_BYTE);

  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_BYTE);

  /* USART1_TX Init */
  LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_2, LL_DMAMUX_REQ_USART1_TX);

  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PRIORITY_LOW);

  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MODE_NORMAL);

  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PERIPH_NOINCREMENT);

  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MEMORY_INCREMENT);

  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PDATAALIGN_BYTE);

  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MDATAALIGN_BYTE);

  /* USART1 interrupt Init */
  NVIC_SetPriority(USART1_IRQn, 0);
  NVIC_EnableIRQ(USART1_IRQn);

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART1, &USART_InitStruct);
  LL_USART_SetTXFIFOThreshold(USART1, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_SetRXFIFOThreshold(USART1, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_DisableFIFO(USART1);
  LL_USART_ConfigAsyncMode(USART1);

  /* USER CODE BEGIN WKUPType USART1 */

  /* USER CODE END WKUPType USART1 */

  LL_USART_Enable(USART1);

  /* Polling USART1 initialisation */
  while((!(LL_USART_IsActiveFlag_TEACK(USART1))) || (!(LL_USART_IsActiveFlag_REACK(USART1))))
  {
  }
  /* USER CODE BEGIN USART1_Init 2 */
LL_USART_EnableIT_RXNE_RXFNE(USART1);
  /* USER CODE END USART1_Init 2 */

}

/* USER CODE BEGIN 1 */

//========================================================= USART RECEIVER  ====================================================================
void USART_Receiver(USART_TypeDef *USARTx){

	uint8_t received_char;

  		  received_char = LL_USART_ReceiveData8(USARTx);

  		//  LL_USART_TransmitData8(USARTx, received_char);


  		  rxBuffer(USARTx,received_char);


  		 if (LL_USART_IsActiveFlag_ORE(USARTx))
  			 {

  		    	LL_USART_ClearFlag_ORE(USARTx);
  		    }


} //====================================================  END USART RECEIVER   ================================================================


//=========================================================  RXBUFFER   =======================================================================

void rxBuffer(USART_TypeDef *USARTx, char data)
{


uint16_t sz;

		if(uartData.actNumber == BUFFRX_SIZE){
				    	uartData.actNumber = 0;
				   }

	 uartData.cirBff[uartData.actNumber] = data;


	 if(uartData.cirBff[uartData.actNumber]== CR_CHAR  ||
	    uartData.cirBff[uartData.actNumber]== LF_CHAR   )
	 {
		 sz = uartData.actNumber+1;
		 uartData.InData = (char*)malloc(sz);


		 snprintf(uartData.InData,sz,"%s",uartData.cirBff);
		 rxHandler(USARTx, uartData.InData);


		 uartData.actNumber = -1;


		 free(uartData.InData);
	 }


      uartData.actNumber++;

}  //=========================================================  END RXBUFFER  ===============================================================


void rxHandler(USART_TypeDef *USARTx,char *inData)
{



      if (sscanf(inData,"X1 :%d ,X2 : %d ,X3 : %d,X4 : %d ",
		   &robotData.robotJoint.rawX1,&robotData.robotJoint.rawX2,
		   &robotData.robotJoint.rawX3,&robotData.robotJoint.rawX4)){

    	robotData.robotJoint.newX1 = map(robotData.robotJoint.rawX1,MINIMUM_ANGLE,MAXIMUM_ANGLE,START_ANGLE,END_ANGLE);
    	robotData.robotJoint.newX2 = map(robotData.robotJoint.rawX2,MINIMUM_ANGLE,MAXIMUM_ANGLE,START_ANGLE,END_ANGLE);
    	robotData.robotJoint.newX3 = map(robotData.robotJoint.rawX3,MINIMUM_ANGLE,MAXIMUM_ANGLE,START_ANGLE,END_ANGLE);
    	robotData.robotJoint.newX4 = map(robotData.robotJoint.rawX4,MINIMUM_ANGLE,MAXIMUM_ANGLE,START_ANGLE,END_ANGLE);



	  robotData.usartTxmode = JOINTS;
	  robotData.endOpFlag =0;

	  if(robotData.robotJoint.newX1 < START_ANGLE){

		  robotData.robotJoint.newX1 = START_ANGLE;
	  }
	  else if(robotData.robotJoint.newX2 < MIN_PWM_AXIS_2){

		  robotData.robotJoint.newX2 = MIN_PWM_AXIS_2;
	  }
	  else if(robotData.robotJoint.newX3 < MIN_PWM_AXIS_3){

		  robotData.robotJoint.newX3 = MIN_PWM_AXIS_3;

	  }
	  else if(robotData.robotJoint.newX4 < MIN_PWM_GAR){

	  		  robotData.robotJoint.newX4 =  MIN_PWM_GAR;

	  	  }


	  else if(robotData.robotJoint.newX1 > END_ANGLE){

		  robotData.robotJoint.newX1 = END_ANGLE;
	  }
	  else if(robotData.robotJoint.newX2 > MAX_PWM_AXIS_2){

	  	  robotData.robotJoint.newX2 = MAX_PWM_AXIS_2;

	  }
	  else if(robotData.robotJoint.newX3 > MAX_PWM_AXIS_3){

		  robotData.robotJoint.newX3 = MAX_PWM_AXIS_3;
	  }
	  else if(robotData.robotJoint.newX4 > END_ANGLE){

	  		  robotData.robotJoint.newX4 = MIN_PWM_GAR;
	  	  }
	  // TIM1->CCR1  = robotData.robotJoint.X1;
	  // TIM1 ->CCR2 = robotData.robotJoint.X1;
	  // TIM15->CCR1 = robotData.robotJoint.X1;
	  // TIM15->CCR2 = robotData.robotJoint.X1;

	  //SET_JOINT(&robotData.robotJoint);
	  if((robotData.robotJoint.newX1 != robotData.robotJoint.actX1) ||
	     (robotData.robotJoint.newX2 != robotData.robotJoint.actX2) ||
	     (robotData.robotJoint.newX3 != robotData.robotJoint.actX3) ||
		 (robotData.robotJoint.newX4 != robotData.robotJoint.actX4)  )
	  {
	   robotData.angleChange =1;
	  }

  }

  else if ((sscanf(inData,"X :%d ,Y : %d ,Z : %d",
 		   &robotData.robotAngle.X,&robotData.robotAngle.Y,&robotData.robotAngle.Z)) ||
		    sscanf(inData,"0xA2;X%d;Y%d;Z%d",
		   &robotData.robotAngle.X,&robotData.robotAngle.Y,&robotData.robotAngle.Z)){

	  robotData.usartTxmode = ANGLES;

 	  if(robotData.robotAngle.X >= MINIMUM_ANGLE && robotData.robotAngle.X <= MAXIMUM_ANGLE){

 		  //robotAngle.joint_1 = X1_Angle;
 	  }
 	  else if(robotData.robotAngle.Y >= MINIMUM_ANGLE && robotData.robotAngle.Y <= MAXIMUM_ANGLE){

 	  		//  robotAngle.joint_2 = X2_Angle;
 	  	  }
 	  else if(robotData.robotAngle.Z >= MINIMUM_ANGLE && robotData.robotAngle.Z <= MAXIMUM_ANGLE){

 	  	  		 // robotAngle.joint_3 = X3_Angle;
 	  	  	  }


   }
  else if(strcmp(inData,"fim")== 0)
  {
	  robotData.endOpFlag =1;
	 //endOperation();
  }
  else if(strcmp(inData,"abrir-garra")== 0)
    {
	 // robotData.robotJoint.actX4 =
	  //TIM15->CCR2 = robotData.robotJoint.actX4;
	  robotData.robotJoint.newX4 = MIN_PWM_GAR;
	  robotData.angleChange =1;

    }
  else if(strcmp(inData,"fechar-garra")== 0)
     {
	  //robotData.robotJoint.actX4 = END_ANGLE;
	 // TIM15->CCR2 = robotData.robotJoint.actX4;
 	  robotData.robotJoint.newX4 = END_ANGLE;
 	  robotData.angleChange =1;

     }
  else {

	   robotData.usartTxmode = NO_DATA;
   }

    	      txBilder(USART1);

} // end rxHandler


void txBilder(USART_TypeDef *USARTx){

  if(robotData.usartTxmode == JOINTS)
  {
	  uartData.BffTxSz = snprintf(uartData.BffTx,BFFTX_SIZE,"X1_POSITION: %d\r\nX2_POSITION: %d\r\nX3_POSITION: %d\r\n",
			                      robotData.robotJoint.newX1,
								  robotData.robotJoint.newX2,
								  robotData.robotJoint.newX3);

	  LL_USART_EnableIT_TXE(USARTx);
  }else if(robotData.usartTxmode == ANGLES)
  {
	  uartData.BffTxSz = snprintf(uartData.BffTx,BFFTX_SIZE,"X_Angle: %d\r\nY_Angle: %d\r\nZ_Angle: %d\r\n",
	  			                  robotData.robotAngle.X,
								  robotData.robotAngle.Y,
								  robotData.robotAngle.Z);
	  LL_USART_EnableIT_TXE(USARTx);

  }

}

//=====================================================  TXDATATRANSMITTER   ================================================================
void TxDataTransmitter(USART_TypeDef *USARTx){

//txBffBilder();

	 if (uartData.TxPosition == (uartData.BffTxSz - 1))
	   {
	     /* Disable TXE interrupt */
	     LL_USART_DisableIT_TXE(USARTx);

	     /* Enable TC interrupt */
	     LL_USART_EnableIT_TC(USARTx);
	   }


	 LL_USART_TransmitData8(USARTx,uartData.BffTx[uartData.TxPosition++]);



} //===================================================== END TXDATATRANSMITTER   ===========================================================


//===========================================  UART_TransmitComplete_Callback   =============================================================

void UART_TransmitComplete_Callback(USART_TypeDef *USARTx)
{
 // if (uartData.TxPosition == sizeof(uartData.BffTx)||
	//   LL_USART_IsActiveFlag_TC(USART2))
  //{
	  uartData.TxPosition = 0;
	  LL_USART_ClearFlag_TC(USARTx);
    /* Disable TC interrupt */
    LL_USART_DisableIT_TC(USARTx);
// }

}  //===========================================  END UART_TransmitComplete_Callback   ========================================================


//======================================================= TxRxITCaller   ==========================================================================
void TxRxITCaller(USART_TypeDef *USARTx){


	if (LL_USART_IsActiveFlag_RXNE(USARTx) && LL_USART_IsEnabledIT_RXNE(USARTx))
	  {
		USART_Receiver(USARTx);
	  }


	if (LL_USART_IsEnabledIT_TXE(USARTx) && LL_USART_IsActiveFlag_TXE(USARTx))
	  {

		TxDataTransmitter(USARTx);
	  }

	  if (LL_USART_IsEnabledIT_TC(USARTx) && LL_USART_IsActiveFlag_TC(USARTx))
	  {


	    UART_TransmitComplete_Callback(USARTx);

	  }

} //======================================================= End TxRxITCaller   =====================================================================


/* USER CODE END 1 */
