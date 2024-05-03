#include "pwm.h"
#include "math.h"
#include "sys.h"

void MOTOR_CONFIG()
{
	TIM5_PWM_Init(99,168-1);      //PWM频率为5KHZ
	Motor_Dir();
//输出0占空比
     TIM_SetCompare1(TIM5,0);
	 TIM_SetCompare2(TIM5,0); 
	 TIM_SetCompare3(TIM5,0);    
     TIM_SetCompare4(TIM5,0);    //左前轮
			
}

//初始化TIM5通道1,2 作为PWM1和PWM2输出
void TIM5_PWM_Init(u32 arr,u32 psc)
{     
	    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	    GPIO_InitTypeDef GPIO_InitStructure;
	    TIM_OCInitTypeDef TIM_OCInitStructure;
	
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);//使能定时器5
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//使能GPIOA
	
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//普通输出模式
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
      GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
      GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);//GPIOA0复用为
	    GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);
	    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);
	    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5);
	
	    TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
	    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	    TIM_TimeBaseInitStructure.TIM_Period=arr;
	    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
			
	    TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);
	    
			TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//操作CCMR寄存器,设置PWM模式1,CNT<CCR为有效
			TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
			TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//极性为高电平游有效
					
	    TIM_OC1Init(TIM5,&TIM_OCInitStructure);//初始化输出比较参数
		TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);//使能预装载寄存器
			
		TIM_OC2Init(TIM5,&TIM_OCInitStructure);//初始化输出比较参数	
		TIM_OC2PreloadConfig(TIM5,TIM_OCPreload_Enable);
			
        TIM_OC3Init(TIM5,&TIM_OCInitStructure);
	    TIM_OC3PreloadConfig(TIM5,TIM_OCPreload_Enable);
			
        TIM_OC4Init(TIM5,&TIM_OCInitStructure);			
		TIM_OC4PreloadConfig(TIM5,TIM_OCPreload_Enable);
			
		TIM_ARRPreloadConfig(TIM5,ENABLE);//ARRE使能
			
		TIM_Cmd(TIM5,ENABLE);//使能定时器
}

//初始化电机驱动
void Motor_Dir()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 	//使能PORTF时钟	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOF,&GPIO_InitStructure);              //初始化PF9
		
    M1 = 1;
	M2 = 1;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOG,&GPIO_InitStructure); 

	M3 = 1;
	M4 = 1;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//使能PORTF时钟	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //初始化PF9
		
    M5 = 1;
	M6 = 1;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOE,&GPIO_InitStructure); 

	M7 = 1;
	M8 = 1;
	
}


