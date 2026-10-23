/*
 * robot_control.h
 *
 *  Created on: Jan 22, 2025
 *      Author: Carlos
 */

#ifndef INC_ROBOT_CONTROL_H_
#define INC_ROBOT_CONTROL_H_

#include "main.h"
#include "usart.h"
#define TEST_TICK_VAL 150

/*  @brief: Funcao para seter
 *
 * */

__STATIC_INLINE void SET_JOINT(robotJoint_t *robotJoint)
{

 if(robotJoint->newX1 < robotJoint->actX1)
 {
	 if(robotJoint->newX1 == robotJoint->actX1)
	 {
		 robotJoint->actX1 = robotJoint->newX1;
		 TIM1 ->CCR1 = robotJoint->actX1;

	 }else
	 {
		 TIM1 ->CCR1 = robotJoint->actX1--;
	 }

 }

 else if(robotJoint->newX1 > robotJoint->actX1)
 {
	 if(robotJoint->newX1 == robotJoint->actX1)
	 {
		 robotJoint->actX1 = robotJoint->newX1;
		 TIM1 ->CCR1 = robotJoint->actX1;

	 }else
	 {
		 TIM1 ->CCR1 = robotJoint->actX1++;
	 }

 }



 if(robotJoint->newX2 < robotJoint->actX2)
  {
 	 if(robotJoint->newX2 == robotJoint->actX2)
 	 {
 		 robotJoint->actX2 = robotJoint->newX2;
 		TIM1 ->CCR2 = robotJoint->actX2;
 	 }else
 	 {
 		TIM1 ->CCR2 = robotJoint->actX2--;
 	 }
 	// HAL_Delay(50);
  }

  else if(robotJoint->newX2 > robotJoint->actX2)
  {
 	 if(robotJoint->newX2 == robotJoint->actX2)
 	 {
 		 robotJoint->actX2 = robotJoint->newX2;

 		TIM1 ->CCR2 = robotJoint->actX2;
 	 }else
 	 {
 		TIM1 ->CCR2 = robotJoint->actX2++;
 	 }

  }


 if(robotJoint->newX3 < robotJoint->actX3)
  {
 	 if(robotJoint->newX3 == robotJoint->actX3)
 	 {
 		 robotJoint->actX3 = robotJoint->newX3;
 		 TIM15->CCR1 = robotJoint->actX3;
 	 }else
 	 {
 		TIM15->CCR1 = robotJoint->actX3--;
 	 }
 	// HAL_Delay(50);
  }

  else if(robotJoint->newX3 > robotJoint->actX3)
  {
 	 if(robotJoint->newX3 == robotJoint->actX3)
 	 {
 		 robotJoint->actX3 = robotJoint->newX3;
 		TIM15->CCR1 = robotJoint->actX3;
 		 //robotData.angleChange = 0;
 	 }else
 	 {
 		TIM15->CCR1 =robotJoint->actX3++;
 	 }

  }

 if(robotJoint->newX4 < robotJoint->actX4)
   {
  	 if(robotJoint->newX4 == robotJoint->actX4)
  	 {
  		 robotJoint->actX4 = robotJoint->newX4;
  		 TIM15 ->CCR2 = robotJoint->actX4;
  	 }else
  	 {
  		TIM15 ->CCR2 = robotJoint->actX4--;
  	 }
  	// HAL_Delay(50);
   }

   else if(robotJoint->newX4 > robotJoint->actX4)
   {
  	 if(robotJoint->newX4 == robotJoint->actX4)
  	 {
  		 robotJoint->actX4 = robotJoint->newX4;
  		TIM15 ->CCR2 = robotJoint->actX4;
  		 //robotData.angleChange = 0;
  	 }else
  	 {
  		TIM15 ->CCR2 = robotJoint->actX4++;
  	 }

   }




 if((robotJoint->newX1 == robotJoint->actX1) &&
    (robotJoint->newX2 == robotJoint->actX2) &&
	(robotJoint->newX3 == robotJoint->actX3) &&
	(robotJoint->newX4 == robotJoint->actX4))
 {
	 robotData.angleChange = 0;
 }
 HAL_Delay(50);
}

__STATIC_INLINE void SELF_TEST(void)
{

	robotData.selfTestPWM = START_ANGLE;

   while(robotData.selfTestPWM < END_ANGLE)
   {
	    TIM1->CCR1  = robotData.selfTestPWM;
	   	TIM1->CCR2  = robotData.selfTestPWM;
	    TIM15->CCR1 = robotData.selfTestPWM;
	    TIM15->CCR2 = robotData.selfTestPWM;
	    robotData.selfTestPWM ++;
	       HAL_Delay(30);
   }
	       if(robotData.selfTestPWM >= END_ANGLE){

	    	   while(robotData.selfTestPWM-- > CENTER_ANGLE)
	    	   {

	    		   robotData.robotJoint.actX1 = robotData.selfTestPWM;
	    		   robotData.robotJoint.actX2 = robotData.selfTestPWM;
	    		   robotData.robotJoint.actX3 = robotData.selfTestPWM;
	    		   robotData.robotJoint.actX4 = robotData.selfTestPWM;

	    		   robotData.robotJoint.newX1 = robotData.selfTestPWM;
	    		   robotData.robotJoint.newX2 = robotData.selfTestPWM;
	    		   robotData.robotJoint.newX3 = robotData.selfTestPWM;
	    		   robotData.robotJoint.newX4 = robotData.selfTestPWM;

	    		   TIM1 ->CCR1 = robotData.robotJoint.actX1;
	    		   TIM1 ->CCR2 = robotData.robotJoint.actX2;
	    		   TIM15->CCR1 = robotData.robotJoint.actX3;
	    		   TIM15->CCR2 = robotData.robotJoint.actX4;


	    		   HAL_Delay(45);

	    	   }

	       }



}


__STATIC_INLINE void SELF_TEST2(void)
{

		 /*****************  AUTO TESTE EIXO 3 ****************/

	robotData.selfTestPWM = MIN_PWM_AXIS_3;

		   	   while(robotData.selfTestPWM < MAX_PWM_AXIS_3)
		   	   {
		   		    TIM15->CCR1  = robotData.selfTestPWM;

		   		    robotData.selfTestPWM ++;
		   		       HAL_Delay(30);
		   	   }
		   	   if(robotData.selfTestPWM >= MAX_PWM_AXIS_3){

		   	  	    	   while(robotData.selfTestPWM-- > MIN_PWM_AXIS_3)
		   	  	    	   {

		   	  	    		   robotData.robotJoint.actX3 = robotData.selfTestPWM;


		   	  	    		   robotData.robotJoint.newX3 = robotData.selfTestPWM;


		   	  	    		   TIM15 ->CCR1 = robotData.robotJoint.actX3;



		   	  	    		   HAL_Delay(45);

		   	  	    	   }
		   	   }

     /*****************  AUTO TESTE EIXO 2 ****************/
	robotData.selfTestPWM = MIN_PWM_AXIS_2;

	   	while(robotData.selfTestPWM < MAX_PWM_AXIS_2)
	   	   {
	   		    TIM1->CCR2  = robotData.selfTestPWM;

	   		    robotData.selfTestPWM ++;
	   		       HAL_Delay(30);
	   	   }
	   	   if(robotData.selfTestPWM >= (MAX_PWM_AXIS_2+MAX_PWM_AXIS_2)/2){

	   	  	    	   while(robotData.selfTestPWM-- > MIN_PWM_AXIS_2)
	   	  	    	   {

	   	  	    		   robotData.robotJoint.actX2 = robotData.selfTestPWM;


	   	  	    		   robotData.robotJoint.newX2 = robotData.selfTestPWM;


	   	  	    		   TIM1 ->CCR2 = robotData.robotJoint.actX2;



	   	  	    		   HAL_Delay(45);

	   	  	    	   }
	   	   }
	   	 /*****************  AUTO TESTE EIXO 1 ****************/
	   	robotData.selfTestPWM = START_ANGLE;

	   		   while(robotData.selfTestPWM < END_ANGLE)
	   		   {
	   			    TIM1->CCR1  = robotData.selfTestPWM;
	   	            robotData.selfTestPWM ++;
	   			    HAL_Delay(30);
	   		   }
	   		   if(robotData.selfTestPWM >= END_ANGLE)
	   		   {
	   	             while(robotData.selfTestPWM-- > CENTER_AXIS_1)
	   		  	    	   {

	   	            	      robotData.robotJoint.actX1 = robotData.selfTestPWM;
	   	                      robotData.robotJoint.newX1 = robotData.selfTestPWM;
	   	                      TIM1 ->CCR1 = robotData.robotJoint.actX1;

	   	                      HAL_Delay(45);
	   	                    }
	   		   }


	   		/*****************  AUTO TESTE EIXO 4   GARRA  ****************/
	   		   	robotData.selfTestPWM = MIN_PWM_GAR;

	   		   		   	   while(robotData.selfTestPWM < END_ANGLE)
	   		   		   	   {
	   		   		   		    TIM15->CCR2  = robotData.selfTestPWM;

	   		   		   		    robotData.selfTestPWM ++;
	   		   		   		       HAL_Delay(30);
	   		   		   	   }
	   		   		   	   if(robotData.selfTestPWM >= END_ANGLE){

	   		   		   	  	    	   while(robotData.selfTestPWM-- > MIN_PWM_GAR)
	   		   		   	  	    	   {

	   		   		   	  	    		   robotData.robotJoint.actX4 = robotData.selfTestPWM;


	   		   		   	  	    		   robotData.robotJoint.newX4 = robotData.selfTestPWM;


	   		   		   	  	    		   TIM15 ->CCR2 = robotData.robotJoint.actX2;



	   		   		   	  	    		   HAL_Delay(45);

	   		   		   	  	    	   }
	   		   		   	   }

}// End SELF_TEST2


__STATIC_INLINE void endOperation(robotJoint_t *robotJoint)
{

	 if(START_ANGLE < robotJoint->actX1)
	 {
		 if(robotJoint->actX1 == START_ANGLE)
		 {
			 robotJoint->actX1 = START_ANGLE;
			 TIM1 ->CCR1 = START_ANGLE;

		 }else
		 {
			 TIM1 ->CCR1 = robotJoint->actX1--;
		 }

	 }

	 // PARA O EIXO 2

	  if(MIN_PWM_AXIS_2 < robotJoint->actX2)
		 {
			 if(robotJoint->actX2 == MIN_PWM_AXIS_2)
			 {
				 robotJoint->actX2 = MIN_PWM_AXIS_2;
				 TIM1 ->CCR2 = MIN_PWM_AXIS_2;

			 }else
			 {
				 TIM1 ->CCR2 = robotJoint->actX2--;
			 }

		 }
	  if(MIN_PWM_AXIS_3 < robotJoint->actX3)
	 		 {
	 			 if(robotJoint->actX3 == MIN_PWM_AXIS_3)
	 			 {
	 				robotJoint->actX3 = MIN_PWM_AXIS_3;
	 				 TIM15 ->CCR1 = MIN_PWM_AXIS_3;

	 			 }else
	 			 {
	 				 TIM15 ->CCR1 = robotJoint->actX3--;
	 			 }

	 		 }


	  if(START_ANGLE < robotJoint->actX4)
	 		 {
	 			 if(robotJoint->actX4 == MIN_PWM_GAR)
	 			 {
	 				robotJoint->actX4 = MIN_PWM_GAR;
	 				 TIM15 ->CCR2 = MIN_PWM_GAR;

	 			 }else
	 			 {
	 				 TIM15 ->CCR2 = robotJoint->actX4--;
	 			 }

	 		 }



	 if((robotJoint->actX1 == START_ANGLE) &&
	    (robotJoint->actX2 == MIN_PWM_AXIS_2) &&
		(robotJoint->actX3 == MIN_PWM_AXIS_3) &&
		(robotJoint->actX4 == MIN_PWM_GAR) )
	 {
		 robotData.angleChange = 0;
	 }



}
#endif /* INC_ROBOT_CONTROL_H_ */
