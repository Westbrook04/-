#include "myiic.h"
#include "delay.h"

void IIC_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOCʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	
    IIC_SCL=1;//�Ƚ�IIC_SCL��IIC_SDA����
    IIC_SDA=1;
}

void IIC_Start(void)
{
    SDA_OUT();     	//SDAģʽ����Ϊ���
    IIC_SDA=1;			//�ٽ�SDA��SCL���Ϊ1ʹI2CΪ����״̬
    IIC_SCL=1;      //�ٽ�SDA��SCL���Ϊ1ʹI2CΪ����״̬
    delay_us(4);		//ʹSDA��SCL����4us�ߵ�ƽ
	  IIC_SDA=0;			//��ʼ�ź�:��SCLΪ�ߵ�ƽʱ,SDA�ɸ�����͵�ƽ
    delay_us(4);    //��ʼ�ź��Ѿ����
    IIC_SCL=0;			//ǯסI2C���ߣ�׼�����ͻ��������
}

void IIC_Stop(void)
{
    SDA_OUT();      //SDAģʽ����Ϊ���
    IIC_SCL=0;      //����SCL
    IIC_SDA=0;      //����SDA
    delay_us(4);    //ʹSDA��SCL����4us�͵�ƽ
    IIC_SCL=1;      //����SCL
    IIC_SDA=1;      //ֹͣ�ź�:��SCLΪ�ߵ�ƽʱ,SDA�ɵ͵�ƽ����ߵ�ƽ
    delay_us(4);    //ʹSDA��SCL����4us�ߵ�ƽ
}

/**
  */
u8 IIC_Wait_Ack(void)
{
    u8 ucErrTime=0;
	
    SDA_IN();      						//SDA����Ϊ����
    IIC_SDA=1;
    delay_us(1);
    IIC_SCL=1;
    delay_us(1);							//�Ƚ�SDA��SCLȫ������

    while(READ_SDA) {					//while(READ_SDA)
        ucErrTime++;					//#define READ_SDA   PGin(5)  //����SDA
															//����ѭ����˵��READ_SDA == 1��Ҳ����PG5��������1
        if(ucErrTime>250) {		//��ʱһ��ʱ���
            IIC_Stop();				//ֹͣIIC����
            return 1;					//STM32��PG5���յ������壬��ʱΪ��Ӧ���ź�
        }
    }
    IIC_SCL=0;								//READ_SDA == 0��ʱ�����0
    return 0;									//STM32��PG5���յ������壬��ʱΪӦ���ź�
}

/*
TM32����ACKӦ��
STM32����ACKӦ��˵��STM32������8bit���ݡ���������IC����Ӧ���ź�
��ˣ���ʱSTM32��SDA����������Ϊ���ģʽ�����SDA���0�������ACKӦ��
*/
void IIC_Ack(void)
{
    IIC_SCL=0;
    SDA_OUT();
    IIC_SDA=0;
    delay_us(2);
    IIC_SCL=1;
    delay_us(2);
    IIC_SCL=0;
}

/**
  * @brief  STM32������ACKӦ��
  * @note   STM32����ACKӦ��˵��STM32������8bit���ݡ���������IC����Ӧ���ź�
						��ˣ���ʱSTM32��SDA����������Ϊ���ģʽ�����SDA���1���򲻲���ACKӦ��
  * @param  None
  * @date  	2021��3��27��
  * @retval None
  */
void IIC_NAck(void)
{
    IIC_SCL=0;
    SDA_OUT();
    IIC_SDA=1;
    delay_us(2);
    IIC_SCL=1;
    delay_us(2);
    IIC_SCL=0;
}

/**
  * @brief  IIC����һ���ֽ�
  * @note   �˺��������͵����ݽ��ж���������

�ڴ˾ٸ����ӣ����緢�͵��β�u8 txd = 0X40
��0X40ת�����ƣ�0100 0000
����&0X80�Ƕ�txd�����λ����λ�������������
(txd&0x80):0100 0000 & 1000 0000 = 0000 0000
�����ý������7λ�����������ǽ�һ��������λ�Ĳ�������ָ���ƶ���λ�������ƶ����Ƴ�λ������������Ƴ��Ŀ�λ����һ�ɲ�0
(txd&0x80)>>7:0000 000 0 = 0X00
����IIC_SDA = 0��
���������λʱ��txd����1λ
txd��0100 0000
txd<<1��1000 0000 
(txd&0x80):1000 0000 & 1000 0000 = 1000 0000
�����ý������7λ�����������ǽ�һ��������λ�Ĳ�������ָ���ƶ���λ�������ƶ����Ƴ�λ������������Ƴ��Ŀ�λ����һ�ɲ�0
(txd&0x80)>>7:0000 000 1 = 0X01
����IIC_SDA = 1��

���ѭ��8�Σ���8bit��txdȫ�����ͳ�ȥ
ע�⣡������������������������������������������������
��Щλ������STM32�зǳ����������������ѧϰ��һ��Ҫѧ����Щ���ݵ�λ����
*/
void IIC_Send_Byte(u8 txd)
{
    u8 t;
    SDA_OUT();
    IIC_SCL=0;              //����ʱ�ӿ�ʼ���ݴ���
    for(t=0; t<8; t++) 
	 {
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1;
        delay_us(2);   //��TEA5767��������ʱ���Ǳ����
        IIC_SCL=1;
        delay_us(2);
        IIC_SCL=0;
        delay_us(2);
    }
}
//��1���ֽ�
/*
STM32ͨ��IIC_Read_Byte()��ȡ�ⲿ�豸��һ���ֽ�
�����λ����Ͳ�����⣬�Լ��κ����
unsigned char ack        
ack=1ʱ������ACK��ͬʱ����һ��ACKӦ���źţ�ack=0������nACK��������ACKӦ���ź�                   
���ض�ȡ����1�ֽ�����
  */
u8 IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA����Ϊ����
    for(i=0; i<8; i++ ) 
	  {
        IIC_SCL=0;
        delay_us(2);
        IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;
        delay_us(1);
    }
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK
    return receive;
}


/************************ (C) COPYRIGHT JXUST@WangMingcong *****END OF FILE****/

