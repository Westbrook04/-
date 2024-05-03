
#ifndef __MOTOR_H
#define __MOTOR_H

#include "system.h"

/*--------Motor_A control pins--------*/
#define PWM_PORTA1 GPIOB			 //PWMA
#define PWM_PIN_A1 GPIO_Pin_8 //PWMA
#define PWMA1 	  TIM10->CCR1	 //PWMA

#define PWM_PORTA2 GPIOB			 //PWMA
#define PWM_PIN_A2 GPIO_Pin_9 //PWMA
#define PWMA2 	  TIM11->CCR1	 //PWMA
/*------------------------------------*/

/*--------Motor_B control pins--------*/
#define PWM_PORTB1 GPIOE			 //PWMB
#define PWM_PIN_B1 GPIO_Pin_5 //PWMB
#define PWMB1 	  TIM9->CCR1	 //PWMB

#define PWM_PORTB2 GPIOE			 //PWMB
#define PWM_PIN_B2 GPIO_Pin_6 //PWMB
#define PWMB2 	  TIM9->CCR2	 //PWMB

/*------------------------------------*/

/*--------Motor_C control pins--------*/
#define PWM_PORTC1 GPIOE			 //PWMC
#define PWM_PIN_C1 GPIO_Pin_11 //PWMC
#define PWMC1 	  TIM1->CCR2	 //PWMC

#define PWM_PORTC2 GPIOE			 //PWMC
#define PWM_PIN_C2 GPIO_Pin_9 //PWMC
#define PWMC2 	  TIM1->CCR1	 //PWMC

/*------------------------------------*/

/*--------Motor_D control pins--------*/
#define PWM_PORTD1 GPIOE			 //PWMD
#define PWM_PIN_D1 GPIO_Pin_14 //PWMD
#define PWMD1 	  TIM1->CCR4	 //PWMD

#define PWM_PORTD2 GPIOE			 //PWMD
#define PWM_PIN_D2 GPIO_Pin_13 //PWMD
#define PWMD2 	  TIM1->CCR3	 //PWMD

/*------------------------------------*/
#define EN     PDin(3)  

#define Servo_PWM6  TIM12->CCR2
#define Servo_PWM5  TIM12->CCR1
#define Servo_PWM4  TIM8->CCR4
#define Servo_PWM3  TIM8->CCR3
#define Servo_PWM2  TIM8->CCR2
#define Servo_PWM1  TIM8->CCR1

#define SERVO_INIT 1500  //Servo zero point //������



#define M1 PFout(14)
#define M2 PFout(15)
#define M3 PGout(0)
#define M4 PGout(1)


#define M5 PCout(4)
#define M6 PCout(5)
#define M7 PEout(7)
#define M8 PEout(8)







void Enable_Pin(void);
void Servo_PWM_Init(u16 arr,u16 psc);
void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM9_PWM_Init(u16 arr,u16 psc);
void TIM10_PWM_Init(u16 arr,u16 psc);
void TIM11_PWM_Init(u16 arr,u16 psc);			
	
void MOTOR_CONFIG(void);
void TIM5_PWM_Init(u32 arr,u32 psc);
void Motor_Dir(void);

#endif
