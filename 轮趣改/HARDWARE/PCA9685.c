/**
  ******************************************************************************
  * @file    	PCA9685.c
  * @author  	MC_Wang
  * @version 	V1.0
  * @date    	2021年3月27日
  * @brief   	STM32通过模拟IIC协议与PCA9685通讯
 @verbatim
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================
    [..]
      (#)使用setPWMFreq(u8 freq)函数初始化PCA9685;
			(++)u8 freq:设置舵机的PWM频率；这里使用u8类型(0~255)
			但PCA9685可以设置最大约为1.6KHz的频率，如果要设置更大频率，需要改形参类型和PCA9685_write(unsigned char reg,unsigned char data)
			有兴趣可以自己试试，我这里就用u8类型，舵机50Hz；将freq = 50;即可
	  (#)使用PCA9685_write(unsigned char reg,unsigned char data)向选中的PCA9685的XX寄存器写XX数据
			(++)unsigned char reg：PCA9685寄存器地址
			(++)unsigned char data:向选中的PCA9685的某寄存器写入的数据
	  (#)使用u8 PCA9685_read(unsigned char reg)向选中的PCA9685的XX寄存器读取XX数据
			(++)unsigned char reg：PCA9685寄存器地址
			(++)返回值为PCA9685某寄存器的数据
	  (#)设置PCA9685某通道的占空比，请使用setPWM(u8 num, u16 on, u16 off)
	  (#)将舵机的角度转换成LEDx_OFF的值，请使用calculate_PWM(u8 angle)
 @endverbatim
  *
  ******************************************************************************
  * @attention
  * <h2><center>&copy; COPYRIGHT 2021 JXUST@WangMingcong</center></h2>
	******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "PCA9685.h"
#include "myiic.h"
#include "delay.h"
#include "math.h"
#include "usart.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup PCA9685_Private_Functions
  * @{
  */
/** @defgroup PCA9685 Initialization and Configuration
 *  @brief   Initialization and Configuration
 *
 @verbatim
 ===============================================================================
                 ##### PCA9685初始化和设置PCA9685的PWM频率 #####
 ===============================================================================

 @endverbatim
  * @{
  */


void PCA9685_Init()
{
    IIC_Init();
    PCA9685_write(PCA9685_MODE1,0x0);
    setPWMFreq(50);//舵机50Hz
}
/**
  * @brief  向选中的PCA9685的XX寄存器写XX数据
  * @note   先选中PCA9685，STM32先通过IIC向PCA9685写PCA9685设备地址,即PCA9685_adrr：0x80
						再通过形参将数据写入到PCA9685寄存器中
  * @param  unsigned char reg
  *            @arg 寄存器地址
  * @param  unsigned char data
  *            @arg 向寄存器写入的内容
  * @date   2021年3月27日
  * @retval None
  */
void PCA9685_write(unsigned char reg,unsigned char data)
{
    IIC_Start();
    IIC_Send_Byte(PCA9685_adrr);
    IIC_Wait_Ack();
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();
    IIC_Send_Byte(data);
    IIC_Wait_Ack();
    IIC_Stop();
}
/**
  * @brief  向选中的PCA9685的XX寄存器读取XX数据
  * @note   先选中PCA9685，STM32先通过IIC向PCA9685写PCA9685设备地址,即PCA9685_adrr：0x80
						再通过形参读取PCA9685寄存器中的数据
  * @param  unsigned char reg
  *            @arg PCA9685寄存器地址
  * @date   2021年3月27日
  * @retval  读取到寄存器中的数据
  */
u8 PCA9685_read(unsigned char reg)
{
    u8 res;
    IIC_Start();
    IIC_Send_Byte(PCA9685_adrr);
    IIC_Wait_Ack();
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();
    IIC_Start();
    IIC_Send_Byte(PCA9685_adrr|0X01);
    IIC_Wait_Ack();
    res=IIC_Read_Byte(0);
    IIC_Stop();
    return res;
}

/**
  * @brief  初始化PCA9685并设置PWM输出频率
  * @note   1.读出PCA9685的MODE1寄存器的值:oldmode == 0x33 = 0011 0011(不复位、使用内部25MHz时钟、内部地址读写完后自动增加、进入sleep、响应0x70通用IIC地址)
						2.不复位PCA9685且进入sleep模式
						3.操作PCA9685的PRE_SCALE寄存器，设置PCA9685的输出PWM频率
						4.退出sleep模式
  * @param  u8 freq
  *            @arg  设置PCA9685的输出PWM频率（0~255）Hz，也就是PPT中的update_rate
  * @date   2021年3月27日
  * @retval None
  */
void setPWMFreq(u8 freq)
{
    u8 prescale,oldmode,newmode;
    double prescaleval;
    prescaleval = 25000000.0/(4096*freq*0.915);
    prescale = (u8)floor(prescaleval+0.5)-1;//floor()：向下取整函数

    oldmode = PCA9685_read(PCA9685_MODE1);
//测试使用：
//		printf("%d\r\n",oldmode);//oldmode == 0x33 = 0011 0011
    newmode = (oldmode&0x7F) | 0x10; // 不复位且进入sleep模式
    PCA9685_write(PCA9685_MODE1, newmode); // go to sleep
    PCA9685_write(PCA9685_PRESCALE, prescale); // set the prescaler
    PCA9685_write(PCA9685_MODE1, oldmode);
    delay_ms(5);
    PCA9685_write(PCA9685_MODE1, oldmode | 0xa1); //1010 0001
}


/**
  * @brief  设置各个通道的ON和OFF寄存器，从而达到改变PCA9685输出PWM的占空比
  * @note   因为PCA9685的PWM是12位的，所以传入的参数为u16（16位才可以装下12位的数据）
						在16位数据中，高四位没用，on和off的值在0~4096 慎用
  * @param  u8 num      
  *            @arg	通道号 (0~15)                  
  * @param  u16 on
  *            @arg 计到LEDX_ON时跳变为高电平
  * @param  u16 off
  *            @arg 计数到LEDX_OFF时跳变为低电平
  * @date  	2021年3月27日
  * @retval None
  */
void setPWM(u8 num, u16 on, u16 off)
{
    PCA9685_write(LED0_ON_L+4*num,on);
    PCA9685_write(LED0_ON_H+4*num,on>>8);
    PCA9685_write(LED0_OFF_L+4*num,off);
    PCA9685_write(LED0_OFF_H+4*num,off>>8);
}



/**
  * @brief  将舵机的角度计算成12位LEDX_OFF的值
  * @author MC_Wang
  * @note   通过计算公式，将舵机的角度计算成12位LEDX_OFF的值
计算公式：PWM = 4096*(0.5 + (2.5-0.5)*(u8 angle)/180)/20

  * @param  u8 angle       
  *            @arg 舵机角度                    
  * @date  	2021年3月27日
  * @retval 12位LEDX_OFF的值
  */
u16 calculate_PWM(u8 angle)
{
    return (int)(204.8*(0.5+angle*1.0/90));
}

/************************ (C) COPYRIGHT JXUST@WangMingcong *****END OF FILE****/
void crazyMe(int i,u16 a,u16 b,u16 tim,u8 xf)//i：控制位 a：目前角度  b：目标角度	tim：每一步的时间		xf：动作分隔次数
{
	u16 k,m;
	u8 s;
	for(s=0;s<=xf;s++)
	{
		if(a>b)
		{
			k=calculate_PWM(a)-calculate_PWM(b);
		}
		else
			k=calculate_PWM(b)-calculate_PWM(a);;
		if(a>b)
		{
			m=calculate_PWM(a)-k*s/xf;
		}
		else
			m=calculate_PWM(a)+k*s/xf;
		setPWM(i,0,m);
		delay_ms(tim);
	}
}


/*************************************************

对一个姿势到另一个姿势进行分片段运动
a:起始绝对角度
b:目标绝对角度
tim:每份片段延时时
xf：片段份数
	
*************************************************/
u16 Zeroservo[16]= { 0, 12, 150, 39, 100, 155, 130,63, 0, 0, 0, 0, 0, 0, 0, 135};      

u16   Servotemp[16];
u16   NowAngle[16];



void ControlAServo(u8 number,u16 Angel)
{	
	NowAngle[number-1] = calculate_PWM(Angel);
	switch(number){
		case 1:
			number = 0;
			break;
		case 2:
			number = 1;
			break;
		case 3:
			number = 2;
			break;
		case 4:
			number = 3;
			break;
		case 5:
			number = 4;
			break;
		case 6:
			number = 5;
			break;
		case 7:
			number = 6;
			break;
		case 8:
			number = 7;
			break;
		case 9:
			number = 8;
			break;
		case 10:
			number = 9;
			break;
		case 11:
			number = 10;
			break;
		case 12:
			number = 11;
			break;
		case 13:
			number = 12;
			break;
		case 14:
			number = 13;
			break;
		case 15:
			number = 14;
			break;
		case 16:
			number = 15;
			break;
		default:
			return;


	}
	setPWM(number,0,calculate_PWM(Angel));
}				

void segmentation(u16 * a,u16* b,u16 tim,u8 xf)
{

	u16 k[16],m;
	u8 i,s;

	for(s=0;s<=xf;s++)
	{
		for(i=0;i<16;i++)
		{
				if(a[i]>b[i])
				{
					k[i]=a[i]-b[i];
				}
				else
					k[i]=b[i]-a[i];
//			k[i]=abs(a[i]-b[i]);

		}
		for(i=0;i<16;i++)
		{
			if(a[i]>b[i])
				{
					m=a[i]-k[i]*s/xf;
				}
			else
					m=a[i]+k[i]*s/xf;
			ControlAServo(i+1,m);
			//	printf("%d  ",m);
		}
		//printf("\n");
		delay_ms(tim);
	}

}

void   SlowAngle(s16 *begin,s16 *end,u16 tim,u8 xf)
{
	u16 a[16];
	u16 b[16];
	u8 i;
	
	
	for(i=0;i<16;i++)	//计算相对角度
	{
		a[i] = Zeroservo[i] +begin[i];
		b[i] = Zeroservo[i] +end[i];
	}
	segmentation(a,b,tim,xf);
	
}

