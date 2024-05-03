#include "drive_motor.h"
#include "pwm.h"
#include "sys.h"

/************PWM1��Ӧ��ǰ�� PWM2��Ӧ�����***************/
/************PWM3��Ӧ��ǰ�� PWM4��Ӧ�Һ���***************/
//�����������ٶȺ���  ����22(����)


//extern int rpm;
//extern  int rpm1;


//void PID_Init(float A,float Kp,float Ki,float Kd,float target)
//{	
//error=target-A;   //Ŀ���ٶ�С�ڵ���ٶȣ���ֵ
//integral+=error;    //����ۻ�
//if(integral>2750)  {integral=2750;}   //�����޷�
//if(integral<-2750) {integral=-2750;}	
//p_out=Kp*error;
//i_out=Ki*integral;
//d_out=Kd*(error-error_last);
//if(error>2000) {i_out=0;}      //���ַ���
//pwmout=p_out+i_out+d_out;
//error_last =error;
//if(pwmout>2750) {pwmout=2750;}
//if(pwmout<-2750) {pwmout=-2750;}
//change(pwmout);
//return pwmout;
//} 
// 
 
 
 
// 
//void change(float a)
//{
// if(a<0)
// {
//	a=-a;
//	TIM_SetCompare1(TIM4,a); 
//	D0=0;
//	D1=1;
// }
// else if(a>0)
// {
//  TIM_SetCompare1(TIM4,a);
//	D0=1;
//	D1=0;	 
// }
// else
//{
//  TIM_SetCompare1(TIM4,0);
//	D0=0;
//	D1=0;
//}
//}


void Set_Motor_rpm(s32 leftspeed,s32 rightseepd)
{
//	rpm=leftspeed;
//	rpm1=rightseepd;
}

void Set_Motor(s32 leftspeed,s32 rightseepd)
{
	   if(leftspeed>=0)
		 {
			 M1=1;   
			 M2=0;	 
             TIM_SetCompare1(TIM5,leftspeed);    //��ǰ��
			 TIM_SetCompare2(TIM5,leftspeed);    //�����
		 }
		 if(rightseepd>=0)
		 { 
		     M3=1;
			 M4=0;
             TIM_SetCompare3(TIM5,rightseepd);   //��ǰ��
			 TIM_SetCompare4(TIM5,rightseepd);   //�Һ���
		 }
		  if(leftspeed<0)
		 {
		    M1=0;
		    M2=1;	
            leftspeed=-leftspeed;
             TIM_SetCompare1(TIM5,leftspeed);
			 TIM_SetCompare2(TIM5,leftspeed);
		 }
		  if(rightseepd<0)
		 {
		     M3=0;
			 M4=1;
             rightseepd=-rightseepd;			 
             TIM_SetCompare3(TIM5,rightseepd);
			 TIM_SetCompare4(TIM5,rightseepd);
		 }
}


void SET_Motor(s32 leftspeed_b,s32 leftspeed_f,s32 rightseepd_f,s32 rightseepd_b)
{
	   if(leftspeed_f>=0)//2
		 {
			 M1=0;   
			 M2=1;	 

			 TIM_SetCompare2(TIM5,leftspeed_f);    //�����
		 }
		 if(rightseepd_f>=0)//3
		 { 
		     M3=0;
			 M4=1;
             TIM_SetCompare3(TIM5,rightseepd_f);   //��ǰ��

		 }
		  if(leftspeed_f<0)//2
		 {
		    M1=1;
		    M2=0;	
            leftspeed_f=-leftspeed_f;

			 TIM_SetCompare2(TIM5,leftspeed_f);
		 }
		  if(rightseepd_f<0)//3
		 {
		     M3=1;
			 M4=0;
             rightseepd_f=-rightseepd_f;			 
             TIM_SetCompare3(TIM5,rightseepd_f);

		 }

/////////////////����
		 	   if(leftspeed_b>=0)//1
		 {
			 M5=1;   
			 M6=0;	 
             TIM_SetCompare1(TIM5,leftspeed_b);    //��ǰ��

		 }
		 if(rightseepd_b>=0)//4
		 { 
		     M7=1;
			 M8=0;

			 TIM_SetCompare4(TIM5,rightseepd_b);   //�Һ���
		 }
		  if(leftspeed_b<0)//1
		 {
		    M5=0;
		    M6=1;	
            leftspeed_b=-leftspeed_b;
             TIM_SetCompare1(TIM5,leftspeed_b);

		 }
		  if(rightseepd_b<0)//4
		 {
		     M7=0;
			 M8=1;
             rightseepd_b=-rightseepd_b;			 

			 TIM_SetCompare4(TIM5,rightseepd_b);
		 }

}
//С��ǰ������
void CarAdvance(u8 speed)
{
     M1=1;
	 M3=0;
	 M2=1;
	 M4=0;
	 TIM_SetCompare1(TIM5,speed);
	 TIM_SetCompare2(TIM5,speed);
	 TIM_SetCompare3(TIM5,speed);
	 TIM_SetCompare4(TIM5,speed);
}	 
 //С�����˺���
void CarRetreat(u8 speed)
{
     M1=0;
	 M3=1;
	 M2=0;
	 M4=1;
	 TIM_SetCompare1(TIM5,speed);
	 TIM_SetCompare2(TIM5,speed);
	 TIM_SetCompare3(TIM5,speed);
	 TIM_SetCompare4(TIM5,speed);
}
//����С������ left_direction��д1��0��0��ת1��ת��
void DriveLeftWhell(u8 left_direction,u8 speed)
{
     M1=0;
     M2=left_direction;
	 TIM_SetCompare1(TIM5,speed);
	 TIM_SetCompare2(TIM5,speed);
}
//����С������ right_direction��д1��0��1��ת0��ת��
void DriveRightWhell(u8 right_direction,u8 speed)
{
     M3=0;
     M4=right_direction;
	 TIM_SetCompare3(TIM5,speed);
	 TIM_SetCompare4(TIM5,speed);
}
void Car_Advance35(void)
{
    // Set_Motor(35,35);
	SET_Motor(35,35,35,35);
}
void Car_Advance30(void)
{
//     Set_Motor(30,30);
	 SET_Motor(30,30,30,30);
	
}

void Car_Advance35pian(void)
{
     SET_Motor(30,30,31,31);//Set_Motor(30,31);
}
void Car_Advance27pian(void)
{
     Set_Motor(26,25);
}
void Car_Advance28(void)
{
//     Set_Motor(27,27);

	SET_Motor(27,27,27,27);
}

void Car_Advance22(void)
{
//     Set_Motor(23,23);
	SET_Motor(23,23,23,23);
}
void Car_Advance20(void)
{
//     Set_Motor(20,20);
	SET_Motor(20,20,20,20);
	
}
void Car_Retreat35(void)
{
//     Set_Motor(-35,-35);
	SET_Motor(-35,-35,-35,-35);
}
void Car_Retreat28(void)
{
//     Set_Motor(-28,-28);
	SET_Motor(-28,-28,-28,-28);
}
void Car_Retreat20(void)
{
//     Set_Motor(-20,-20);
	SET_Motor(-20,-20,-20,-20);

}
