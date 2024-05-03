#ifndef __GRAY_H
#define __GRAY_H

#include "sys.h"

/********�ǻҶȵ���,��⵽��ɫ  1�ǻҶȵư�,��⵽��ɫ*********/

//һ·�Ҷ�
//#define L_front         PEin(0)            //ETR1  (��ǰ)һ·�Ҷ�
//#define R_front         PFin(8)            //DIO4  (��ǰ)һ·�Ҷ�   

//#define L_Centre        PAin(5)            //ETR2  (����)һ·�Ҷ�
//#define R_Centre        PCin(7)            //PWM7  (����)һ·�Ҷ�      
//#define R_back          PDin(7)            //DIO2  �Һ�һ·�Ҷ�
//#define L_back          PDin(2)            //ETR3  ���һ·�Ҷ�

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

/*******�Ҷȳ�ʼ��*******/
void Eight_Gray_Init(void);
void OneGray_init(void);
void Gray_Init(void);
//��������
void RL_Centre_Count(void (*d)(void),int ti);  //����   ��   һ·
void RL_Back_Count(void (*d)(void),int ti);    //����   ��   һ·
void RL_Front_Count(void (*d)(void),int ti);    //����ǰ

void R_Front_Count(void (*d)(void),int ti);     //��ǰ  
void L_Front_Count(void (*d)(void),int ti);     //��ǰ

void R_Centre_Count(void (*d)(void),int ti);   //��     ��   һ·
void R_Back_Count(void (*d)(void),int ti);     //��     ��   һ·

void L_Centre_Count(void (*d)(void),int ti);   //����
void L_Back_Count(void (*d)(void),int ti);    //���
/********�Ҷ�Ѳ��*********/
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

//������ʻ
void RightRetreat_flexuous(void); 
void LeftRetreat_flexuous(void);

//PIDѲ��
//void Pid_run(u8 speed);
//void Pid_run35(void);
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
void Camera_Speed1(void);
#endif
