#ifndef __USRATX_H
#define __USRATX_H 

#include "stdio.h"
#include "sys.h"
#include "system.h"

#define DATA_STK_SIZE   512 
#define DATA_TASK_PRIO  4

#define FRAME_HEADER_CAR 0X7B //���Ƶ����˶�������֡ͷ
#define FRAME_TAIL_CAR 0X7D //���Ƶ����˶�������֡β
#define FRAME_HEADER_MOVEIT 0XAA //���ƻ�е���˶�������֡ͷ
#define FRAME_TAIL_MOVEIT 0XBB //���ƻ�е���˶�������֡ͷ
#define SEND_DATA_SIZE    24
#define RECEIVE_DATA_SIZE 11

#define follower 2
#define default_mode 1

#define Infrared1 PAin(2)  //
#define Infrared2 PAin(3)  //
#define Infrared3 PAin(6)  //
#define Infrared4 PAin(7)  //
#define BEEP PGout(11)	// ����������IO λ��������

#define L_front         PFin(8)            //DIO4  
#define R_front         PDin(7)            //DIO2  

#define L_Centre        PFin(7)            //DIO3
#define R_Centre        PDin(2)            //ETR3

#define L_back          PEin(0)            //ETR1
#define R_back          PAin(5)            //ETR2 


   
/*********ǰ����һ·�Ҷ�*********/
#define F5 PBin(8)  //GDIO14
#define F6 PBin(9)  //GDIO15
#define F7 PEin(1)  //GPIO16
#define F8 PEin(2)  //GPIO1
#define F1 PBin(7)  //GPIO13
#define F2 PBin(6)  //GPIO12
#define F3 PBin(5)  //GPIO11
#define F4 PBin(4)  //GPIO10

/**********������һ·�Ҷ�********/
//Ϊ�����P9
#define D5 PEin(5)  //GPIO2
#define D6 PEin(6)  //GPIO3
#define D7 PFin(0)  //GPIO4
#define D8 PFin(1)  //GPIO5
#define D4 PFin(2)  //GPIO6
#define D3 PFin(4)  //GPIO7
#define D2 PFin(5)  //GPIO8
#define D1 PFin(6)  //GPIO9


/*****A structure for storing triaxial data of a gyroscope accelerometer*****/
/*****���ڴ�������Ǽ��ٶȼ��������ݵĽṹ��*********************************/
typedef struct __Mpu6050_Data_ 
{
	short X_data; //2 bytes //2���ֽ�
	short Y_data; //2 bytes //2���ֽ�
	short Z_data; //2 bytes //2���ֽ�
}Mpu6050_Data;

/*******The structure of the serial port sending data************/
/*******���ڷ������ݵĽṹ��*************************************/
typedef struct _SEND_DATA_  
{
	unsigned char buffer[SEND_DATA_SIZE];
	struct _Sensor_Str_
	{
		unsigned char Frame_Header; //1���ֽ�
		short X_speed;	            //2 bytes //2���ֽ�
		short Y_speed;              //2 bytes //2���ֽ�
		short Z_speed;              //2 bytes //2���ֽ�
		short Power_Voltage;        //2 bytes //2���ֽ�
		Mpu6050_Data Accelerometer; //6 bytes //6���ֽ�
		Mpu6050_Data Gyroscope;     //6 bytes //6���ֽ�	
		unsigned char Frame_Tail;   //1 bytes //1���ֽ�
	}Sensor_Str;
}SEND_DATA;

typedef struct _RECEIVE_DATA_  
{
	unsigned char buffer[RECEIVE_DATA_SIZE];
	struct _Control_Str_
	{
		unsigned char Frame_Header; //1 bytes //1���ֽ�
		float X_speed;	            //4 bytes //4���ֽ�
		float Y_speed;              //4 bytes //4���ֽ�
		float Z_speed;              //4 bytes //4���ֽ�
		unsigned char Frame_Tail;   //1 bytes //1���ֽ�
	}Control_Str;
}RECEIVE_DATA;


void data_task(void *pvParameters);
void data_transition(void);
void USART1_SEND(void);
void USART3_SEND(void);
void USART5_SEND(void);

void CAN_SEND(void);
void uart1_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);
void uart5_init(u32 bound);

void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
int UART5_IRQHandler(void);

float Vz_to_Akm_Angle(float Vx, float Vz);
float XYZ_Target_Speed_transition(u8 High,u8 Low);
void usart1_send(u8 data);
void usart2_send(u8 data);
void usart3_send(u8 data);
void usart5_send(u8 data);

u8 Check_Sum(unsigned char Count_Number,unsigned char Mode);

void DMA_forUsart3IDLE_Init(void);
void dinwei(void);

void lay(void);
void code_data_deal(u8 data);
void Car_TurnAngle(s16 angle);
void Car_TurnToAngle(s32 goal_Angle);
void _6zhou_calibration(void);
void saoma(void);
void zhua2(void);
void zhua1(void);
void zhuan_pang(void);

void BEEP_Init(void);//��ʼ��	
void Infrared_sensor_Init(void);//�����ʼ��

//void Eight_Gray_Init(void);
//void OneGray_init(void);
//void Gray_Init(void);
//��������
//void RL_Centre_Count(void (*d)(void),int ti);  //����   ��   һ·
//void RL_Back_Count(void (*d)(void),int ti);    //����   ��   һ·
//void RL_Front_Count(void (*d)(void),int ti);    //����ǰ

//void R_Front_Count(void (*d)(void),int ti);     //��ǰ  
//void L_Front_Count(void (*d)(void),int ti);     //��ǰ


//void R_Centre_Count(void (*d)(void),int ti);   //��     ��   һ·
//void R_Back_Count(void (*d)(void),int ti);     //��     ��   һ·

//void L_Centre_Count(void (*d)(void),int ti);   //����
//void L_Back_Count(void (*d)(void),int ti);    //���
void GY53_Init (void);
uint32_t GetGYTimer(void);
float Hcsr04GetLength(void);
float Hcsr04GetLength1(void);
float Hcsr04GetLength2(void);
float Hcsr04GetLength3(void);
void TIM7_IRQHandler(void);
void TIM7_Int_Init(u16 arr,u16 psc);
void TIM6_Int_Init(void);
void TIM6_IRQHandler(void);


//ǰ��Ѳ��
void run28_6lu(void);
void New_run35(void);
void New_run351(void);
void run28(void);
void run28_(void);
void run28_1(void);
void run35(void);
void run45(void);
void run45one(void);
void run356lu(void);
void run65(void);
void Dispel_left_run35(void);
void Dispel_left_run60(void);
void Dispel_right_run35(void);
void run28_4(void);
//����Ѳ��
void New_anti_run35(void);
void New_anti_run35b(void);
void anti_run45(void);
void anti_run35(void);
void anti_run28(void);
void anti_run286lu(void);
void anti_run28_8lu(void);
void anti_run24(void);
void Dispel_rightanti_run35(void);
void Dispel_leftanti_run35(void);

void g_run28(void);
void g_run35(void);
void g_anti_run286lu(void);
void g_run45(void);
void g_run26(void);
void g_run23(void);
void white_g_run23(void);
void white_g_run26(void);
void wg_anti_run286lu(void);
void zuo_g_run26(void);
void zuo_g_anti_run24(void);



#endif

