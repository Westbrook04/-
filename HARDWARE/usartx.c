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


u8 colour_type;//1绿2红3蓝4白5黑
u8 colour_cx;
u8 colour_cy;
u8 colour_distance;

//void crazyMe(int i,u16 a,u16 b,u16 tim,u8 xf)//i：控制位 a：目前角度  b：目标角度	tim：每一步的时间		xf：动作分隔次数
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
					Drive_Motor(-0.05,0.03,-0.05,0.03);//靠近
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

//				Drive_Motor(-0.03,-0.03,0.03,0.03);//远离
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
//				Drive_Motor(0.03,0.03,-0.03,-0.03);//远离
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
//				Drive_Motor(0.03,-0.05,0.03,-0.05);//远离
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
函数功能：串口3、串口1、串口5、CAN发送数据任务
入口参数：无
返回  值：无
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
			//此任务以20Hz的频率运行
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
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//使能GPIOD时钟
//	
//    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;  //输入
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz; 
//	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;  //推挽输出
//	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;  //上拉
//	
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7; //PA13
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
// 
//}






void BEEP_Init(void)
{   
   	 GPIO_InitTypeDef GPIO_InitStructure;

	   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);//使能时钟
/*****************GPIO初始化************/
	   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	   GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	   GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	   GPIO_Init(GPIOG,&GPIO_InitStructure);//初始化GPIO

     GPIO_ResetBits(GPIOG,GPIO_Pin_11); //低电平
}
void GY53_Init (void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;     //GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
}

void TIM7_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
 
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值 //5ms记一次数
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);//初始化TIM7
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
 
	TIM_Cmd(TIM7,ENABLE); //使能定时器3
	
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
 
  TIM_TimeBaseInitStructure.TIM_Period = 1000-1; 	//自动重装载值 //5ms记一次数
	TIM_TimeBaseInitStructure.TIM_Prescaler=168-1;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);//初始化TIM6
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); //允许定时器6更新中断
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn; //定时器6中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x04; //
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
 
	TIM_Cmd(TIM6,ENABLE); //使能定时器3
	
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
	//设置TIM计数器寄存器的值
	TIM_SetCounter(TIM7,0); //清除计数  
	time = 0;  
	TIM_Cmd(TIM7,ENABLE);  //使能TIMX外设  
}  
   
/* 关闭定时器 */
static void CloseTimerForGY(void)           
{  
	TIM_Cmd(TIM7,DISABLE); //使能TIMX外设  
} 

uint32_t GetGYTimer(void)  
{  
	uint32_t t = 0;  
	t = time * 1000;      //将ms转化为us 
  t = t + TIM_GetCounter(TIM7);    //得到总us  
	TIM7-> CNT = 0;       //将TIM6计数寄存器的计数值清零 （上一个函数返回值）  
	delay_ms(50);
	return t;  
}  


//一次获取测距数据两次测距之间需要相隔一段时间，隔断回响信号  
float Hcsr04GetLength(void)  
{  
	uint32_t t = 0;  
	float  lengthTemp = 0;  
	
	delay_ms(500);

	while (GY53_Receive == 0);      //等待接收口高电平输出  
	OpenTimerForGY();           //打开定时器  
		
	while (GY53_Receive == 1);  //
	CloseTimerForGY();         //关闭定时器 
	
	t = GetGYTimer();         //获取时间，分辨率为1US   
	
	lengthTemp = (float)t / 10;
		
	return lengthTemp;
}
float Hcsr04GetLength1(void)  
{  
	uint32_t t = 0;  
	float  lengthTemp = 0;  
	
	delay_ms(500);

	while (GY53_Receive1 == 0);      //等待接收口高电平输出  
	OpenTimerForGY();           //打开定时器  
		
	while (GY53_Receive1 == 1);  //
	CloseTimerForGY();         //关闭定时器 
	
	t = GetGYTimer();         //获取时间，分辨率为1US   
	
	lengthTemp = (float)t / 10;
		
	return lengthTemp;
}
float Hcsr04GetLength2(void)  
{  
	uint32_t t = 0;  
	float  lengthTemp = 0;  
	
	delay_ms(500);

	while (GY53_Receive2 == 0);      //等待接收口高电平输出  
	OpenTimerForGY();           //打开定时器  
		
	while (GY53_Receive2 == 1);  //
	CloseTimerForGY();         //关闭定时器 
	
	t = GetGYTimer();         //获取时间，分辨率为1US   
	
	lengthTemp = (float)t / 10;
		
	return lengthTemp;
}
float Hcsr04GetLength3(void)  
{  
	uint32_t t = 0;  
	float  lengthTemp = 0;  
	
	delay_ms(500);

	while (GY53_Receive3 == 0);      //等待接收口高电平输出  
	OpenTimerForGY();           //打开定时器  
		
	while (GY53_Receive3 == 1);  //
	CloseTimerForGY();         //关闭定时器 
	
	t = GetGYTimer();         //获取时间，分辨率为1US   
	
	lengthTemp = (float)t / 10;
		
	return lengthTemp;
}
/**************************************************************************
Function: The data sent by the serial port is assigned
Input   : none
Output  : none
函数功能：串口发送的数据进行赋值
入口参数：无
返回  值：无
**************************************************************************/
void data_transition(void)
{
	Send_Data.Sensor_Str.Frame_Header = FRAME_HEADER_CAR; //Frame_header //帧头
	Send_Data.Sensor_Str.Frame_Tail = FRAME_TAIL_CAR;     //Frame_tail //帧尾
	
	//According to different vehicle types, different kinematics algorithms were selected to carry out the forward kinematics solution, 
	//and the three-axis velocity was obtained from each wheel velocity
	//根据不同车型选择不同运动学算法进行运动学正解，从各车轮速度求出三轴速度
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
	
	//The acceleration of the triaxial acceleration //加速度计三轴加速度
	Send_Data.Sensor_Str.Accelerometer.X_data= accel[1]; //The accelerometer Y-axis is converted to the ros coordinate X axis //加速度计Y轴转换到ROS坐标X轴
	Send_Data.Sensor_Str.Accelerometer.Y_data=-accel[0]; //The accelerometer X-axis is converted to the ros coordinate y axis //加速度计X轴转换到ROS坐标Y轴
	Send_Data.Sensor_Str.Accelerometer.Z_data= accel[2]; //The accelerometer Z-axis is converted to the ros coordinate Z axis //加速度计Z轴转换到ROS坐标Z轴
	
	//The Angle velocity of the triaxial velocity //角速度计三轴角速度
	Send_Data.Sensor_Str.Gyroscope.X_data= gyro[1]; //The Y-axis is converted to the ros coordinate X axis //角速度计Y轴转换到ROS坐标X轴
	Send_Data.Sensor_Str.Gyroscope.Y_data=-gyro[0]; //The X-axis is converted to the ros coordinate y axis //角速度计X轴转换到ROS坐标Y轴
	if(Flag_Stop==0) 
		//If the motor control bit makes energy state, the z-axis velocity is sent normall
	  //如果电机控制位使能状态，那么正常发送Z轴角速度
		Send_Data.Sensor_Str.Gyroscope.Z_data=gyro[2];  
	else  
		//If the robot is static (motor control dislocation), the z-axis is 0
    //如果机器人是静止的（电机控制位失能），那么发送的Z轴角速度为0		
		Send_Data.Sensor_Str.Gyroscope.Z_data=0;        
	
	//Battery voltage (this is a thousand times larger floating point number, which will be reduced by a thousand times as well as receiving the data).
	//电池电压(这里将浮点数放大一千倍传输，相应的在接收端在接收到数据后也会缩小一千倍)
	Send_Data.Sensor_Str.Power_Voltage = Voltage*1000; 
	
	Send_Data.buffer[0]=Send_Data.Sensor_Str.Frame_Header; //Frame_heade //帧头
  Send_Data.buffer[1]=Flag_Stop; //Car software loss marker //小车软件失能标志位
	
	//The three-axis speed of / / car is split into two eight digit Numbers
	//小车三轴速度,各轴都拆分为两个8位数据再发送
	Send_Data.buffer[2]=Send_Data.Sensor_Str.X_speed >>8; 
	Send_Data.buffer[3]=Send_Data.Sensor_Str.X_speed ;    
	Send_Data.buffer[4]=Send_Data.Sensor_Str.Y_speed>>8;  
	Send_Data.buffer[5]=Send_Data.Sensor_Str.Y_speed;     
	Send_Data.buffer[6]=Send_Data.Sensor_Str.Z_speed >>8; 
	Send_Data.buffer[7]=Send_Data.Sensor_Str.Z_speed ;    
	
	//The acceleration of the triaxial axis of / / imu accelerometer is divided into two eight digit reams
	//IMU加速度计三轴加速度,各轴都拆分为两个8位数据再发送
	Send_Data.buffer[8]=Send_Data.Sensor_Str.Accelerometer.X_data>>8; 
	Send_Data.buffer[9]=Send_Data.Sensor_Str.Accelerometer.X_data;   
	Send_Data.buffer[10]=Send_Data.Sensor_Str.Accelerometer.Y_data>>8;
	Send_Data.buffer[11]=Send_Data.Sensor_Str.Accelerometer.Y_data;
	Send_Data.buffer[12]=Send_Data.Sensor_Str.Accelerometer.Z_data>>8;
	Send_Data.buffer[13]=Send_Data.Sensor_Str.Accelerometer.Z_data;
	
	//The axis of the triaxial velocity of the / /imu is divided into two eight digits
	//IMU角速度计三轴角速度,各轴都拆分为两个8位数据再发送
	Send_Data.buffer[14]=Send_Data.Sensor_Str.Gyroscope.X_data>>8;
	Send_Data.buffer[15]=Send_Data.Sensor_Str.Gyroscope.X_data;
	Send_Data.buffer[16]=Send_Data.Sensor_Str.Gyroscope.Y_data>>8;
	Send_Data.buffer[17]=Send_Data.Sensor_Str.Gyroscope.Y_data;
	Send_Data.buffer[18]=Send_Data.Sensor_Str.Gyroscope.Z_data>>8;
	Send_Data.buffer[19]=Send_Data.Sensor_Str.Gyroscope.Z_data;
	
	//Battery voltage, split into two 8 digit Numbers
	//电池电压,拆分为两个8位数据发送
	Send_Data.buffer[20]=Send_Data.Sensor_Str.Power_Voltage >>8; 
	Send_Data.buffer[21]=Send_Data.Sensor_Str.Power_Voltage; 

  //Data check digit calculation, Pattern 1 is a data check
  //数据校验位计算，模式1是发送数据校验
	Send_Data.buffer[22]=Check_Sum(22,1); 
	
	Send_Data.buffer[23]=Send_Data.Sensor_Str.Frame_Tail; //Frame_tail //帧尾
}
/**************************************************************************
Function: Serial port 1 sends data
Input   : none
Output  : none
函数功能：串口1发送数据
入口参数：无
返回  值：无
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
函数功能：串口3发送数据
入口参数：无
返回  值：无
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
函数功能：串口5发送数据
入口参数：无
返回  值：无
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
函数功能：CAN发送数据
入口参数：无
返 回 值：无
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
函数功能：串口1初始化
入口参数：无
返 回 值：无
**************************************************************************/
//int fputc(int ch, FILE *f)
//{ 	
//	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
//	USART1->DR = (u8) ch;      
//	return ch;
//}

void uart1_init(u32 bound)
{  	 
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	 //Enable the gpio clock //使能GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //Enable the Usart clock //使能USART时钟

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10 ,GPIO_AF_USART1);	 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;            //输出模式
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;          //推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;       //高速50MHZ
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);  		          //初始化
	
  //UsartNVIC configuration //UsartNVIC配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	//Preempt priority //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	//Subpriority //子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	//Enable the IRQ channel //IRQ通道使能
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  //Initialize the VIC register with the specified parameters 
	//根据指定的参数初始化VIC寄存器	
	NVIC_Init(&NVIC_InitStructure);	
	
  //USART Initialization Settings 初始化设置
	USART_InitStructure.USART_BaudRate = bound; //Port rate //串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //The word length is 8 bit data format //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //A stop bit //一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No; //Prosaic parity bits //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //No hardware data flow control //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//Sending and receiving mode //收发模式
	USART_Init(USART1, &USART_InitStructure); //Initialize serial port 1 //初始化串口1
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //Open the serial port to accept interrupts //开启串口接受中断
	USART_Cmd(USART1, ENABLE);                     //Enable serial port 1 //使能串口1
}
/**************************************************************************
Function: Serial port 2 initialization
Input   : none
Output  : none
函数功能：串口2初始化
入口参数：无
返回  值：无
**************************************************************************/
void uart2_init(u32 bound)
{  	 
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	 //Enable the gpio clock  //使能GPIO时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //Enable the Usart clock //使能USART时钟
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6 ,GPIO_AF_USART2);	 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;            //输出模式
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;          //推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;       //高速50MHZ
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);  		          //初始化
	USART_Cmd(USART2, ENABLE);                     //Enable serial port 2 //使能串口2 
	
	DMA_forUsart3IDLE_Init();
	
	//UsartNVIC configuration //UsartNVIC配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	//Preempt priority //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	//Subpriority //子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
  //Enable the IRQ channel //IRQ通道使能	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  //Initialize the VIC register with the specified parameters 
	//根据指定的参数初始化VIC寄存器		
	NVIC_Init(&NVIC_InitStructure);	
	
	//USART Initialization Settings 初始化设置
	USART_InitStructure.USART_BaudRate = bound; //Port rate //串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //The word length is 8 bit data format //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //A stop bit //一个停止
	USART_InitStructure.USART_Parity = USART_Parity_No; //Prosaic parity bits //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //No hardware data flow control //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//Sending and receiving mode //收发模式
	USART_Init(USART2, &USART_InitStructure);      //Initialize serial port 2 //初始化串口2
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //Open the serial port to accept interrupts //开启串口接受中断
	
	DMA_ITConfig(DMA1_Stream1,DMA_IT_TC,ENABLE);
	
	
}
/**************************************************************************
Function: Serial port 3 initialization
Input   : none
Output  : none
函数功能：串口3初始化
入口参数：无
返回  值：无
**************************************************************************/
void uart3_init(u32 bound)
{  	

	//定义结构体GPIO/USART/NVIC
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART3时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//使能GPIOB时钟
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);//复用串口，将PB11复用为串口3接受

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化PB11

	USART_InitStructure.USART_BaudRate=115200;//波特率设为115200
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	//数据流
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//使能发送接收
	USART_InitStructure.USART_Parity=USART_Parity_No;					//无校验位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//1位停止位
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;	//8位数据位
	
	USART_Init(USART3,&USART_InitStructure);//初始化串口3
	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);//使能接收DMA
	 
	USART_Cmd(USART3,ENABLE);
  
	
	//DMA初始化
//	DMA_forUsart3IDLE_Init();


//	//中断相关
	USART_ITConfig(USART3,USART_IT_IDLE,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;//USART3中断服务函数
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//中断抢占优先级分组设置
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//中断响应优先级分组设置
	NVIC_Init(&NVIC_InitStructure);//初始化NVIC
	
	//DMA中断配置，数据流1
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
	//定义DMA结构体
		DMA_InitTypeDef DMA_InitStructure;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//DMA1 时钟使能
	
		while (DMA_GetCmdStatus(DMA1_Stream1) != DISABLE){}//等待 DMA 可配置
		
			DMA_InitStructure.DMA_Channel=DMA_Channel_4;//通道4
			DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART2->DR;//DMA 外设地址   USART2的数据寄存器地址
			DMA_InitStructure.DMA_Memory0BaseAddr = (u32)bufferAngle;//DMA 存储器  0 地址
			DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//存储器到外设模式
			DMA_InitStructure.DMA_BufferSize = 33;//数据传输量
			DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设非增量模式
			DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//存储器增量模式
			DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据长度:8 位
			DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//存储器数据长度:8 位
			DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// 使用普通模式
			DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//中等优先级
			DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
			DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
			DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//单次传输
			DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//外设突发单次传输
			
			//初始化DMA
			DMA_Init(DMA1_Stream1,&DMA_InitStructure);
			//串口3的DMA使能
			USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);
			//使能DMA
			DMA_Cmd(DMA1_Stream1, ENABLE);



//一开始就黑

//			设置对应的 DMA 数据流传输的数据量大小,函数为：
//void DMA_SetCurrDataCounter(DMA_Stream_TypeDef* DMAy_Streamx, uint16_t Counter);

//FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG)
//比如我们要查询 DMA 数据流 7 传输是否完成，方法是：

//获取当前剩余数据量大小的函数：
//uint16_t DMA_GetCurrDataCounter(DMA_Stream_TypeDef* DMAy_Streamx);
//比如我们要获取 DMA 数据流 7 还有多少个数据没有传输，方法是：
//DMA_GetCurrDataCounter(DMA1_Channel4);
}
s16 getAngle(u8 axle)
{
		if(bufferAngle[0]==0x55&&bufferAngle[11]==0x55)//判断DMA接收到的数据是否正确
		{
					switch(axle)//更新数据，，并返回当前角度值
					{
								case 1:{
								Angle_X=(u16)(((bufferAngle[25]<<8)|bufferAngle[24])/182);//(32768/180=182.04)
																			//滚转角（x 轴） Roll=((RollH<<8)|RollL)/32768*180(°)
								return Angle_X;
								}
								case 2:{
								Angle_Y=(u16)(((bufferAngle[27]<<8)|bufferAngle[26])/182);
																				//俯仰角（y 轴） Pitch=((PitchH<<8)|PitchL)/32768*180(°)
								return Angle_Y;
								}
								case 3:{                                     //偏航角(z轴)
								Angle_Z=(u16)(((bufferAngle[29]<<8)|bufferAngle[28])/182);
								return Angle_Z;}
									
								case 4:{                                     //加速度（x 轴） 
								aacx=(u16)(((bufferAngle[3]<<8)|bufferAngle[2])/182);
								return aacx;}
									
								case 5:{                                     //加速度（y 轴） 
								aacy=(u16)(((bufferAngle[5]<<8)|bufferAngle[4])/182);
								return aacy;}
									
								case 6:{                                     //加速度（z 轴） 
								aacz=(u16)(((bufferAngle[7]<<8)|bufferAngle[6])/182);
								return aacz;
								}
								case 7:{                                     //角速度（z 轴） 
								gyrox=(u16)(((bufferAngle[14]<<8)|bufferAngle[13])/182);
								return gyrox;
								}
								case 8:{                                     //角速度（z 轴） 
								gyroy=(u16)(((bufferAngle[16]<<8)|bufferAngle[15])/182);
								return gyroy;
								}
								case 9:{                                     //角速度（z 轴） 
								gyroz=(u16)(((bufferAngle[18]<<8)|bufferAngle[17])/182);
								return gyroz;
								}
					}
		}
	   else//数据错误
		{
					USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);//在中断函数中校准
					switch(axle)//返回之前准的数据
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
		return Angle_Z;//没用防止报错
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
			while(cos((b-ANGLE_Z)/57.3)<cos(60/57.3))//60°
	{
								if(sin((ANGLE_Z-b)/57.3)>=0)      //算出角度大于0度,  目标角度和当前角度是否相差0°或180°
						{
								Drive_Motor(0.8,0.8,-0.8,-0.8);
		                
							
//								Set_Motor(70,-70);									//右转
						}
						else
						{
//								Set_Motor(-70,70);		
								Drive_Motor(-0.8,-0.8,0.8,0.8);							//左转
						}
	}	
//	Set_Motor(0,0);
//	delay_ms(10); 
	Drive_Motor(0,0,0,0);
	vTaskDelay(10);
			while(cos((b-ANGLE_Z)/57.3)<cos(35/57.3))//40°
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
函数功能：串口5初始化
入口参数：无
返回  值：无
**************************************************************************/
void uart5_init(u32 bound)
{  	 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//PC12 TX
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	 //Enable the gpio clock  //使能GPIO时钟
		//PD2 RX
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	 //Enable the gpio clock  //使能GPIO时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE); //Enable the Usart clock //使能USART时钟

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5);	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2 ,GPIO_AF_UART5);	 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;            //输出模式
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;          //推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;       //高速50MHZ
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);  		          //初始化

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;            //输出模式
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;          //推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;       //高速50MHZ
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);  		          //初始化
	
  //UsartNVIC configuration //UsartNVIC配置
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	//Preempt priority //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	//Preempt priority //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	//Enable the IRQ channel //IRQ通道使能	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  //Initialize the VIC register with the specified parameters 
	//根据指定的参数初始化VIC寄存器		
	NVIC_Init(&NVIC_InitStructure);
	
  //USART Initialization Settings 初始化设置
	USART_InitStructure.USART_BaudRate = bound; //Port rate //串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //The word length is 8 bit data format //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //A stop bit //一个停止
	USART_InitStructure.USART_Parity = USART_Parity_No; //Prosaic parity bits //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //No hardware data flow control //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//Sending and receiving mode //收发模式
  USART_Init(UART5, &USART_InitStructure);      //Initialize serial port 5 //初始化串口5
  USART_ITConfig(UART5, USART_IT_RXNE, ENABLE); //Open the serial port to accept interrupts //开启串口接受中断
  USART_Cmd(UART5, ENABLE);                     //Enable serial port 5 //使能串口5
}
/**************************************************************************
Function: Serial port 1 receives interrupted
Input   : none
Output  : none
函数功能：串口1接收中断
入口参数：无
返 回 值：无
**************************************************************************/
void colour_data_deal(u8 data)
{
	RxBuffer_UARST1[RxCnt++] = data;	//将收到的数据存入缓冲区中
	if (RxBuffer_UARST1[0] != 0x5a) //数据头不对，则重新开始寻找0x55数据头
	{
		LED1 = !LED1;delay_ms(100);
		RxCnt=0;
		return;
	}

	if (RxCnt < colour_data_Max_len) //数据不满5个，则返回
	{
		return;
	}
	else
	{
		if(RxBuffer_UARST1[5] != 0x5b)//数据尾不对，重新开始
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
	Code_UARST1[CoCnt++] = data;	//将收到的数据存入缓冲区中
//	if (Code_UARST1[0] != 0x55) //数据头不对，则重新开始寻找0x5a数据头
//	{
////	LED1 = !LED1;delay_ms(100);
//		CoCnt=0;
//		return;	
//	}
//		if (CoCnt < code_data_Max_len) //数据不满3个，则返回
//	{
//		return;
//	}
//		else
//	{
//		if(Code_UARST1[7] != 0x0D)//数据尾不对，重新开始
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

//	if (CoCnt < code_data_Max_len) //数据不满3个，则返回
//	{
//		return;
//	}
//	else
//	{
//		if(Code_UARST1[2] != 0x5b)//数据尾不对，重新开始
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
	Code_UARST1[CoCnt++] = data;	//将收到的数据存入缓冲区中

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

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据		
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
	RxBuffer_UARST4[RxCnt4++] = date;	//将收到的数据存入缓冲区中							
  if (RxBuffer_UARST4[0] != 0x55) //数据头不对，则重新开始寻找0x55数据头
	{
		
	
		RxCnt4=0;
		return;
	}

	if (RxCnt4 < 8) //数据不满8个，则返回
	{
		return;
	}
	else
	{
		if(RxBuffer_UARST4[7] != 0x56)//数据尾不对，重新开始
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
Function: 巡线
Input   : none
Output  : none
函数功能：串口2接收中断
入口参数：无
返回  值：无
**************************************************************************/
void USART2_IRQHandler(void)
{
	

	
	u8 res;
   if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)	//?óê?μ?êy?Y
	{	 
		
USART_ClearITPendingBit(USART2,USART_IT_RXNE);   //清除中断标志
	res = USART_ReceiveData(USART2);
			circle_data_deal(res);
//		openmv_deal(res);
}
}

/**************************************************************************
Function: Serial port 3 receives interrupted
Input   : none
Output  : none
函数功能：串口3接收中断
入口参数：无
返回  值：无
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
//#if SYSTEM_SUPPORT_OS  //使用UCOS操作系统
//	OSIntEnter();  
//#endif  
		if(USART_GetITStatus(USART3,USART_IT_IDLE))//接受中断，接受到一帧数据就产生中断
		{
			DMA_Cmd(DMA1_Stream1, DISABLE);//关闭DMA
			DMA_forUsart3IDLE_Init();//初始 化DMA
			USART_ITConfig(USART3,USART_IT_IDLE,DISABLE);//关闭DMA中断配置
			i++;
		}
//#if SYSTEM_SUPPORT_OS  
//	OSIntExit();    	//退出中断
//#endif		
	

}

/**************************************************************************
Function: Serial port 5 receives interrupted
Input   : none
Output  : none
函数功能：串口5接收中断
入口参数：无
返回  值：无
**************************************************************************/
int UART5_IRQHandler(void)
{	
	
	
	
		   if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //接收中断
	{
		USART_ClearITPendingBit(UART5, USART_IT_RXNE);
		RES=USART_ReceiveData(UART5);//(UART4->DR);	//读取接收到的数据
		b[m++] = RES;
//        //用数组去接收扫二维码（二维码是三个数）
//        //下面一定要写成4，因为它发过来的数据是3+1个
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
函数功能：将上位机发过来目标前进速度Vx、目标角速度Vz，转换为阿克曼小车的右前轮转角
入口参数：目标前进速度Vx、目标角速度Vz，单位：m/s，rad/s
返回  值：阿克曼小车的右前轮转角，单位：rad
**************************************************************************/
float Vz_to_Akm_Angle(float Vx, float Vz)
{
	float R, AngleR, Min_Turn_Radius;
	//float AngleL;
	
	//Ackermann car needs to set minimum turning radius
	//If the target speed requires a turn radius less than the minimum turn radius,
	//This will greatly improve the friction force of the car, which will seriously affect the control effect
	//阿克曼小车需要设置最小转弯半径
	//如果目标速度要求的转弯半径小于最小转弯半径，
	//会导致小车运动摩擦力大大提高，严重影响控制效果
	Min_Turn_Radius=MINI_AKM_MIN_TURN_RADIUS;
	
	if(Vz!=0 && Vx!=0)
	{
		//If the target speed requires a turn radius less than the minimum turn radius
		//如果目标速度要求的转弯半径小于最小转弯半径
		if(float_abs(Vx/Vz)<=Min_Turn_Radius)
		{
			//Reduce the target angular velocity and increase the turning radius to the minimum turning radius in conjunction with the forward speed
			//降低目标角速度，配合前进速度，提高转弯半径到最小转弯半径
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
函数功能：将上位机发过来的高8位和低8位数据整合成一个short型数据后，再做单位还原换算
入口参数：高8位，低8位
返回  值：机器人X/Y/Z轴的目标速度
**************************************************************************/
float XYZ_Target_Speed_transition(u8 High,u8 Low)
{
	//Data conversion intermediate variable
	//数据转换的中间变量
	short transition; 
	
	//将高8位和低8位整合成一个16位的short型数据
	//The high 8 and low 8 bits are integrated into a 16-bit short data
	transition=((High<<8)+Low); 
	return 
		transition/1000+(transition%1000)*0.001; //Unit conversion, mm/s->m/s //单位转换, mm/s->m/s						
}
/**************************************************************************
Function: Serial port 1 sends data
Input   : The data to send
Output  : none
函数功能：串口1发送数据
入口参数：要发送的数据
返回  值：无
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
函数功能：串口2发送数据
入口参数：要发送的数据
返回  值：无
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
函数功能：串口3发送数据
入口参数：要发送的数据
返回  值：无
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
函数功能：串口5发送数据
入口参数：要发送的数据
返回  值：无
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
函数功能：计算要发送/接收的数据校验结果
入口参数：Count_Number：校验的前几位数；Mode：0-对接收数据进行校验，1-对发送数据进行校验
返回  值：校验结果
**************************************************************************/
u8 Check_Sum(unsigned char Count_Number,unsigned char Mode)
{
	unsigned char check_sum=0,k;
	
	//Validate the data to be sent
	//对要发送的数据进行校验
	if(Mode==1)
	for(k=0;k<Count_Number;k++)
	{
	check_sum=check_sum^Send_Data.buffer[k];
	}
	
	//Verify the data received
	//对接收到的数据进行校验
	if(Mode==0)
	for(k=0;k<Count_Number;k++)
	{
	check_sum=check_sum^Receive_Data.buffer[k];
	}
	return check_sum;
}






