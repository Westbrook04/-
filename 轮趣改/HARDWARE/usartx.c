#include "usartx.h"




#define TRANSFER_IT_ENABLE_MASK (uint32_t)(DMA_SxCR_TCIE | DMA_SxCR_HTIE | \
                                           DMA_SxCR_TEIE | DMA_SxCR_DMEIE)
										   
										   
										   
//#define Infrared1 PAin(2)  //
//#define Infrared2 PAin(3)  //
//#define Infrared3 PAin(6)  //
//#define Infrared4 PAin(7)  //
#define LED0 PEout(3)
#define LED1 PEout(4)
#define 	ANGLE_Z 	getAngle(3)
#define  GY53_Receive    PAin(2)
#define  GY53_Receive1    PAin(3)
#define  GY53_Receive2    PAin(6)
#define  GY53_Receive3    PAin(7)
SEND_DATA Send_Data;
RECEIVE_DATA Receive_Data;
extern int Time_count;
static unsigned char RxBuffer_UARST4[100];

static unsigned char RxBuffer_UARST1[100];
u8 colour_data_Max_len = 6;

static unsigned char RxCnt = 0;
int openmv_date[6];
int left_flag;
int right_flag;
int rho_err,theta_err,cx,cy;//
static unsigned char RxCnt4 = 0;
int a=0;
u8 RES=0;
short int m=0;
u8 b[8];
u8 cc[11];
u8 bufferAngle[33];
u16 Angle_X ;
u16 Angle_Y ;
u16 Angle_Z ;
u16 aacx ;
u16 aacy ;
u16 aacz ;
u16 gyrox ;
u16 gyroy ;
u16 gyroz ;

u8 code_data_Max_len = 8;
static unsigned char Code_UARST1[100];
static unsigned char CoCnt = 0;
extern u16 i,p;


int tin=0;
int ii=0;

int code_number1;
int code_number2;
int code_number3;
int code_number4;
int code_number5;
int code_number6;


volatile uint8_t dataToSend;
volatile uint8_t dataSent = 0;

uint16_t time=0 ;
uint16_t time1=0 ;


u8 colour_type;//1��2��3��4��5��
u8 colour_cx;
u8 colour_cy;
u8 colour_distance;

//void crazyMe(int i,u16 a,u16 b,u16 tim,u8 xf)//i������λ a��Ŀǰ�Ƕ�  b��Ŀ��Ƕ�	tim��ÿһ����ʱ��		xf�������ָ�����
//{
//	u16 k,m;
//	u8 s;
//	for(s=0;s<=xf;s++)
//	{
//		if(a>b)
//		{
//			k=calculate_PWM(a)-calculate_PWM(b);
//		}
//		else
//			k=calculate_PWM(b)-calculate_PWM(a);;
//		if(a>b)
//		{
//			m=calculate_PWM(a)-k*s/xf;
//		}
//		else
//			m=calculate_PWM(a)+k*s/xf;
//		setPWM(i,0,m);
//		delay_ms(tim);
//	}
//}

void chu()
{
			Servo_PWM1=1600;
			Servo_PWM2=1200;
			Servo_PWM3=1800;
			Servo_PWM4=2100;
			Servo_PWM5=300;
			Servo_PWM6=1000;
				vTaskDelay(1800);
}

void lay()
{
	vTaskDelay(480);
	Servo_PWM4=1650;
	vTaskDelay(480);
	Servo_PWM2=1400;
	vTaskDelay(580);
	Servo_PWM1=430;
	vTaskDelay(480);
	Servo_PWM2=1330;
	vTaskDelay(480);
	Servo_PWM5=1900;
	vTaskDelay(480);
	Servo_PWM6=1000;
//	Servo_PWM1=1600;
//	vTaskDelay(480);
//			  Servo_PWM2=1300;
//	vTaskDelay(480);
//			Servo_PWM4=2100;
//	vTaskDelay(480);
//			Servo_PWM5=1400;
//	vTaskDelay(480);
//			Servo_PWM6=600;
//	vTaskDelay(480);
				
}
void dinwei()
{
	Servo_PWM1=1600;
			  Servo_PWM2=1600;
			Servo_PWM4=1500;
			Servo_PWM5=300;
			Servo_PWM6=1000;
				
}
void saoma()
{
	Drive_Motor(0.05,0.05,0.05,0.05);
	vTaskDelay(1500);
//	Drive_Motor(0.3,0.3,0.3,0.3);
//	vTaskDelay(80);
	Drive_Motor(0.05,0.05,0.05,0.05);
	vTaskDelay(1800);
	Drive_Motor(0,0,0,0);
	vTaskDelay(1800);
}
void dinweiyuan()
{
	while(1){
			 vTaskDelay(50);
			if(cx<=75){
				
        Drive_Motor(0.03,0.03,0.03,0.03);
				vTaskDelay(10);
			}
			else if(cx>85)
			{
				
				 Drive_Motor(-0.03,-0.03,-0.03,-0.03);
			vTaskDelay(10);
			}
			else{
				 Drive_Motor(0,0,0,0);
				vTaskDelay(10);
//				i++;
//				if(i==100)
				
					break;
			}
		}
			while(1){
				vTaskDelay(50);
			 if(cy<55){
					Drive_Motor(-0.05,0.03,-0.05,0.03);
			vTaskDelay(10);
			}
			else if(cy>65){
				
			
				Drive_Motor(0.03,-0.05,0.03,-0.05);
	vTaskDelay(10);
			}
			else
			{
				Drive_Motor(0,0,0,0);
				vTaskDelay(20);
			  break;
			}
		}
}



void zhuan_pang()
{

//int i=0;
//	while(1){
//		vTaskDelay(50);
////			 if(cy<55){
////					Drive_Motor(-0.05,0.03,-0.05,0.03);
////			vTaskDelay(10);
////			}
//		
//	}
	
	
	
	
while(1){
			 vTaskDelay(50);
//			if(Hcsr04GetLength3()>=310&&Hcsr04GetLength2()>=317)
//			{
//				 Drive_Motor(0.03,0.03,0.03,0.03);

//			vTaskDelay(10);
//				while(1)
//				{
//				if(Hcsr04GetLength3()<=306&&Hcsr04GetLength2()<=309)
//				{
//					Drive_Motor(0,0,0,0);
//				break;
//				}
//				}
//				
//				
//			}
	
//			else if(Hcsr04GetLength3()<=303&&Hcsr04GetLength2()>=317){
//				
//        Drive_Motor(-0.03,-0.03,0.03,0.03);
//				vTaskDelay(10);
////					while(1)
////				{
////				if(Hcsr04GetLength3()>=302&&Hcsr04GetLength2()<=307)
////				{
////					Drive_Motor(0,0,0,0);
////				break;
////				}
////				}
//			}
//			else if(Hcsr04GetLength3()>=310&&Hcsr04GetLength2()<=310){
//				
//        Drive_Motor(0.03,0.03,-0.03,-0.03);
//				vTaskDelay(10);
////						while(1)
////				{
////				if(Hcsr04GetLength3()<=305&&Hcsr04GetLength2()>=307)
////				{
////					Drive_Motor(0,0,0,0);
////				break;
////				}
////				}
//				
//			}
//			else if(Hcsr04GetLength3()<=303&&Hcsr04GetLength2()<=307){
//				
//       
//				Drive_Motor(-0.03,-0.03,-0.03,-0.03);
//				vTaskDelay(10);
//								while(1)
//				{
//				if(Hcsr04GetLength3()>=305&&Hcsr04GetLength2()>=310)
//				{
//					Drive_Motor(0,0,0,0);
//				break;
//				}
//			}
//			}
//			else{
//				 Drive_Motor(0,0,0,0);
//				vTaskDelay(10);
////				i++;
////				if(i==100)
//				
//					break;
//			}
//		}

		
			while(1){
				vTaskDelay(50);
			 if(Hcsr04GetLength()>=88&&Hcsr04GetLength1()>=78){
					Drive_Motor(-0.05,0.03,-0.05,0.03);//����
			vTaskDelay(10);
				 	
			while(1){
				if(Hcsr04GetLength()<=82&&Hcsr04GetLength1()<=74)
				{
					Drive_Motor(0,0,0,0);
					break;
				}
						}
			}
			 
//			else if(Hcsr04GetLength()>=67&&Hcsr04GetLength1()<=59){

//				Drive_Motor(-0.03,-0.03,0.03,0.03);//Զ��
//	vTaskDelay(10);
////				while(1)
////				{
////				
////				if(Hcsr04GetLength()<=67&&Hcsr04GetLength1()>=59)
////				{Drive_Motor(0,0,0,0);
////					break;
////				}
////				
////				}
//			}
//			
//			else if(Hcsr04GetLength()<=67&&Hcsr04GetLength1()>=59){
//		
//				Drive_Motor(0.03,0.03,-0.03,-0.03);//Զ��
//	vTaskDelay(10);
//								while(1)
//				{
//				
//				if(Hcsr04GetLength()>=67&&Hcsr04GetLength1()<=59)
//				{
//					Drive_Motor(0,0,0,0);
//					break;
//				
//				}
//				}
//				
//			}
			
	
//			else if(Hcsr04GetLength()<=78&&Hcsr04GetLength1()<=70){
//				
//			
//				Drive_Motor(0.03,-0.05,0.03,-0.05);//Զ��
//	vTaskDelay(10);
//											while(1)
//				{
//				
//				if(Hcsr04GetLength()>=80&&Hcsr04GetLength1()>=71)
//				{Drive_Motor(0,0,0,0);
					break;
//				}
//				
//				}
//				
//				
			}
//			else
//			{
//				Drive_Motor(0,0,0,0);
//				vTaskDelay(20);
			  break;
//			}
		}
//	

	
	
	
	
	
	

}
/**************************************************************************
Function: Usartx3, Usartx1,Usartx5 and CAN send data task 
Input   : none
Output  : none
�������ܣ�����3������1������5��CAN������������
��ڲ�������
����  ֵ����
**************************************************************************/
void data_task(void *pvParameters)
{
	


	 u32 lastWakeTime = getSysTickCnt();
//	chu();

//		vTaskDelay(800);
//Car_TurnAngle(60);
//		int i;

   while(1)
    {	
		int i;
			//The task is run at 20hz
			//��������20Hz��Ƶ������
			vTaskDelayUntil(&lastWakeTime, F2T(RATE_20_HZ));

		while(1)
		{	
			
			g_run28();
			
//			
//		Drive_Motor(-0.1,0.1,0.5,-0.1);
			
		
//						_6zhou_calibration();
//		printf("AngleX=%d\r\n",Angle_X);
//		printf("AngleY=%d\r\n",Angle_Y);
//		printf("AngleZ=%d\r\n",Angle_Z);
//		
//		printf("aacx=%d\r\n",aacx);
//		printf("aacy=%d\r\n",aacy);
//		printf("aacz=%d\r\n",aacz);
//			
//		printf("gyrox=%d\r\n",gyrox);
//		printf("gyroy=%d\r\n",gyroy);
//		printf("gyroz=%d\r\n",gyroz);
					
			
			
			
			if(i>1000)
//		if(Hcsr04GetLength()>22&&Hcsr04GetLength1()>16)	
		{
			
	Drive_Motor(0,0,0,0);
		vTaskDelay(200);
			break;
		}	
		
		
		}
		
		
		
		

		
	}
		
}



//void Infrared_sensor_Init(void)
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//ʹ��GPIODʱ��
//	
//    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;  //����
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; 
//	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;  //�������
//	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;  //����
//	
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7; //PA13
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
// 
//}






void BEEP_Init(void)
{   
   	 GPIO_InitTypeDef GPIO_InitStructure;

	   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);//ʹ��ʱ��
/*****************GPIO��ʼ��************/
	   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	   GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	   GPIO_Init(GPIOG,&GPIO_InitStructure);//��ʼ��GPIO

     GPIO_ResetBits(GPIOG,GPIO_Pin_11); //�͵�ƽ
}
void GY53_Init (void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;     //GPIO_Mode_IN_FLOATING;//��������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
}

void TIM7_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
 
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ //5ms��һ����
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);//��ʼ��TIM7
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
 
	TIM_Cmd(TIM7,ENABLE); //ʹ�ܶ�ʱ��3
	
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	
}
void TIM7_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
  {
	  	time++;
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
  }
}

void TIM6_Int_Init()
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
 
  TIM_TimeBaseInitStructure.TIM_Period = 1000-1; 	//�Զ���װ��ֵ //5ms��һ����
	TIM_TimeBaseInitStructure.TIM_Prescaler=168-1;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);//��ʼ��TIM6
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); //����ʱ��6�����ж�
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn; //��ʱ��6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x04; //
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
 
	TIM_Cmd(TIM6,ENABLE); //ʹ�ܶ�ʱ��3
	
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	
}
void TIM6_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
  {
	  	time1++;
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
  }
}
static void OpenTimerForGY(void)         
{  
	//����TIM�������Ĵ�����ֵ
	TIM_SetCounter(TIM7,0); //�������  
	time = 0;  
	TIM_Cmd(TIM7,ENABLE);  //ʹ��TIMX����  
}  
   
/* �رն�ʱ�� */
static void CloseTimerForGY(void)           
{  
	TIM_Cmd(TIM7,DISABLE); //ʹ��TIMX����  
} 

uint32_t GetGYTimer(void)  
{  
	uint32_t t = 0;  
	t = time * 1000;      //��msת��Ϊus 
  t = t + TIM_GetCounter(TIM7);    //�õ���us  
	TIM7-> CNT = 0;       //��TIM6�����Ĵ����ļ���ֵ���� ����һ����������ֵ��  
	delay_ms(50);
	return t;  
}  


//һ�λ�ȡ����������β��֮����Ҫ���һ��ʱ�䣬���ϻ����ź�  
float Hcsr04GetLength(void)  
{  
	uint32_t t = 0;  
	float  lengthTemp = 0;  
	
	delay_ms(500);

	while (GY53_Receive == 0);      //�ȴ����տڸߵ�ƽ���  
	OpenTimerForGY();           //�򿪶�ʱ��  
		
	while (GY53_Receive == 1);  //
	CloseTimerForGY();         //�رն�ʱ�� 
	
	t = GetGYTimer();         //��ȡʱ�䣬�ֱ���Ϊ1US   
	
	lengthTemp = (float)t / 10;
		
	return lengthTemp;
}
float Hcsr04GetLength1(void)  
{  
	uint32_t t = 0;  
	float  lengthTemp = 0;  
	
	delay_ms(500);

	while (GY53_Receive1 == 0);      //�ȴ����տڸߵ�ƽ���  
	OpenTimerForGY();           //�򿪶�ʱ��  
		
	while (GY53_Receive1 == 1);  //
	CloseTimerForGY();         //�رն�ʱ�� 
	
	t = GetGYTimer();         //��ȡʱ�䣬�ֱ���Ϊ1US   
	
	lengthTemp = (float)t / 10;
		
	return lengthTemp;
}
float Hcsr04GetLength2(void)  
{  
	uint32_t t = 0;  
	float  lengthTemp = 0;  
	
	delay_ms(500);

	while (GY53_Receive2 == 0);      //�ȴ����տڸߵ�ƽ���  
	OpenTimerForGY();           //�򿪶�ʱ��  
		
	while (GY53_Receive2 == 1);  //
	CloseTimerForGY();         //�رն�ʱ�� 
	
	t = GetGYTimer();         //��ȡʱ�䣬�ֱ���Ϊ1US   
	
	lengthTemp = (float)t / 10;
		
	return lengthTemp;
}
float Hcsr04GetLength3(void)  
{  
	uint32_t t = 0;  
	float  lengthTemp = 0;  
	
	delay_ms(500);

	while (GY53_Receive3 == 0);      //�ȴ����տڸߵ�ƽ���  
	OpenTimerForGY();           //�򿪶�ʱ��  
		
	while (GY53_Receive3 == 1);  //
	CloseTimerForGY();         //�رն�ʱ�� 
	
	t = GetGYTimer();         //��ȡʱ�䣬�ֱ���Ϊ1US   
	
	lengthTemp = (float)t / 10;
		
	return lengthTemp;
}
/**************************************************************************
Function: The data sent by the serial port is assigned
Input   : none
Output  : none
�������ܣ����ڷ��͵����ݽ��и�ֵ
��ڲ�������
����  ֵ����
**************************************************************************/
void data_transition(void)
{
	Send_Data.Sensor_Str.Frame_Header = FRAME_HEADER_CAR; //Frame_header //֡ͷ
	Send_Data.Sensor_Str.Frame_Tail = FRAME_TAIL_CAR;     //Frame_tail //֡β
	
	//According to different vehicle types, different kinematics algorithms were selected to carry out the forward kinematics solution, 
	//and the three-axis velocity was obtained from each wheel velocity
	//���ݲ�ͬ����ѡ��ͬ�˶�ѧ�㷨�����˶�ѧ���⣬�Ӹ������ٶ���������ٶ�
	switch(Car_Mode)
	{	
		case Mec_Car:      
			Send_Data.Sensor_Str.X_speed = ((MOTOR_A.Encoder+MOTOR_B.Encoder+MOTOR_C.Encoder+MOTOR_D.Encoder)/4)*1000;
	    Send_Data.Sensor_Str.Y_speed = ((MOTOR_A.Encoder-MOTOR_B.Encoder+MOTOR_C.Encoder-MOTOR_D.Encoder)/4)*1000; 
	    Send_Data.Sensor_Str.Z_speed = ((-MOTOR_A.Encoder-MOTOR_B.Encoder+MOTOR_C.Encoder+MOTOR_D.Encoder)/4/(Axle_spacing+Wheel_spacing))*1000;         
		  break; 
		
		case FourWheel_Car:
      Send_Data.Sensor_Str.X_speed = ((MOTOR_A.Encoder+MOTOR_B.Encoder+MOTOR_C.Encoder+MOTOR_D.Encoder)/4)*1000; 
	    Send_Data.Sensor_Str.Y_speed = 0;
	    Send_Data.Sensor_Str.Z_speed = ((-MOTOR_B.Encoder-MOTOR_A.Encoder+MOTOR_C.Encoder+MOTOR_D.Encoder)/2/(Axle_spacing+Wheel_spacing))*1000;
		 break; 
		
		case Tank_Car:   
			Send_Data.Sensor_Str.X_speed = ((MOTOR_A.Encoder+MOTOR_B.Encoder)/2)*1000; 
			Send_Data.Sensor_Str.Y_speed = 0;
			Send_Data.Sensor_Str.Z_speed = ((MOTOR_B.Encoder-MOTOR_A.Encoder)/(Wheel_spacing)*1000);
			break; 
	}
	
	//The acceleration of the triaxial acceleration //���ٶȼ�������ٶ�
	Send_Data.Sensor_Str.Accelerometer.X_data= accel[1]; //The accelerometer Y-axis is converted to the ros coordinate X axis //���ٶȼ�Y��ת����ROS����X��
	Send_Data.Sensor_Str.Accelerometer.Y_data=-accel[0]; //The accelerometer X-axis is converted to the ros coordinate y axis //���ٶȼ�X��ת����ROS����Y��
	Send_Data.Sensor_Str.Accelerometer.Z_data= accel[2]; //The accelerometer Z-axis is converted to the ros coordinate Z axis //���ٶȼ�Z��ת����ROS����Z��
	
	//The Angle velocity of the triaxial velocity //���ٶȼ�������ٶ�
	Send_Data.Sensor_Str.Gyroscope.X_data= gyro[1]; //The Y-axis is converted to the ros coordinate X axis //���ٶȼ�Y��ת����ROS����X��
	Send_Data.Sensor_Str.Gyroscope.Y_data=-gyro[0]; //The X-axis is converted to the ros coordinate y axis //���ٶȼ�X��ת����ROS����Y��
	if(Flag_Stop==0) 
		//If the motor control bit makes energy state, the z-axis velocity is sent normall
	  //����������λʹ��״̬����ô��������Z����ٶ�
		Send_Data.Sensor_Str.Gyroscope.Z_data=gyro[2];  
	else  
		//If the robot is static (motor control dislocation), the z-axis is 0
    //����������Ǿ�ֹ�ģ��������λʧ�ܣ�����ô���͵�Z����ٶ�Ϊ0		
		Send_Data.Sensor_Str.Gyroscope.Z_data=0;        
	
	//Battery voltage (this is a thousand times larger floating point number, which will be reduced by a thousand times as well as receiving the data).
	//��ص�ѹ(���ｫ�������Ŵ�һǧ�����䣬��Ӧ���ڽ��ն��ڽ��յ����ݺ�Ҳ����Сһǧ��)
	Send_Data.Sensor_Str.Power_Voltage = Voltage*1000; 
	
	Send_Data.buffer[0]=Send_Data.Sensor_Str.Frame_Header; //Frame_heade //֡ͷ
  Send_Data.buffer[1]=Flag_Stop; //Car software loss marker //С�����ʧ�ܱ�־λ
	
	//The three-axis speed of / / car is split into two eight digit Numbers
	//С�������ٶ�,���ᶼ���Ϊ����8λ�����ٷ���
	Send_Data.buffer[2]=Send_Data.Sensor_Str.X_speed >>8; 
	Send_Data.buffer[3]=Send_Data.Sensor_Str.X_speed ;    
	Send_Data.buffer[4]=Send_Data.Sensor_Str.Y_speed>>8;  
	Send_Data.buffer[5]=Send_Data.Sensor_Str.Y_speed;     
	Send_Data.buffer[6]=Send_Data.Sensor_Str.Z_speed >>8; 
	Send_Data.buffer[7]=Send_Data.Sensor_Str.Z_speed ;    
	
	//The acceleration of the triaxial axis of / / imu accelerometer is divided into two eight digit reams
	//IMU���ٶȼ�������ٶ�,���ᶼ���Ϊ����8λ�����ٷ���
	Send_Data.buffer[8]=Send_Data.Sensor_Str.Accelerometer.X_data>>8; 
	Send_Data.buffer[9]=Send_Data.Sensor_Str.Accelerometer.X_data;   
	Send_Data.buffer[10]=Send_Data.Sensor_Str.Accelerometer.Y_data>>8;
	Send_Data.buffer[11]=Send_Data.Sensor_Str.Accelerometer.Y_data;
	Send_Data.buffer[12]=Send_Data.Sensor_Str.Accelerometer.Z_data>>8;
	Send_Data.buffer[13]=Send_Data.Sensor_Str.Accelerometer.Z_data;
	
	//The axis of the triaxial velocity of the / /imu is divided into two eight digits
	//IMU���ٶȼ�������ٶ�,���ᶼ���Ϊ����8λ�����ٷ���
	Send_Data.buffer[14]=Send_Data.Sensor_Str.Gyroscope.X_data>>8;
	Send_Data.buffer[15]=Send_Data.Sensor_Str.Gyroscope.X_data;
	Send_Data.buffer[16]=Send_Data.Sensor_Str.Gyroscope.Y_data>>8;
	Send_Data.buffer[17]=Send_Data.Sensor_Str.Gyroscope.Y_data;
	Send_Data.buffer[18]=Send_Data.Sensor_Str.Gyroscope.Z_data>>8;
	Send_Data.buffer[19]=Send_Data.Sensor_Str.Gyroscope.Z_data;
	
	//Battery voltage, split into two 8 digit Numbers
	//��ص�ѹ,���Ϊ����8λ���ݷ���
	Send_Data.buffer[20]=Send_Data.Sensor_Str.Power_Voltage >>8; 
	Send_Data.buffer[21]=Send_Data.Sensor_Str.Power_Voltage; 

  //Data check digit calculation, Pattern 1 is a data check
  //����У��λ���㣬ģʽ1�Ƿ�������У��
	Send_Data.buffer[22]=Check_Sum(22,1); 
	
	Send_Data.buffer[23]=Send_Data.Sensor_Str.Frame_Tail; //Frame_tail //֡β
}
/**************************************************************************
Function: Serial port 1 sends data
Input   : none
Output  : none
�������ܣ�����1��������
��ڲ�������
����  ֵ����
**************************************************************************/
void USART1_SEND(void)
{
  unsigned char i = 0;	
	
	for(i=0; i<24; i++)
	{
		usart1_send(Send_Data.buffer[i]);
	}	 
}
/**************************************************************************
Function: Serial port 3 sends data
Input   : none
Output  : none
�������ܣ�����3��������
��ڲ�������
����  ֵ����
**************************************************************************/
void USART3_SEND(void)
{
  unsigned char i = 0;	
	for(i=0; i<24; i++)
	{
		usart3_send(Send_Data.buffer[i]);
	}	 
}
/**************************************************************************
Function: Serial port 5 sends data
Input   : none
Output  : none
�������ܣ�����5��������
��ڲ�������
����  ֵ����
**************************************************************************/
void USART5_SEND(void)
{
  unsigned char i = 0;	
	for(i=0; i<24; i++)
	{
		usart5_send(Send_Data.buffer[i]);
	}	 
}
/**************************************************************************
Function: CAN sends data
Input   : none
Output  : none
�������ܣ�CAN��������
��ڲ�������
�� �� ֵ����
**************************************************************************/
void CAN_SEND(void) 
{
	u8 CAN_SENT[8],i;
	
	for(i=0;i<8;i++)
	{
	  CAN_SENT[i]=Send_Data.buffer[i];
	}
	CAN1_Send_Num(0x101,CAN_SENT);
	
	for(i=0;i<8;i++)
	{
	  CAN_SENT[i]=Send_Data.buffer[i+8];
	}
	CAN1_Send_Num(0x102,CAN_SENT);
	
	for(i=0;i<8;i++)
	{
	  CAN_SENT[i]=Send_Data.buffer[i+16];
	}
	CAN1_Send_Num(0x103,CAN_SENT);
}
/**************************************************************************
Function: Serial port 1 initialization
Input   : none
Output  : none
�������ܣ�����1��ʼ��
��ڲ�������
�� �� ֵ����
**************************************************************************/
//int fputc(int ch, FILE *f)
//{ 	
//	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
//	USART1->DR = (u8) ch;      
//	return ch;
//}

void uart1_init(u32 bound)
{  	 
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	 //Enable the gpio clock //ʹ��GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //Enable the Usart clock //ʹ��USARTʱ��

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10 ,GPIO_AF_USART1);	 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;            //���ģʽ
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;          //�������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;       //����50MHZ
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;            //����
	GPIO_Init(GPIOA, &GPIO_InitStructure);  		          //��ʼ��
	
  //UsartNVIC configuration //UsartNVIC����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	//Preempt priority //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	//Subpriority //�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	//Enable the IRQ channel //IRQͨ��ʹ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  //Initialize the VIC register with the specified parameters 
	//����ָ���Ĳ�����ʼ��VIC�Ĵ���	
	NVIC_Init(&NVIC_InitStructure);	
	
  //USART Initialization Settings ��ʼ������
	USART_InitStructure.USART_BaudRate = bound; //Port rate //���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //The word length is 8 bit data format //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //A stop bit //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No; //Prosaic parity bits //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //No hardware data flow control //��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//Sending and receiving mode //�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); //Initialize serial port 1 //��ʼ������1
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //Open the serial port to accept interrupts //�������ڽ����ж�
	USART_Cmd(USART1, ENABLE);                     //Enable serial port 1 //ʹ�ܴ���1
}
/**************************************************************************
Function: Serial port 2 initialization
Input   : none
Output  : none
�������ܣ�����2��ʼ��
��ڲ�������
����  ֵ����
**************************************************************************/
void uart2_init(u32 bound)
{  	 
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	 //Enable the gpio clock  //ʹ��GPIOʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //Enable the Usart clock //ʹ��USARTʱ��
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6 ,GPIO_AF_USART2);	 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;            //���ģʽ
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;          //�������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;       //����50MHZ
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;            //����
	GPIO_Init(GPIOD, &GPIO_InitStructure);  		          //��ʼ��
	USART_Cmd(USART2, ENABLE);                     //Enable serial port 2 //ʹ�ܴ���2 
	
	DMA_forUsart3IDLE_Init();
	
	//UsartNVIC configuration //UsartNVIC����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	//Preempt priority //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	//Subpriority //�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
  //Enable the IRQ channel //IRQͨ��ʹ��	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  //Initialize the VIC register with the specified parameters 
	//����ָ���Ĳ�����ʼ��VIC�Ĵ���		
	NVIC_Init(&NVIC_InitStructure);	
	
	//USART Initialization Settings ��ʼ������
	USART_InitStructure.USART_BaudRate = bound; //Port rate //���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //The word length is 8 bit data format //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //A stop bit //һ��ֹͣ
	USART_InitStructure.USART_Parity = USART_Parity_No; //Prosaic parity bits //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //No hardware data flow control //��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//Sending and receiving mode //�շ�ģʽ
	USART_Init(USART2, &USART_InitStructure);      //Initialize serial port 2 //��ʼ������2
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //Open the serial port to accept interrupts //�������ڽ����ж�
	
	DMA_ITConfig(DMA1_Stream1,DMA_IT_TC,ENABLE);
	
	
}
/**************************************************************************
Function: Serial port 3 initialization
Input   : none
Output  : none
�������ܣ�����3��ʼ��
��ڲ�������
����  ֵ����
**************************************************************************/
void uart3_init(u32 bound)
{  	

	//����ṹ��GPIO/USART/NVIC
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//ʹ��GPIOBʱ��
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);//���ô��ڣ���PB11����Ϊ����3����

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��PB11

	USART_InitStructure.USART_BaudRate=115200;//��������Ϊ115200
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	//������
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//ʹ�ܷ��ͽ���
	USART_InitStructure.USART_Parity=USART_Parity_No;					//��У��λ
	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//1λֹͣλ
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;	//8λ����λ
	
	USART_Init(USART3,&USART_InitStructure);//��ʼ������3
	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);//ʹ�ܽ���DMA
	 
	USART_Cmd(USART3,ENABLE);
  
	
	//DMA��ʼ��
//	DMA_forUsart3IDLE_Init();


//	//�ж����
	USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;//USART3�жϷ�����
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//�ж���ռ���ȼ���������
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//�ж���Ӧ���ȼ���������
	NVIC_Init(&NVIC_InitStructure);//��ʼ��NVIC
	
	//DMA�ж����ã�������1
	DMA_ITConfig(DMA1_Stream1,DMA_IT_TC,ENABLE);

	

  
  
}
void DMA_ITConfig(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
  assert_param(IS_DMA_CONFIG_IT(DMA_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Check if the DMA_IT parameter contains a FIFO interrupt */
  if ((DMA_IT & DMA_IT_FE) != 0)
  {
    if (NewState != DISABLE)
    {
      /* Enable the selected DMA FIFO interrupts */
      DMAy_Streamx->FCR |= (uint32_t)DMA_IT_FE;
    }    
    else 
    {
      /* Disable the selected DMA FIFO interrupts */
      DMAy_Streamx->FCR &= ~(uint32_t)DMA_IT_FE;  
    }
  }

  /* Check if the DMA_IT parameter contains a Transfer interrupt */
  if (DMA_IT != DMA_IT_FE)
  {
    if (NewState != DISABLE)
    {
      /* Enable the selected DMA transfer interrupts */
      DMAy_Streamx->CR |= (uint32_t)(DMA_IT  & TRANSFER_IT_ENABLE_MASK);
    }
    else
    {
      /* Disable the selected DMA transfer interrupts */
      DMAy_Streamx->CR &= ~(uint32_t)(DMA_IT & TRANSFER_IT_ENABLE_MASK);
    }    
  }
}
void DMA_Init(DMA_Stream_TypeDef* DMAy_Streamx, DMA_InitTypeDef* DMA_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
  assert_param(IS_DMA_CHANNEL(DMA_InitStruct->DMA_Channel));
  assert_param(IS_DMA_DIRECTION(DMA_InitStruct->DMA_DIR));
  assert_param(IS_DMA_BUFFER_SIZE(DMA_InitStruct->DMA_BufferSize));
  assert_param(IS_DMA_PERIPHERAL_INC_STATE(DMA_InitStruct->DMA_PeripheralInc));
  assert_param(IS_DMA_MEMORY_INC_STATE(DMA_InitStruct->DMA_MemoryInc));
  assert_param(IS_DMA_PERIPHERAL_DATA_SIZE(DMA_InitStruct->DMA_PeripheralDataSize));
  assert_param(IS_DMA_MEMORY_DATA_SIZE(DMA_InitStruct->DMA_MemoryDataSize));
  assert_param(IS_DMA_MODE(DMA_InitStruct->DMA_Mode));
  assert_param(IS_DMA_PRIORITY(DMA_InitStruct->DMA_Priority));
  assert_param(IS_DMA_FIFO_MODE_STATE(DMA_InitStruct->DMA_FIFOMode));
  assert_param(IS_DMA_FIFO_THRESHOLD(DMA_InitStruct->DMA_FIFOThreshold));
  assert_param(IS_DMA_MEMORY_BURST(DMA_InitStruct->DMA_MemoryBurst));
  assert_param(IS_DMA_PERIPHERAL_BURST(DMA_InitStruct->DMA_PeripheralBurst));

  /*------------------------- DMAy Streamx CR Configuration ------------------*/
  /* Get the DMAy_Streamx CR value */
  tmpreg = DMAy_Streamx->CR;

  /* Clear CHSEL, MBURST, PBURST, PL, MSIZE, PSIZE, MINC, PINC, CIRC and DIR bits */
  tmpreg &= ((uint32_t)~(DMA_SxCR_CHSEL | DMA_SxCR_MBURST | DMA_SxCR_PBURST | \
                         DMA_SxCR_PL | DMA_SxCR_MSIZE | DMA_SxCR_PSIZE | \
                         DMA_SxCR_MINC | DMA_SxCR_PINC | DMA_SxCR_CIRC | \
                         DMA_SxCR_DIR));

  /* Configure DMAy Streamx: */
  /* Set CHSEL bits according to DMA_CHSEL value */
  /* Set DIR bits according to DMA_DIR value */
  /* Set PINC bit according to DMA_PeripheralInc value */
  /* Set MINC bit according to DMA_MemoryInc value */
  /* Set PSIZE bits according to DMA_PeripheralDataSize value */
  /* Set MSIZE bits according to DMA_MemoryDataSize value */
  /* Set CIRC bit according to DMA_Mode value */
  /* Set PL bits according to DMA_Priority value */
  /* Set MBURST bits according to DMA_MemoryBurst value */
  /* Set PBURST bits according to DMA_PeripheralBurst value */
  tmpreg |= DMA_InitStruct->DMA_Channel | DMA_InitStruct->DMA_DIR |
            DMA_InitStruct->DMA_PeripheralInc | DMA_InitStruct->DMA_MemoryInc |
            DMA_InitStruct->DMA_PeripheralDataSize | DMA_InitStruct->DMA_MemoryDataSize |
            DMA_InitStruct->DMA_Mode | DMA_InitStruct->DMA_Priority |
            DMA_InitStruct->DMA_MemoryBurst | DMA_InitStruct->DMA_PeripheralBurst;

  /* Write to DMAy Streamx CR register */
  DMAy_Streamx->CR = tmpreg;

  /*------------------------- DMAy Streamx FCR Configuration -----------------*/
  /* Get the DMAy_Streamx FCR value */
  tmpreg = DMAy_Streamx->FCR;

  /* Clear DMDIS and FTH bits */
  tmpreg &= (uint32_t)~(DMA_SxFCR_DMDIS | DMA_SxFCR_FTH);

  /* Configure DMAy Streamx FIFO: 
    Set DMDIS bits according to DMA_FIFOMode value 
    Set FTH bits according to DMA_FIFOThreshold value */
  tmpreg |= DMA_InitStruct->DMA_FIFOMode | DMA_InitStruct->DMA_FIFOThreshold;

  /* Write to DMAy Streamx CR */
  DMAy_Streamx->FCR = tmpreg;

  /*------------------------- DMAy Streamx NDTR Configuration ----------------*/
  /* Write to DMAy Streamx NDTR register */
  DMAy_Streamx->NDTR = DMA_InitStruct->DMA_BufferSize;

  /*------------------------- DMAy Streamx PAR Configuration -----------------*/
  /* Write to DMAy Streamx PAR */
  DMAy_Streamx->PAR = DMA_InitStruct->DMA_PeripheralBaseAddr;

  /*------------------------- DMAy Streamx M0AR Configuration ----------------*/
  /* Write to DMAy Streamx M0AR */
  DMAy_Streamx->M0AR = DMA_InitStruct->DMA_Memory0BaseAddr;
}
FunctionalState DMA_GetCmdStatus(DMA_Stream_TypeDef* DMAy_Streamx)
{
  FunctionalState state = DISABLE;

  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));

  if ((DMAy_Streamx->CR & (uint32_t)DMA_SxCR_EN) != 0)
  {
    /* The selected DMAy Streamx EN bit is set (DMA is still transferring) */
    state = ENABLE;
  }
  else
  {
    /* The selected DMAy Streamx EN bit is cleared (DMA is disabled and 
        all transfers are complete) */
    state = DISABLE;
  }
  return state;
}   
void DMA_forUsart3IDLE_Init()
{
	//����DMA�ṹ��
		DMA_InitTypeDef DMA_InitStructure;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//DMA1 ʱ��ʹ��
	
		while (DMA_GetCmdStatus(DMA1_Stream1) != DISABLE){}//�ȴ� DMA ������
		
			DMA_InitStructure.DMA_Channel=DMA_Channel_4;//ͨ��4
			DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART2->DR;//DMA �����ַ   USART2�����ݼĴ�����ַ
			DMA_InitStructure.DMA_Memory0BaseAddr = (u32)bufferAngle;//DMA �洢��  0 ��ַ
			DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//�洢��������ģʽ
			DMA_InitStructure.DMA_BufferSize = 33;//���ݴ�����
			DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
			DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
			DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ���:8 λ
			DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ���:8 λ
			DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// ʹ����ͨģʽ
			DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//�е����ȼ�
			DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
			DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
			DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//���δ���
			DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
			
			//��ʼ��DMA
			DMA_Init(DMA1_Stream1,&DMA_InitStructure);
			//����3��DMAʹ��
			USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);
			//ʹ��DMA
			DMA_Cmd(DMA1_Stream1, ENABLE);



//һ��ʼ�ͺ�

//			���ö�Ӧ�� DMA �������������������С,����Ϊ��
//void DMA_SetCurrDataCounter(DMA_Stream_TypeDef* DMAy_Streamx, uint16_t Counter);

//FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG)
//��������Ҫ��ѯ DMA ������ 7 �����Ƿ���ɣ������ǣ�

//��ȡ��ǰʣ����������С�ĺ�����
//uint16_t DMA_GetCurrDataCounter(DMA_Stream_TypeDef* DMAy_Streamx);
//��������Ҫ��ȡ DMA ������ 7 ���ж��ٸ�����û�д��䣬�����ǣ�
//DMA_GetCurrDataCounter(DMA1_Channel4);
}
s16 getAngle(u8 axle)
{
		if(bufferAngle[0]==0x55&&bufferAngle[11]==0x55)//�ж�DMA���յ��������Ƿ���ȷ
		{
					switch(axle)//�������ݣ��������ص�ǰ�Ƕ�ֵ
					{
								case 1:{
								Angle_X=(u16)(((bufferAngle[25]<<8)|bufferAngle[24])/182);//(32768/180=182.04)
																			//��ת�ǣ�x �ᣩ Roll=((RollH<<8)|RollL)/32768*180(��)
								return Angle_X;
								}
								case 2:{
								Angle_Y=(u16)(((bufferAngle[27]<<8)|bufferAngle[26])/182);
																				//�����ǣ�y �ᣩ Pitch=((PitchH<<8)|PitchL)/32768*180(��)
								return Angle_Y;
								}
								case 3:{                                     //ƫ����(z��)
								Angle_Z=(u16)(((bufferAngle[29]<<8)|bufferAngle[28])/182);
								return Angle_Z;}
									
								case 4:{                                     //���ٶȣ�x �ᣩ 
								aacx=(u16)(((bufferAngle[3]<<8)|bufferAngle[2])/182);
								return aacx;}
									
								case 5:{                                     //���ٶȣ�y �ᣩ 
								aacy=(u16)(((bufferAngle[5]<<8)|bufferAngle[4])/182);
								return aacy;}
									
								case 6:{                                     //���ٶȣ�z �ᣩ 
								aacz=(u16)(((bufferAngle[7]<<8)|bufferAngle[6])/182);
								return aacz;
								}
								case 7:{                                     //���ٶȣ�z �ᣩ 
								gyrox=(u16)(((bufferAngle[14]<<8)|bufferAngle[13])/182);
								return gyrox;
								}
								case 8:{                                     //���ٶȣ�z �ᣩ 
								gyroy=(u16)(((bufferAngle[16]<<8)|bufferAngle[15])/182);
								return gyroy;
								}
								case 9:{                                     //���ٶȣ�z �ᣩ 
								gyroz=(u16)(((bufferAngle[18]<<8)|bufferAngle[17])/182);
								return gyroz;
								}
					}
		}
	   else//���ݴ���
		{
					USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);//���жϺ�����У׼
					switch(axle)//����֮ǰ׼������
								{
											case 1:{
											return Angle_X;
											}
											case 2:{
											return Angle_Y;
											}
											case 3:{
											return Angle_Z;
											}
											case 4:{
											return aacx;
											}
											case 5:{
											return aacy;
											}
											case 6:{
											return aacz;
											}
											case 7:{
											return gyrox;
											}
											case 8:{
											return gyroy;
											}
											case 9:{
											return gyroz;
											}
								}				
		}
		return Angle_Z;//û�÷�ֹ����
}

void _6zhou_calibration(void)
{
	int i;
	for(i=1;i<=9;i++)
	{
	getAngle(i);
	}

	
}
void Car_TurnAngle(s16 angle)
{
	u16 b;
	b=((s16)ANGLE_Z+360+angle)%360;
	
		Car_TurnToAngle(b);
}
	
void Car_TurnToAngle(s32 goal_Angle)
{
// s32 a	=	55;
	s32 b	=	goal_Angle-2;
			while(cos((b-ANGLE_Z)/57.3)<cos(60/57.3))//60��
	{
								if(sin((ANGLE_Z-b)/57.3)>=0)      //����Ƕȴ���0��,  Ŀ��ǶȺ͵�ǰ�Ƕ��Ƿ����0���180��
						{
								Drive_Motor(0.8,0.8,-0.8,-0.8);
		                
							
//								Set_Motor(70,-70);									//��ת
						}
						else
						{
//								Set_Motor(-70,70);		
								Drive_Motor(-0.8,-0.8,0.8,0.8);							//��ת
						}
	}	
//	Set_Motor(0,0);
//	delay_ms(10); 
	Drive_Motor(0,0,0,0);
	vTaskDelay(10);
			while(cos((b-ANGLE_Z)/57.3)<cos(35/57.3))//40��
	{
						if(sin((ANGLE_Z-b)/57.3)>=0)
				{
//						Set_Motor(60,-60);
					Drive_Motor(0.7,0.7,-0.7,-0.7);
				}
				else
				{
//						Set_Motor(-60,60);
					Drive_Motor(-0.7,-0.7,0.7,0.7);		
				}		
	}
		Drive_Motor(0,0,0,0);
	vTaskDelay(10);
//Set_Motor(0,0);
//delay_ms(10);

			while(cos((b-ANGLE_Z)/57.3)<cos(20/57.3))
	{
						if(sin((ANGLE_Z-b)/57.3)>=0)
				{
//						Set_Motor(50,-50);
					Drive_Motor(0.5,0.5,-0.5,-0.5);
				}
				else
				{
//						Set_Motor(-50,50);
					Drive_Motor(-0.5,-0.5,0.5,0.5);		
				}		
	}
		Drive_Motor(0,0,0,0);
	vTaskDelay(10);
//Set_Motor(0,0);
//delay_ms(5);
	while(cos((b-ANGLE_Z)/57.3)<cos(4/57.3))
	{
						if(sin((ANGLE_Z-b)/57.3)>=0)
				{
//						Set_Motor(30,-30);
					Drive_Motor(0.3,0.3,-0.3,-0.3);
				}
				else
				{
//						Set_Motor(-30,30);
					Drive_Motor(-0.3,-0.3,0.3,0.3);		
				}		
	}
		Drive_Motor(0,0,0,0);
	vTaskDelay(10);
//Set_Motor(0,0);
//delay_ms(20);
}

/**************************************************************************
Function: Serial port 5 initialization
Input   : none
Output  : none
�������ܣ�����5��ʼ��
��ڲ�������
����  ֵ����
**************************************************************************/
void uart5_init(u32 bound)
{  	 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//PC12 TX
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	 //Enable the gpio clock  //ʹ��GPIOʱ��
		//PD2 RX
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	 //Enable the gpio clock  //ʹ��GPIOʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE); //Enable the Usart clock //ʹ��USARTʱ��

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5);	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2 ,GPIO_AF_UART5);	 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;            //���ģʽ
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;          //�������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;       //����50MHZ
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;            //����
	GPIO_Init(GPIOC, &GPIO_InitStructure);  		          //��ʼ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;            //���ģʽ
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;          //�������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;       //����50MHZ
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;            //����
	GPIO_Init(GPIOD, &GPIO_InitStructure);  		          //��ʼ��
	
  //UsartNVIC configuration //UsartNVIC����
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	//Preempt priority //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	//Preempt priority //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	//Enable the IRQ channel //IRQͨ��ʹ��	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  //Initialize the VIC register with the specified parameters 
	//����ָ���Ĳ�����ʼ��VIC�Ĵ���		
	NVIC_Init(&NVIC_InitStructure);
	
  //USART Initialization Settings ��ʼ������
	USART_InitStructure.USART_BaudRate = bound; //Port rate //���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //The word length is 8 bit data format //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //A stop bit //һ��ֹͣ
	USART_InitStructure.USART_Parity = USART_Parity_No; //Prosaic parity bits //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //No hardware data flow control //��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//Sending and receiving mode //�շ�ģʽ
  USART_Init(UART5, &USART_InitStructure);      //Initialize serial port 5 //��ʼ������5
  USART_ITConfig(UART5, USART_IT_RXNE, ENABLE); //Open the serial port to accept interrupts //�������ڽ����ж�
  USART_Cmd(UART5, ENABLE);                     //Enable serial port 5 //ʹ�ܴ���5
}
/**************************************************************************
Function: Serial port 1 receives interrupted
Input   : none
Output  : none
�������ܣ�����1�����ж�
��ڲ�������
�� �� ֵ����
**************************************************************************/
void colour_data_deal(u8 data)
{
	RxBuffer_UARST1[RxCnt++] = data;	//���յ������ݴ��뻺������
	if (RxBuffer_UARST1[0] != 0x5a) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		LED1 = !LED1;delay_ms(100);
		RxCnt=0;
		return;
	}

	if (RxCnt < colour_data_Max_len) //���ݲ���5�����򷵻�
	{
		return;
	}
	else
	{
		if(RxBuffer_UARST1[5] != 0x5b)//����β���ԣ����¿�ʼ
		{
			RxCnt=0;
			return;
		}
		else
		{
			
			colour_type = RxBuffer_UARST1[1];
			colour_cx = RxBuffer_UARST1[2];
			colour_cy = RxBuffer_UARST1[3];
			colour_distance = RxBuffer_UARST1[4];
			RxCnt=0;
		}
		
	}
}
void code_data_deal(u8 data)
{
	Code_UARST1[CoCnt++] = data;	//���յ������ݴ��뻺������
//	if (Code_UARST1[0] != 0x55) //����ͷ���ԣ������¿�ʼѰ��0x5a����ͷ
//	{
////	LED1 = !LED1;delay_ms(100);
//		CoCnt=0;
//		return;	
//	}
//		if (CoCnt < code_data_Max_len) //���ݲ���3�����򷵻�
//	{
//		return;
//	}
//		else
//	{
//		if(Code_UARST1[7] != 0x0D)//����β���ԣ����¿�ʼ
//		{
//			CoCnt=0;
//			return;
//		}
//		else
//		{
//			code_number1 = Code_UARST1[1];
//			code_number2 = Code_UARST1[2];
//			code_number3 = Code_UARST1[3];
//			code_number4 = Code_UARST1[4];
//			code_number5 = Code_UARST1[5];
//			code_number6 = Code_UARST1[6];
//			CoCnt=0;
//		}
//	}
	if(CoCnt==8)
	{
	for(a=5;a<8;a++)
		{
			if(Code_UARST1[a]==0x55)
		{
			if(Code_UARST1[a+1]==0x0D)
			{
			code_number1 = Code_UARST1[7];
			code_number2 = Code_UARST1[0];
			code_number3 = Code_UARST1[1];
			code_number4 = Code_UARST1[2];
			code_number5 = Code_UARST1[3];
			code_number6 = Code_UARST1[4];

			}
		}
	}
		CoCnt=0;
	}
	
	
	
//
	
	
	
	
	
	
	
	
	
	
//	{
//		uartWriteshujv(1);
//		LED1 = !LED1;delay_ms(100);
//		CoCnt=0;
//		return;
//	}//int i;

//	if (CoCnt < code_data_Max_len) //���ݲ���3�����򷵻�
//	{
//		return;
//	}
//	else
//	{
//		if(Code_UARST1[2] != 0x5b)//����β���ԣ����¿�ʼ
//		{
//			CoCnt=0;
//			return;
//		}
//		else
//		{
//			code_number = Code_UARST1[1];
//			CoCnt=0;
//		}
//	}
}
void diatance_data_deal(u8 data)
{
	Code_UARST1[CoCnt++] = data;	//���յ������ݴ��뻺������

	if(CoCnt==8)
	{
	for(a=0;a<8;a++)
		{
			if(Code_UARST1[a]==0x55)
		{
			if(Code_UARST1[a+7]==0x0D)
			{
			code_number1 = Code_UARST1[1];
			code_number2 = Code_UARST1[2];
			code_number3 = Code_UARST1[3];
			code_number4 = Code_UARST1[4];
			code_number5 = Code_UARST1[5];
			code_number6 = Code_UARST1[6];

			}
		}
	}
		CoCnt=0;
	}

}
void USART1_IRQHandler(void)
{	
		u8 Res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������		
		if(tin==0)
		{
			
			colour_data_deal(Res);
//			openmv_deal(Res);
		}
		else
		{
			code_data_deal(Res);
		}			
  } 
	USART_ClearFlag(USART1,USART_FLAG_TC);

}
void QR_data_deal(void)
{

//	int i;
//	for(i=0;i<7;i++)
//	{
//	if(b[i]=='1')
//	{
//	c[i]='1';
//	}	
//	else if(b[i]=='2')
//	{
//	c[i]='2';
//	}
//	else if(b[i]=='3')
//	{
//	c[i]='3';
//	}
//	else if(b[i]=='+')
//	{
//	c[i]='+';
//	}
//	
//	}
	

	
}
void circle_data_deal(u8 data)
{
	 RxBuffer_UARST4[RxCnt4++] = data;	//????????????							
			if(RxCnt4==4)                     //RxBuffer_UARST1
			{        

				//RxBuffer_UARST1[0]0x5a
				for( a=0;a<4;a++)            //RxBuffer_UARST1[2]?0x5a
				{															
					if(RxBuffer_UARST4[a]==0x5a)
					{
						if(RxBuffer_UARST4[a+3]==0x5b)
						{
							
						
							cx=RxBuffer_UARST4[1];
							cy=RxBuffer_UARST4[2];
			      }
					}
				}
				RxCnt4=0;
			}
}


void openmv_deal(u8 date)
{
	RxBuffer_UARST4[RxCnt4++] = date;	//���յ������ݴ��뻺������							
  if (RxBuffer_UARST4[0] != 0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		
	
		RxCnt4=0;
		return;
	}

	if (RxCnt4 < 8) //���ݲ���8�����򷵻�
	{
		return;
	}
	else
	{
		if(RxBuffer_UARST4[7] != 0x56)//����β���ԣ����¿�ʼ
		{
			RxCnt4=0;
			return;
		}
		else
		{
			for(a=0; a<6; a++)
							{
								openmv_date[a] = RxBuffer_UARST4[a+1];
							}
			rho_err=openmv_date[1];
			theta_err=openmv_date[3];
			left_flag=openmv_date[4];
			right_flag=openmv_date[5];
			RxCnt4=0;
							
		}
	}
}
/**************************************************************************
Function: Ѳ��
Input   : none
Output  : none
�������ܣ�����2�����ж�
��ڲ�������
����  ֵ����
**************************************************************************/
void USART2_IRQHandler(void)
{
	

	
	u8 res;
   if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)	//?����?��?��y?Y
	{	 
		
USART_ClearITPendingBit(USART2,USART_IT_RXNE);   //����жϱ�־
	res = USART_ReceiveData(USART2);
			circle_data_deal(res);
//		openmv_deal(res);
}
}

/**************************************************************************
Function: Serial port 3 receives interrupted
Input   : none
Output  : none
�������ܣ�����3�����ж�
��ڲ�������
����  ֵ����
**************************************************************************/
void DMA_Cmd(DMA_Stream_TypeDef* DMAy_Streamx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected DMAy Streamx by setting EN bit */
    DMAy_Streamx->CR |= (uint32_t)DMA_SxCR_EN;
  }
  else
  {
    /* Disable the selected DMAy Streamx by clearing EN bit */
    DMAy_Streamx->CR &= ~(uint32_t)DMA_SxCR_EN;
  }
}

void USART3_IRQHandler(void)
{	

	int i;
//#if SYSTEM_SUPPORT_OS  //ʹ��UCOS����ϵͳ
//	OSIntEnter();  
//#endif  
		if(USART_GetITStatus(USART3,USART_IT_IDLE))//�����жϣ����ܵ�һ֡���ݾͲ����ж�
		{
			DMA_Cmd(DMA1_Stream1, DISABLE);//�ر�DMA
			DMA_forUsart3IDLE_Init();//��ʼ ��DMA
			USART_ITConfig(USART3,USART_IT_IDLE,DISABLE);//�ر�DMA�ж�����
			i++;
		}
//#if SYSTEM_SUPPORT_OS  
//	OSIntExit();    	//�˳��ж�
//#endif		
	

}

/**************************************************************************
Function: Serial port 5 receives interrupted
Input   : none
Output  : none
�������ܣ�����5�����ж�
��ڲ�������
����  ֵ����
**************************************************************************/
int UART5_IRQHandler(void)
{	
	
	
	
		   if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //�����ж�
	{
		USART_ClearITPendingBit(UART5, USART_IT_RXNE);
		RES=USART_ReceiveData(UART5);//(UART4->DR);	//��ȡ���յ�������
		b[m++] = RES;
//        //������ȥ����ɨ��ά�루��ά������������
//        //����һ��Ҫд��4����Ϊ����������������3+1��
        if(m == 8)
            m=0;
		USART_SendData(USART1,RES);
//		dataToSend = RES;
//		dataSent = 0;
	

		
		
	}
	USART_ClearFlag(UART5,USART_FLAG_TC);
	
	

  return 0;	
}
/**************************************************************************
Function: After the top 8 and low 8 figures are integrated into a short type data, the unit reduction is converted
Input   : 8 bits high, 8 bits low
Output  : The target velocity of the robot on the X/Y/Z axis
�������ܣ�����λ��������Ŀ��ǰ���ٶ�Vx��Ŀ����ٶ�Vz��ת��Ϊ������С������ǰ��ת��
��ڲ�����Ŀ��ǰ���ٶ�Vx��Ŀ����ٶ�Vz����λ��m/s��rad/s
����  ֵ��������С������ǰ��ת�ǣ���λ��rad
**************************************************************************/
float Vz_to_Akm_Angle(float Vx, float Vz)
{
	float R, AngleR, Min_Turn_Radius;
	//float AngleL;
	
	//Ackermann car needs to set minimum turning radius
	//If the target speed requires a turn radius less than the minimum turn radius,
	//This will greatly improve the friction force of the car, which will seriously affect the control effect
	//������С����Ҫ������Сת��뾶
	//���Ŀ���ٶ�Ҫ���ת��뾶С����Сת��뾶��
	//�ᵼ��С���˶�Ħ���������ߣ�����Ӱ�����Ч��
	Min_Turn_Radius=MINI_AKM_MIN_TURN_RADIUS;
	
	if(Vz!=0 && Vx!=0)
	{
		//If the target speed requires a turn radius less than the minimum turn radius
		//���Ŀ���ٶ�Ҫ���ת��뾶С����Сת��뾶
		if(float_abs(Vx/Vz)<=Min_Turn_Radius)
		{
			//Reduce the target angular velocity and increase the turning radius to the minimum turning radius in conjunction with the forward speed
			//����Ŀ����ٶȣ����ǰ���ٶȣ����ת��뾶����Сת��뾶
			if(Vz>0)
				Vz= float_abs(Vx)/(Min_Turn_Radius);
			else	
				Vz=-float_abs(Vx)/(Min_Turn_Radius);	
		}		
		R=Vx/Vz;
		//AngleL=atan(Axle_spacing/(R-0.5*Wheel_spacing));
		AngleR=atan(Axle_spacing/(R+0.5f*Wheel_spacing));
	}
	else
	{
		AngleR=0;
	}
	
	return AngleR;
}
/**************************************************************************
Function: After the top 8 and low 8 figures are integrated into a short type data, the unit reduction is converted
Input   : 8 bits high, 8 bits low
Output  : The target velocity of the robot on the X/Y/Z axis
�������ܣ�����λ���������ĸ�8λ�͵�8λ�������ϳ�һ��short�����ݺ�������λ��ԭ����
��ڲ�������8λ����8λ
����  ֵ��������X/Y/Z���Ŀ���ٶ�
**************************************************************************/
float XYZ_Target_Speed_transition(u8 High,u8 Low)
{
	//Data conversion intermediate variable
	//����ת�����м����
	short transition; 
	
	//����8λ�͵�8λ���ϳ�һ��16λ��short������
	//The high 8 and low 8 bits are integrated into a 16-bit short data
	transition=((High<<8)+Low); 
	return 
		transition/1000+(transition%1000)*0.001; //Unit conversion, mm/s->m/s //��λת��, mm/s->m/s						
}
/**************************************************************************
Function: Serial port 1 sends data
Input   : The data to send
Output  : none
�������ܣ�����1��������
��ڲ�����Ҫ���͵�����
����  ֵ����
**************************************************************************/
void usart1_send(u8 data)
{
	USART1->DR = data;
	while((USART1->SR&0x40)==0);	
}
/**************************************************************************
Function: Serial port 2 sends data
Input   : The data to send
Output  : none
�������ܣ�����2��������
��ڲ�����Ҫ���͵�����
����  ֵ����
**************************************************************************/
void usart2_send(u8 data)
{
	USART2->DR = data;
	while((USART2->SR&0x40)==0);	
}
/**************************************************************************
Function: Serial port 3 sends data
Input   : The data to send
Output  : none
�������ܣ�����3��������
��ڲ�����Ҫ���͵�����
����  ֵ����
**************************************************************************/
void usart3_send(u8 data)
{
	USART3->DR = data;
	while((USART3->SR&0x40)==0);	
}

/**************************************************************************
Function: Serial port 5 sends data
Input   : The data to send
Output  : none
�������ܣ�����5��������
��ڲ�����Ҫ���͵�����
����  ֵ����
**************************************************************************/
void usart5_send(u8 data)
{
	UART5->DR = data;
	while((UART5->SR&0x40)==0);	
}
/**************************************************************************
Function: Calculates the check bits of data to be sent/received
Input   : Count_Number: The first few digits of a check; Mode: 0-Verify the received data, 1-Validate the sent data
Output  : Check result
�������ܣ�����Ҫ����/���յ�����У����
��ڲ�����Count_Number��У���ǰ��λ����Mode��0-�Խ������ݽ���У�飬1-�Է������ݽ���У��
����  ֵ��У����
**************************************************************************/
u8 Check_Sum(unsigned char Count_Number,unsigned char Mode)
{
	unsigned char check_sum=0,k;
	
	//Validate the data to be sent
	//��Ҫ���͵����ݽ���У��
	if(Mode==1)
	for(k=0;k<Count_Number;k++)
	{
	check_sum=check_sum^Send_Data.buffer[k];
	}
	
	//Verify the data received
	//�Խ��յ������ݽ���У��
	if(Mode==0)
	for(k=0;k<Count_Number;k++)
	{
	check_sum=check_sum^Receive_Data.buffer[k];
	}
	return check_sum;
}






