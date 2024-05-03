#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"

                                                   //IO��������
#define SDA_IN()  {GPIOC->MODER&=~(3<<(9*2));GPIOC->MODER|=0<<9*2;}	//PB10����ģʽ
#define SDA_OUT() {GPIOC->MODER&=~(3<<(9*2));GPIOC->MODER|=1<<9*2;} //PB10���ģʽ
                                               //IO��������
#define IIC_SCL    PAout(8) //SCL
#define IIC_SDA    PCout(9) //SDA
#define READ_SDA   PCin(9)  //����BSDA 
		
//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��
void IIC_Start(void);				        //����IIC��ʼ�ź�
void IIC_Stop(void);	  			      //����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			    //IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				      //IIC�ȴ�ACK�ź�
void IIC_Ack(void);					        //IIC����ACK�ź�
void IIC_NAck(void);				        //IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);


#endif
/************************ (C) COPYRIGHT JXUST@WangMingcong *****END OF FILE****/
