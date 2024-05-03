#include "gray.h"
#include "delay.h"

#include "drive_motor.h"

void OneGray_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOEʱ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;    //ETR1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
	
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
//	
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_7;//ETR3��DIO2
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ���ģʽ
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
//  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIO
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //ʹ��GPIOEʱ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;    //ETR1 �� ETR4
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;             //��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             //����
  GPIO_Init(GPIOA, &GPIO_InitStructure);                   //��ʼ��GPIO
  
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); //ʹ��GPIOEʱ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;                 //pwm6
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;             //��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             //����
  GPIO_Init(GPIOC, &GPIO_InitStructure);                   //��ʼ��GPIO
}

void Eight_Gray_Init(void)
{
     GPIO_InitTypeDef  GPIO_InitStructure;
	
	   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	   	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;//|GPIO_Pin_2|GPIO_Pin_5|GPIO_Pin_6
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
     GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE(1,2,5,6)
	
	   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
     GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
     GPIO_Init(GPIOF, &GPIO_InitStructure);	 
}

void Gray_Init(void)
{
    Eight_Gray_Init();
	OneGray_init();
}

/*****************************************
*****����Ϊ�Ҷ��������Ѳ�ߺ���(��Ҫ����Ѳ�ߴ������������)
******************************************/

/**********������һ·***************/
void RL_Centre_Count(void (*d)(void),int ti)
{
	int a = 1,b=1,i = 0,k=0;
	while(1)
   {
		(*d)();
		if(L_Centre!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(16);
				if(L_Centre!= a)
				{
					i++;
					a = L_Centre;
				}
			}
			
				if(R_Centre!= b)                     //��¼���������ɿ�λ
			{
				delay_ms(16);
				if(R_Centre != b)
				{
					k++;
					b = R_Centre;
				}
			}
		if(i>=ti&&k>=ti)
		{
//			Set_Motor(0,0);
			break;
		}
	}
}
/************���Һ�һ·�Ҷ�****************/
void RL_Back_Count(void (*d)(void),int ti)
{
	int a = 1,b=1,i = 0,k=0;
	while(1)
   {
		(*d)();
		if(L_back!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(20);
				if(L_back!= a)
				{
					i++;
					a = L_back;
				}
			}
			
				if(R_back!= b)                     //��¼���������ɿ�λ
			{
				delay_ms(20);
				if(R_back != b)
				{
					k++;
					b = R_back;
				}
			}
		if(i>=ti&&k>=ti)
		{
			Set_Motor(0,0);
			break;
		}
	}
}
///****************����ǰ��·�Ҷ����************/
void RL_Front_Count(void (*d)(void),int ti)
{
	int a = 1,b=1,i = 0,k=0;
	while(1)
   {
		(*d)();
		if(L_front!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(15);//20
				if(L_front!= a)
				{
					i++;
					a = L_front;
				}
			}
			
				if(R_front!= b)                     //��¼���������ɿ�λ
			{
				delay_ms(15);//20
				if(R_front != b)
				{
					k++;
					b = R_front;
				}
			}
		if(i>=ti&&k>=ti)
		{
//			Set_Motor(0,0);
			break;
		}
	}
}

///**************����Ϊ����Ҷȼ���*********/

/*****************��ǰ�Ҷ����***************/
void R_Front_Count(void (*d)(void),int ti)
{
	int a = 1,i = 0;
	while(1)
   {
		(*d)();
		if(R_front!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(16);
				if(R_front!= a)
				{
					i++;
					a = R_front;
				}
			}
			
		if(i>=ti)
		{
//			SET_Motor(0,0,0,0);//Set_Motor(0,0);
			break;
		}
	}
}

//��ǰ�Ҷ�
void L_Front_Count(void (*d)(void),int ti)
{
	int a = 1,i = 0;
	while(1)
   {
		(*d)();
		if(L_front!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(20);
				if(L_front!= a)
				{
					i++;
					a = L_front;
				}
			}
			
		if(i>=ti)
		{
			SET_Motor(0,0,0,0);//Set_Motor(0,0);
			break;
		}
	}
}
/*****************����һ·�Ҷ�**************/
void R_Centre_Count(void (*d)(void),int ti)
{
	int a = 1,i = 0;
	while(1)
   {
		(*d)();
		if(R_Centre!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(20);
				if(R_Centre!= a)
				{
					i++;
					a = R_Centre;
				}
			}
			
		if(i>=ti)
		{
			SET_Motor(0,0,0,0);//Set_Motor(0,0);
			break;
		}
	}
}
///*****************����һ·�Ҷ�**************/
void L_Centre_Count(void (*d)(void),int ti)
{
	int a = 1,i = 0;
	while(1)
   {
		(*d)();
		if(L_Centre!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(20);
				if(L_Centre!= a)
				{
					i++;
					a = L_Centre;
				}
			}
			
		if(i>=ti)
		{
			SET_Motor(0,0,0,0);//Set_Motor(0,0);
			break;
		}
	}
}
///****************�Һ�һ·�Ҷ�******************/
void R_Back_Count(void (*d)(void),int ti)
{
	int a = 1,i = 0;
	while(1)
   {
		(*d)();
		if(R_back!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(20);
				if(R_back!= a)
				{
					i++;
					a = R_back;
				}
			}
			
		if(i>=ti)
		{
			SET_Motor(0,0,0,0);//Set_Motor(0,0);
			break;
		}
	}
}
///****************���һ·�Ҷ�******************/
void L_Back_Count(void (*d)(void),int ti)
{
	int a = 1,i = 0;
	while(1)
   {
		(*d)();
		if(L_back!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(20);
				if(L_back!= a)
				{
					i++;
					a = L_back;
				}
			}
			
		if(i>=ti)
		{
			SET_Motor(0,0,0,0);//Set_Motor(0,0);
			break;
		}
	}
}
