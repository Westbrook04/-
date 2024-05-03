#include "encoder.h"

/**************************************************************************
Function: Initialize TIM2 as the encoder interface mode
Input   : none
Output  : none
函数功能：把TIM2初始化为编码器接口模式
入口参数：无
返 回 值：无
**************************************************************************/
void Encoder_Init_TIM1(void)
{



 GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 ,ENABLE);  		//TIM8时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE); 	//使能GPIOC
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);//GPIOC6复用为定时器8
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1);//GPIOC7复用为定时器8

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9| GPIO_Pin_11;           //GPIOE9/10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;          //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	  //速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;        //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;        //下拉
	GPIO_Init(GPIOE,&GPIO_InitStructure); 

/* 允许TIM2的时钟 */
//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

/* 将定时器2寄存器设为初始值 */
TIM_DeInit(TIM1);

/* 填入缺省值 */
TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
/* 预分频值 */
TIM_TimeBaseStructure.TIM_Prescaler = 0;
/* 自动重载值 */
TIM_TimeBaseStructure.TIM_Period = 65536 - 1;
/* 时钟分割 */
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
/* 向上计数 */
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
/* 初始化定时器2 */
TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

/* 设置编码器模式 */
TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling ,TIM_ICPolarity_Falling);

/* 填入缺省值 */
//TIM_ICStructInit(&TIM_OCInitStructure);
/* 输入比较滤波器 */

/* 初始化定时器2 */
//TIM_ICInit(TIM8, &TIM_OCInitStructure);

/* 计数器初始化 */
TIM_SetCounter(TIM1, 0);

/* 开启定时器2 */
TIM_Cmd(TIM1, ENABLE);




}

/**************************************************************************
Function: Initialize TIM3 as the encoder interface mode
Input   : none
Output  : none
函数功能：把TIM3初始化为编码器接口模式
入口参数：无
返回  值：无
**************************************************************************/
void Encoder_Init_TIM3(void)
{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
//  TIM_ICInitTypeDef TIM_ICInitStructure;  
//  GPIO_InitTypeDef GPIO_InitStructure;
//	
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   //使能定时器
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);  //使用A口

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;  //PB4 PB5
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);  
//	TIM_DeInit(TIM3);

//  GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_TIM3);   //复用为TIM2 编码器接口
//  GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_TIM3);   //复用为TIM2 编码器接口
//  
//  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);  
//  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 							// No prescaling     //不分频
//  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;  //设定计数器自动重装值
//  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //选择时钟分频：不分频
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数    
//  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  //初始化定时器
//  
//  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);//使用编码器模式3
//  TIM_ICStructInit(&TIM_ICInitStructure);
//  TIM_ICInitStructure.TIM_ICFilter = 0;
//  TIM_ICInit(TIM3, &TIM_ICInitStructure);  
//	
//  TIM_ClearFlag(TIM3, TIM_FLAG_Update);//清除TIM的更新标志位
//  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
//	TIM_SetCounter(TIM3,0);
//  TIM_Cmd(TIM3, ENABLE); 



    GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 ,ENABLE);  		//TIM8时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE); 	//使能GPIOC
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);//GPIOC6复用为定时器8
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);//GPIOC7复用为定时器8

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;           //GPIOE9/10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;          //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	  //速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;        //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;        //下拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); 

/* 允许TIM2的时钟 */
//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

/* 将定时器2寄存器设为初始值 */
TIM_DeInit(TIM3);

/* 填入缺省值 */
TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
/* 预分频值 */
TIM_TimeBaseStructure.TIM_Prescaler = 0;
/* 自动重载值 */
TIM_TimeBaseStructure.TIM_Period = 65536 - 1;
/* 时钟分割 */
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
/* 向上计数 */
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
/* 初始化定时器2 */
TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

/* 设置编码器模式 */
TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling ,TIM_ICPolarity_Falling);

/* 填入缺省值 */
//TIM_ICStructInit(&TIM_OCInitStructure);
/* 输入比较滤波器 */

/* 初始化定时器2 */
//TIM_ICInit(TIM8, &TIM_OCInitStructure);

/* 计数器初始化 */
TIM_SetCounter(TIM3, 0);

/* 开启定时器2 */
TIM_Cmd(TIM3, ENABLE);











}
/**************************************************************************
Function: Initialize TIM4 as the encoder interface mode
Input   : none
Output  : none
函数功能：把TIM4初始化为编码器接口模式
入口参数：无
返 回 值：无
**************************************************************************/
void Encoder_Init_TIM4(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能定时器4的时钟
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能PB端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;//端口配置
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);   //根据设定参数初始化GPIOB

  GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //复用为TIM4 编码器接口
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4); //复用为TIM4 编码器接口
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // No prescaling 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //TIM向上计数  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 0;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM4,0);
  TIM_Cmd(TIM4, ENABLE); 
}
/**************************************************************************
Function: Initialize TIM5 as the encoder interface mode
Input   : none
Output  : none
函数功能：把TIM5初始化为编码器接口模式
入口参数：无
返回  值：无
**************************************************************************/
void Encoder_Init_TIM8(void)
{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
//  TIM_ICInitTypeDef TIM_ICInitStructure;  
//  GPIO_InitTypeDef GPIO_InitStructure;
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//使能定时器4的时钟
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能PB端口时钟
//	
//	 GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //复用为TIM4 编码器接口
//  GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); //复用为TIM4 编码器接口
//	
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;//端口配置
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);   //根据设定参数初始化GPIOB

//  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//  
//  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // No prescaling 
//  TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; //设定计数器自动重装值
//  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //TIM向上计数  
//  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
//  
//  TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
//  TIM_ICStructInit(&TIM_ICInitStructure);
//  TIM_ICInitStructure.TIM_ICFilter = 0;
//  TIM_ICInit(TIM5, &TIM_ICInitStructure);
//  
//  TIM_ClearFlag(TIM5, TIM_FLAG_Update);
//  TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
//	TIM_SetCounter(TIM5,0);
//  TIM_Cmd(TIM5, ENABLE); 
    GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);  		//TIM8时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//使能GPIOC
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);//GPIOC6复用为定时器8
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);//GPIOC7复用为定时器8

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;           //GPIOC6/7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;          //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	  //速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;        //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;        //下拉
	GPIO_Init(GPIOC,&GPIO_InitStructure); 

/* 允许TIM2的时钟 */
//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

/* 将定时器2寄存器设为初始值 */
TIM_DeInit(TIM8);

/* 填入缺省值 */
TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
/* 预分频值 */
TIM_TimeBaseStructure.TIM_Prescaler = 0;
/* 自动重载值 */
TIM_TimeBaseStructure.TIM_Period = 65536 - 1;
/* 时钟分割 */
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
/* 向上计数 */
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
/* 初始化定时器2 */
TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

/* 设置编码器模式 */
TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling ,TIM_ICPolarity_Falling);

/* 填入缺省值 */
//TIM_ICStructInit(&TIM_OCInitStructure);
/* 输入比较滤波器 */

/* 初始化定时器2 */
//TIM_ICInit(TIM8, &TIM_OCInitStructure);

/* 计数器初始化 */
TIM_SetCounter(TIM8, 0);

/* 开启定时器2 */
TIM_Cmd(TIM8, ENABLE);

}

/**************************************************************************
Function: Read the encoder count
Input   : The timer
Output  : Encoder value (representing speed)
函数功能：读取编码器计数
入口参数：定时器
返回  值：编码器数值(代表速度)
**************************************************************************/
int Read_Encoder(u8 TIMX)
{
 int Encoder_TIM;    
 switch(TIMX)
 {
//	case 2:  Encoder_TIM= (short)TIM2 -> CNT;   TIM2 -> CNT=0;  break;
	 case 1:  Encoder_TIM= (short)TIM1 -> CNT;   TIM1 -> CNT=0;  break;
	case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;  break;
	case 4:  Encoder_TIM= (short)TIM4 -> CNT;   TIM4 -> CNT=0;  break;	
//	case 5:  Encoder_TIM= (short)TIM5 -> CNT;   TIM5 -> CNT=0;  break;
	case 8:  Encoder_TIM= (short)TIM8 -> CNT;   TIM8 -> CNT=0;  break;
	 
	default: Encoder_TIM=0;
 }
	return Encoder_TIM;
}

/**************************************************************************
Function: Tim2 interrupt service function
Input   : none
Output  : none
函数功能：TIM2中断服务函数
入口参数：无
返 回 值：无
**************************************************************************/
void TIM1_IRQHandler(void)
{ 		    		  			    
	if(TIM1->SR&0X0001) //Overflow interrupt //溢出中断
	{    				   				     	    	
	}				   
	TIM1->SR&=~(1<<0); //Clear the interrupt flag bit //清除中断标志位 	    
}
/**************************************************************************
Function: Tim3 interrupt service function
Input   : none
Output  : none
函数功能：TIM3中断服务函数
入口参数：无
返 回 值：无
**************************************************************************/
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001) //Overflow interrupt //溢出中断
	{    				   				     	    	
	}				   
	TIM3->SR&=~(1<<0); //Clear the interrupt flag bit //清除中断标志位  	    
}
/**************************************************************************
Function: Tim4 interrupt service function
Input   : none
Output  : none
函数功能：TIM4中断服务函数
入口参数：无
返 回 值：无
**************************************************************************/
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001) //Overflow interrupt //溢出中断
	{    				   				     	    	
	}				   
	TIM4->SR&=~(1<<0); //Clear the interrupt flag bit //清除中断标志位  	    
}

/**************************************************************************
Function: Tim9 interrupt service function
Input   : none
Output  : none
函数功能：TIM9中断服务函数
入口参数：无
返 回 值：无
**************************************************************************/
void TIM8_IRQHandler(void)
{ 		    		  			    
	if(TIM8->SR&0X0001) //Overflow interrupt //溢出中断
	{    				   				     	    	
	}				   
	TIM8->SR&=~(1<<0); //Clear the interrupt flag bit //清除中断标志位  	    
}

void TIM8_BRK_TIM12_IRQHandler(void)
{
	if(TIM12->SR&0X0001) //Overflow interrupt //溢出中断
	{    				   				     	    	
	}				   
	TIM12->SR&=~(1<<0); //Clear the interrupt flag bit //清除中断标志位  	 

}
