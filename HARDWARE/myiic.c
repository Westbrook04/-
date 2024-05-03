#include "myiic.h"
#include "delay.h"

void IIC_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化

	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	
    IIC_SCL=1;//先将IIC_SCL和IIC_SDA拉高
    IIC_SDA=1;
}

void IIC_Start(void)
{
    SDA_OUT();     	//SDA模式设置为输出
    IIC_SDA=1;			//再将SDA和SCL输出为1使I2C为空闲状态
    IIC_SCL=1;      //再将SDA和SCL输出为1使I2C为空闲状态
    delay_us(4);		//使SDA和SCL保持4us高电平
	  IIC_SDA=0;			//开始信号:当SCL为高电平时,SDA由高跳向低电平
    delay_us(4);    //起始信号已经完成
    IIC_SCL=0;			//钳住I2C总线，准备发送或接收数据
}

void IIC_Stop(void)
{
    SDA_OUT();      //SDA模式设置为输出
    IIC_SCL=0;      //拉低SCL
    IIC_SDA=0;      //拉低SDA
    delay_us(4);    //使SDA和SCL保持4us低电平
    IIC_SCL=1;      //拉高SCL
    IIC_SDA=1;      //停止信号:当SCL为高电平时,SDA由低电平跳箱高电平
    delay_us(4);    //使SDA和SCL保持4us高电平
}

/**
  */
u8 IIC_Wait_Ack(void)
{
    u8 ucErrTime=0;
	
    SDA_IN();      						//SDA设置为输入
    IIC_SDA=1;
    delay_us(1);
    IIC_SCL=1;
    delay_us(1);							//先将SDA、SCL全部拉高

    while(READ_SDA) {					//while(READ_SDA)
        ucErrTime++;					//#define READ_SDA   PGin(5)  //输入SDA
															//进入循环，说明READ_SDA == 1；也就是PG5引脚输入1
        if(ucErrTime>250) {		//延时一段时间后
            IIC_Stop();				//停止IIC总线
            return 1;					//STM32的PG5接收到高脉冲，此时为非应答信号
        }
    }
    IIC_SCL=0;								//READ_SDA == 0；时钟输出0
    return 0;									//STM32的PG5接收到低脉冲，此时为应答信号
}

/*
TM32产生ACK应答
STM32产生ACK应答，说明STM32接收完8bit数据。向发送数据IC发送应答信号
因此，此时STM32的SDA引脚需设置为输出模式，如果SDA输出0，则产生ACK应答
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
  * @brief  STM32不产生ACK应答
  * @note   STM32产生ACK应答，说明STM32接收完8bit数据。向发送数据IC发送应答信号
						因此，此时STM32的SDA引脚需设置为输出模式，如果SDA输出1，则不产生ACK应答
  * @param  None
  * @date  	2021年3月27日
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
  * @brief  IIC发送一个字节
  * @note   此函数将发送的数据进行二进制运算

在此举个例子：例如发送的形参u8 txd = 0X40
将0X40转二进制：0100 0000
这里&0X80是对txd的最高位进行位操作（与操作）
(txd&0x80):0100 0000 & 1000 0000 = 0000 0000
将所得结果右移7位；右移运算是将一个二进制位的操作数按指定移动的位数向右移动，移出位被丢弃，左边移出的空位或者一律补0
(txd&0x80)>>7:0000 000 0 = 0X00
所以IIC_SDA = 0；
发送完最高位时：txd左移1位
txd：0100 0000
txd<<1：1000 0000 
(txd&0x80):1000 0000 & 1000 0000 = 1000 0000
将所得结果右移7位；右移运算是将一个二进制位的操作数按指定移动的位数向右移动，移出位被丢弃，左边移出的空位或者一律补0
(txd&0x80)>>7:0000 000 1 = 0X01
所以IIC_SDA = 1；

最后循环8次，将8bit的txd全部发送出去
注意！！！！！！！！！！！！！！！！！！！！！！！！！
这些位操作在STM32中非常常见，如果想深入学习。一定要学会这些数据的位运算
*/
void IIC_Send_Byte(u8 txd)
{
    u8 t;
    SDA_OUT();
    IIC_SCL=0;              //拉低时钟开始数据传输
    for(t=0; t<8; t++) 
	 {
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1;
        delay_us(2);   //对TEA5767这三个延时都是必须的
        IIC_SCL=1;
        delay_us(2);
        IIC_SCL=0;
        delay_us(2);
    }
}
//读1个字节
/*
STM32通过IIC_Read_Byte()读取外部设备的一个字节
这里的位运算就不做详解，自己课后计算
unsigned char ack        
ack=1时，发送ACK，同时产生一个ACK应答信号；ack=0，发送nACK，不产生ACK应答信号                   
返回读取到的1字节数据
  */
u8 IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA设置为输入
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
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK
    return receive;
}


/************************ (C) COPYRIGHT JXUST@WangMingcong *****END OF FILE****/

