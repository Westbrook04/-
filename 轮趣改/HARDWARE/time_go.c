#include "time_go.h"
#include "timer.h"
#include "delay.h"
#include "drive_motor.h"
#include "gray.h"
#include "usartx.h"

int test_val;
extern u8 stop;
//void TIM3_IRQHandler(void)
//{
//    if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)  //�ж��ж���Դ
//		{
//		   test_val=0;
//		   TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//����жϱ�־λ
//		}
//}

   
void Time_go(void (*a)(),u16 ms)
{
      TIM7_Int_Init(65535,41999);
	  TIM_base_time=0;
	  while(TIM_base_time<2*ms)    //ms��2000Ϊ1s
		{	   
			    (*a)();	
		}
}

void Time_Set(u16 ms)//ms<30000ms��30s 2000Ϊ1s ���㹫ʽΪ:84000000/42000�̶�2oooHZƵ�� ��ʱʱ��=2*ms*0.0005
{
	u16 nms;
	nms=2*ms;
	 TIM7_Int_Init(nms-1,41999);

}

void Creazy_T(void (*a)(void),u16 ms)
{
	Time_Set(ms);
	TIM7->CNT=0;
	test_val=1;
	 	 while(1)
		{
			if(test_val==1)
			{
				(*a)();
			}
			else
			{
				break;
			}
		}
}

//void Creazy_B(void (*a)(),u16 ms)
//{

//	Time_Set(ms);
//	TIM3->CNT=0;
//	test_val=1;
//	 	 while(1)
//		{
//			if(test_val==1) 
//			{
//				(*a)();
//			}
//			else if (test_val==0&&L_Centre==1&&R_Centre==1)
//			{
//				Time_go(New_run35,210);		//150
//				break;
//			}
//		}
//}

void Time_delay_ms(u16 tim)  //tim=2000ʱΪ1s
{
//	 TIM3_Init(65535,41999);
     TIM_base_time=0;
	  while(TIM_base_time<2*tim){};
}

void Stop_Time(int time)     //��10Ϊ100
{
	int i=time;

	for(;i>0;i--)
	{
		SET_Motor(0,0,0,0);//Set_Motor(0,0);
		
		
		delay_ms(10);
	}
	
}
