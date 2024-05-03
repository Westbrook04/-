#include "action.h"
#include "PCA9685.h"
#include "delay.h"
#include "time_go.h"
#include "gray.h"
#include "final_task.h"
#include "usartx.h"
#include "drive_motor.h"
/*从车左侧看hone区左侧
**********************************
舵机      转动方向        对应角度(pwm)
			(从左侧看)
				
0号舵机   逆时针    旋转   变大  （从上往下看）
1号舵机   逆时针    旋转   变大   (从左侧看)
2号舵机   逆时针    旋转   变大   (从左侧看)
3号舵机   逆时针    旋转   变大   (从左侧看)
7号舵机   逆时针    旋转   变大   （从上往下看）
9号舵机   顺时针    旋转   变大   （从上往下看）
10号舵机  顺时针    旋转   变大   （从上往下看）

7号舵机   0   绿色 
          38  红色
          82  蓝色
		  127 白色
		  170 黑色
9号舵机   100抓物块  50归位 左
10号舵机  80抓物块  130归位 右

4号pwm口  气泵     大于90吸气
5号pwm口  电子开关
**********************************/
//10.8v  7月14号
/********机械臂初始化********/
extern u8 green;
extern u8 red;
extern u8 blue;
 extern u8 black;
 extern u8 white;
//  extern u8 colour_type;
// u8 color_sort[2]={0,0};
// extern u8 color_sort1[2]={0,0};
// extern u8 color_sort[5];
  void Initial_action()
{
	
	setPWM(2,0,calculate_PWM(150));  //左40
	delay_ms(500);
	
	
	 setPWM(1,0,calculate_PWM(12));//右115
	delay_ms(500);	


	
	setPWM(3,0,calculate_PWM(39));//往大调向内测
	delay_ms(500);
	
	
		setPWM(5,0,calculate_PWM(155));//往小向上
	delay_ms(500);
	 	setPWM(6,0,calculate_PWM(130));// 往小调向内侧                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
	delay_ms(500);	
		setPWM(4,0,calculate_PWM(100));//往大调向内测
	delay_ms(500); 
	
	

	  
	
	setPWM(7,0,calculate_PWM(63));// 往大调向内侧                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
	delay_ms(500);
	
	
	
	
//	setPWM(8,0,calculate_PWM(100));  //往小调向内膊侧
//	delay_ms(50);
//		setPWM(8,0,calculate_PWM(90));//往小调向内测
//	delay_ms(500);
//	setPWM(12,0,calculate_PWM(80));//往大调向外测98
//	delay_ms(500);
//	setPWM(13,0,calculate_PWM(50));//往大是向下
//	delay_ms(500);
//	setPWM(14,0,calculate_PWM(120));//
//	delay_ms(500);

    setPWM(15,0,calculate_PWM(135));
	
}

void catch_front()
{
	crazyMe(3,130,100,5,80);
	crazyMe(2,170,110,5,80);
	crazyMe(1,100,162,5,120);
	
	setPWM(4,0,calculate_PWM(150));//吸气
	delay_ms(1000);
//	setPWM(4,0,calculate_PWM(0));
//	delay_ms(1000);
	
	 setPWM(1,0,calculate_PWM(100));
	delay_ms(500);	

	setPWM(2,0,calculate_PWM(155));
	delay_ms(500);
	
	setPWM(3,0,calculate_PWM(130));
	delay_ms(500);
	
	//调整放在转盘的位置
	setPWM(6,0,calculate_PWM(149));
	delay_ms(1000);	
	crazyMe(2,170,95,5,150);
	crazyMe(1,100,123,5,130);
	crazyMe(3,130,175,5,130);
	
	setPWM(4,0,calculate_PWM(0));
	delay_ms(300);
	setPWM(5,0,calculate_PWM(130));
	delay_ms(300);
	Initial_action();
	
}

void Clasp_block()
{
//	crazyMe(1,12,114,3,80);//51
//    crazyMe(2,150,50,3,80);
	               //0  1  2  3  4  5  6  7  8   9  10  11 12  13  14  15  
	s16 pose0[16]={  0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0, 0,  0,  0,  0,  0  };
	s16 pose1[16]={  0, 102, -100, 0, 0, 0, 0, 0, 0,  0,  0, 0,  0,  0,  0,  0  };
//	s16 pose2[16]={  0,51,-33,0,0,32,0,0,106,107,0,0, 0, 0, 0, 0  };


	SlowAngle(pose0,pose1,20,15);
//	delay_ms(100);
//	SlowAngle(pose1,pose2,35,20);
//	delay_ms(400);
//	SlowAngle(pose2,pose3,35,20);
//	delay_ms(100);
	
}

void Relesae_block()
{

	crazyMe(1,114,12,3,60);//51
    crazyMe(2,50,150,3,60);







	
//	setPWM(2,0,calculate_PWM(41));
//	delay_ms(300);
//	
//setPWM(1,0,calculate_PWM(115));
//	delay_ms(300);

	
    
//	crazyMe(10,113,40,5,80);
//	crazyMe(9,37,110,5,80);
}

//物块右偏纠正

void CorrectYou_block()	
{    
	crazyMe(1,115,61,3,60);//51
	
	crazyMe(1,61,115,3,60);//51
	
	
	
//	 crazyMe(9,70,90,4,100);
//	delay_ms(70);
//   crazyMe(10,100,64,4,80);
}
void CorrectWhite_block()
{
	    crazyMe(9,70,105,5,150);
			delay_ms(100);
	crazyMe(10,80,57,5,120);
}
//绿色物块纠正
void CorrectGreen_block()
{
	crazyMe(10,80,57,5,120);
	delay_ms(70);
    crazyMe(9,70,105,5,150);
}
//物块左偏纠正
void CorrectZuo_block()
{
	crazyMe(2,40,103,5,150);
	delay_ms(100);
    crazyMe(2,103,40,5,50);
}
void CorrectZuo_block_b()
{
	crazyMe(2,40,108,5,150);
	delay_ms(100);
    crazyMe(2,108,40,5,50);
}
/********爪子准备下去抓的动作，并下去打开爪子********/
void Ready_Catch()
{
//   	crazyMe(4,67,24,10,100);
//	crazyMe(3,100,90,5,120); //3号上台一点防止打到摄像头
//	crazyMe(8,53,107,10,85); // 爪子下去到地面距离*****************调145下面也调
	//...................
	crazyMe(2,120,80,6,120);
	crazyMe(3,130,100,6,120);
	
	crazyMe(1,88,35,6,120);//至此机械臂伸到物块处
	
}

/********吸起小物块（此时物块在车中间）********/
void Pick_Up()
{
	//上个动作是Ready_Catch();
/********节省时间******/
	//机械臂从初始位置抓取正前方物块
	delay_ms(30);
	
	crazyMe(5,155,150,5,100);//120-128
	crazyMe(6,130,75,5,100);//130-75
	
	crazyMe(4,100,46,4,100);//至此机械臂伸到物块处88-45
	
	SET_Motor(26,26,26,26);//Set_Motor(26,26);
    delay_ms(180);
	SET_Motor(0,0,0,0);//Set_Motor(0,0);
	
	crazyMe(7,63,90,4,100);//爪子闭合106-135
	
//	setPWM(4,0,calculate_PWM(150));//吸气
//	delay_ms(1000);

//	 setPWM(1,0,calculate_PWM(106));
//	delay_ms(500);	

//	setPWM(2,0,calculate_PWM(84));
//	delay_ms(500);
//	
//	setPWM(3,0,calculate_PWM(152));
//	delay_ms(500);

	setPWM(5,0,calculate_PWM(155));
	delay_ms(500);

     	crazyMe(4,44,100,4,100);
	delay_ms(500);	

	setPWM(6,0,calculate_PWM(130));
	delay_ms(500);
	
	
	
}
/********将物块放入转盘********/
void Place_Block1()
{  


//	delay_ms(500);
//	delay_ms(30);
//	crazyMe(2,130,80,5,150);
//	
//	crazyMe(3,130,170,5,130);
//	setPWM(0,0,calculate_PWM(120));


	crazyMe(6,130,168,6,120);//20kg舵机是41到148,40到137
	delay_ms(300);	
 	crazyMe(5,155,157,6,120);
	
	crazyMe(4,100,123,4,100);
	
	crazyMe(3,39,145,4,150);
	
//	crazyMe(4,112,123,4,100);
//	
//	crazyMe(5,130,157,4,100);
//	
//	crazyMe(6,150,173,6,120);
	
	crazyMe(4,123,117,4,100);
	
	crazyMe(7,90,80,4,100);
	
	crazyMe(4,117,115,4,100);
	
	crazyMe(7,80,63,4,80);
	////归正
	crazyMe(4,115,123,4,100);
	
	crazyMe(6,168,130,6,120);
	
	crazyMe(3,145,39,4,150);
	
	crazyMe(5,157,155,4,80);
	
	crazyMe(4,123,100,4,80);
	
	delay_ms(200);
	
	setPWM(15,0,calculate_PWM(90));

//	delay_ms(500);
//	Initial_action();
}

void Place_Block()
{  	delay_ms(600);
	setPWM(1,0,calculate_PWM(60));
	delay_ms(600);	
	setPWM(2,0,calculate_PWM(84));
	delay_ms(600);
	
	setPWM(3,0,calculate_PWM(152));
	delay_ms(600);	
		 setPWM(1,0,calculate_PWM(106));
	


	delay_ms(500);
	delay_ms(30);
//	crazyMe(2,130,80,5,150);
//	
//	crazyMe(3,130,170,5,130);
//	setPWM(0,0,calculate_PWM(120));
	crazyMe(6,41,149,6,120);//20kg舵机是41到148,40到137
	delay_ms(1000);	

	crazyMe(1,106,99,5,100);
//	crazyMe(1,100,99,5,130);	
	delay_ms(200);
	crazyMe(2,84,116,5,100);

	crazyMe(1,99,92,5,100);
	
//	setPWM(4,0,calculate_PWM(0));
	

	crazyMe(12,135,126,4,100);
	delay_ms(200);
	crazyMe(1,92,106,5,100);
//	setPWM(5,0,calculate_PWM(130));
	delay_ms(300);
	crazyMe(3,152,138,5,100);
	delay_ms(500);
	Initial_action();
}


//取物块动作
//void Take_Block()
//{

//    crazyMe(3,55,60,5,100);      //爪子抬起防止绕线
//    crazyMe(1,128,15,10,80);     //云台向后转
// 
//    crazyMe(4,95,143,5,100);     //机械臂向下  
//	crazyMe(8,30,55,10,90);	     //8号带动机械臂整体向前伸一小段****
//	                             //*第一次*向前过多再抬起来时，可能会卡到舵盘*****71调
//	
//	crazyMe(5,1,22,5,120);     //爪子闭合一点
//	
//	crazyMe(8,55,58,10,80);      //2号*第二次*（有可能怼到转盘）带动机械臂整体再向前一小段 
//		                         //**********78调
//	
//	crazyMe(4,143,132,5,120);    //4号控制爪子抬起来一点************这个调下面也要调
//	
//	crazyMe(8,58,61,10,80);      //2号*第三次*（最有可能怼到转盘）带动机械臂整体再向前一小段 
//	
//	crazyMe(5,22,32,5,120);    //爪子完全闭合
//    crazyMe(8,61,45,10,85);      //机械臂抬起，抓走物块
//    crazyMe(1,15,128,10,80);
//}
//以上为源码

void Take_Block()
{
	
			crazyMe(6,130,168,6,120);//20kg舵机是41到148,40到137
	delay_ms(300);	
 	crazyMe(5,155,157,6,120);
	
	crazyMe(4,100,123,4,100);
	
	crazyMe(3,39,145,4,150);
	

	
//		crazyMe(6,130,150,6,120);//20kg舵机是41到148,40到137
//	delay_ms(300);	
// 	crazyMe(5,155,130,6,120);
//	
//	crazyMe(4,100,112,4,100);
//	
//	crazyMe(3,39,145,4,150);
	
//	crazyMe(4,112,123,4,100);
//	
//	crazyMe(5,130,157,4,100);
//	
//	crazyMe(6,150,173,6,120);
	
	crazyMe(7,65,78,4,100);
	
	crazyMe(4,123,117,4,100);
	
	crazyMe(4,117,102,4,100);
	
	crazyMe(6,168,165,6,120);
	
	crazyMe(7,78,91,4,100);
	
	crazyMe(4,102,119,4,100);
	
	crazyMe(6,170,150,6,120);
	
	crazyMe(3,145,39,4,150);
	
	delay_ms(500);
	
	setPWM(5,0,calculate_PWM(155));
	delay_ms(500);
    setPWM(4,0,calculate_PWM(100));
	delay_ms(500);	

	setPWM(6,0,calculate_PWM(130));
	delay_ms(500);
	
	
	
	
	
	
//	crazyMe(7,70,80,4,100);
//	
//	crazyMe(6,130,150,6,120);//20kg舵机是41到148,40到137
//	delay_ms(300);	
// 	crazyMe(5,155,130,6,120);
//	
//	crazyMe(4,100,112,4,100);
//	
//	crazyMe(3,35,136,4,150);
//	
//	crazyMe(4,112,117,4,100);
//	
//	crazyMe(5,130,142,4,100);
//	
//	crazyMe(6,150,162,6,120);
//	
//	crazyMe(4,117,99,4,100);
//	
////	crazyMe(6,150,148,6,120);
//	delay_ms(300);
//	
//	crazyMe(7,80,90,4,100);
//	
//	crazyMe(4,99,119,4,100);
//	
//	crazyMe(6,162,150,6,120);
//	
//	crazyMe(3,138,35,4,200);
//	
//		 setPWM(4,0,calculate_PWM(100));
//	delay_ms(500);	

//	setPWM(6,0,calculate_PWM(130));
//	delay_ms(500);
//	
//	setPWM(5,0,calculate_PWM(155));
//	delay_ms(500);
	
//	//爪子先闭合一点点防止撞到相邻的五块
//    crazyMe(1,88,117,4,100);//往后拉一点点
//	crazyMe(2,125,89,5,100); //往上抬
//   
//    crazyMe(6,40,149,6,100);     //云台向后转
// delay_ms(30);
//	crazyMe(3,95,130,5,100);// 机械臂往下
//	crazyMe(2,89,110,5,100); 
//	
//	crazyMe(3,130,172,5,100);// 机械臂往下
//	
//	 crazyMe(1,117,90,5,100);//往前面挺一点
//	crazyMe(12,106,126,4,100);
//	crazyMe(2,110,113,5,100);
// 	crazyMe(3,172,158,5,100);
//	crazyMe(12,126,135,4,100);//爪子闭合
//	crazyMe(1,90,123,5,100);//机械臂抬起
//	crazyMe(6,149,41,6,120);     //云台向后转
	
	
	
//    crazyMe(4,95,143,5,100);     //机械臂向下  
//	crazyMe(8,30,55,10,90);	     //8号带动机械臂整体向前伸一小段****
//	                             //*第一次*向前过多再抬起来时，可能会卡到舵盘*****71调
//	
//	crazyMe(5,1,22,5,120);     //爪子闭合一点
//	
//	crazyMe(8,55,58,10,80);      //2号*第二次*（有可能怼到转盘）带动机械臂整体再向前一小段 
//		                         //**********78调
//	
//	crazyMe(4,143,132,5,120);    //4号控制爪子抬起来一点************这个调下面也要调
//	
//	crazyMe(8,58,61,10,80);      //2号*第三次*（最有可能怼到转盘）带动机械臂整体再向前一小段 
//	
//	crazyMe(5,22,32,5,120);    //爪子完全闭合
//    crazyMe(8,61,45,10,85);      //机械臂抬起，抓走物块
//    crazyMe(1,15,128,10,80);









}
//放置物块并抬起动作
void Take_Block4()//舵机够不到那个角度，得单独写一个
{
	
	
	crazyMe(6,130,173,6,120);//20kg舵机是41到148,40到137
	delay_ms(300);	
 	crazyMe(5,155,157,6,120);
	
	crazyMe(4,100,123,4,100);
	
	crazyMe(3,39,145,4,150);
	
	
	crazyMe(7,65,77,4,100);
	
	crazyMe(4,123,117,4,100);
	
	crazyMe(4,117,100,4,140);
	
	crazyMe(7,77,90,4,100);
	
	crazyMe(4,100,128,4,100);
	
	crazyMe(6,173,150,6,120);
	
	crazyMe(3,145,39,4,150);
	
	delay_ms(500);
	
	setPWM(5,0,calculate_PWM(155));
	delay_ms(500);
    setPWM(4,0,calculate_PWM(100));
	delay_ms(500);	

	setPWM(6,0,calculate_PWM(130));
	delay_ms(500);
	

}
void Take_Block5()//舵机够不到那个角度，得单独写一个
{
	
	
	crazyMe(6,130,173,6,120);//20kg舵机是41到148,40到137
	delay_ms(300);	
 	crazyMe(5,155,157,6,120);
	
	crazyMe(4,100,123,4,100);
	
	crazyMe(3,39,147,4,150);
	
	
	crazyMe(7,65,75,4,100);
	
	crazyMe(4,123,117,4,100);
	
	crazyMe(4,117,100,4,100);
	
	crazyMe(7,75,90,4,100);
	
	crazyMe(4,100,119,4,100);
	
	crazyMe(6,173,150,6,120);
	
	crazyMe(3,147,39,4,150);
	
	delay_ms(500);
	
	setPWM(5,0,calculate_PWM(155));
	delay_ms(500);
    setPWM(4,0,calculate_PWM(100));
	delay_ms(500);	

	setPWM(6,0,calculate_PWM(130));
	delay_ms(500);
	

}









//放置物块并抬起动作
//void Ready_Lay_Block()
//{
//		crazyMe(4,132,50,10,80);//*************
//		crazyMe(3,60,70,10,80);

//		crazyMe(8,45,104,10,100);//爪子距离地面******147调 下面归位也调

//		//放置物块后抬起动作	
//		crazyMe(5,32,2,5,120);

//		crazyMe(4,50,57,10,80);//抬起一点防止起来时打到物块


//		//归位
//		crazyMe(8,104,30,10,100);//***********30
//		crazyMe(4,57,95,10,80);
//		crazyMe(3,70,55,10,80);
//	
//}
//以上为源码

void Ready_Lay_Block()
{
	
	crazyMe(5,155,150,5,100);//120-128
	crazyMe(6,130,75,5,100);//130-75
	
	crazyMe(4,100,46,4,150);//至此机械臂伸到物块处88-45
	
	crazyMe(7,90,65,4,100);
	
//	crazyMe(6,75,145,5,100);
	
//	Set_Motor(-23,-23);
//			delay_ms(100);
//			Set_Motor(0,0);
		setPWM(5,0,calculate_PWM(155));
	delay_ms(500);
	
	delay_ms(300);
	
			 setPWM(4,0,calculate_PWM(100));
	delay_ms(500);	

	setPWM(6,0,calculate_PWM(130));
	delay_ms(500);
	

	//.............................
//	crazyMe(2,113,90,5,100);// 机械臂向上轻轻抬起
//	crazyMe(3,158,100,5,100);// 机械臂往上
//	crazyMe(1,123,41,5,150);//机械臂放下
//	crazyMe(12,135,106,5,100);//松开爪子
//	
//	crazyMe(3,100,130,5,100);//收爪防止碰到物块
//	delay_ms(100);
//	Initial_action();
//....................
//		crazyMe(4,132,50,10,80);//*************
//		crazyMe(3,60,70,10,80);

//		crazyMe(8,45,104,10,100);//爪子距离地面******147调 下面归位也调

//		//放置物块后抬起动作	
//		crazyMe(5,32,2,5,120);

//		crazyMe(4,50,57,10,80);//抬起一点防止起来时打到物块


//		//归位
//		crazyMe(8,104,30,10,100);//***********30
//		crazyMe(4,57,95,10,80);
//		crazyMe(3,70,55,10,80);
	
}


















/********任务二抓1准备动作（下去爪子打开）******** Place_Block()放物块到转盘基础上&******/

void ready_catch1()
{
	
	crazyMe(1,90,85,7,80);
  crazyMe(3,90,126,5,120);//转到a物块上方
	delay_ms(200);
	crazyMe(2,115,82,5,100);//放下爪子钩住
	delay_ms(100);
//	crazyMe(3,123,138,5,120);//转到摄像头面前
//	delay_ms(100);
//		Color_identify();
//	color_sort[1]=colour_type;
	 crazyMe(3,126,90,5,120);
	delay_ms(100);
	
	
	
	
  		crazyMe(6,90,62,5,100);
	delay_ms(100);
	crazyMe(5,65,99,5,100);
	delay_ms(100);
	
	crazyMe(6,62,40,5,100);
	delay_ms(100);
//	Color_identify();
//	color_sort[0]=colour_type;
//crazyMe(6,62,90,5,100);
//	delay_ms(100);
	

	
		

//.............
}

void ready_catch1_1()
{
	
//	crazyMe(1,90,85,7,80);
//	crazyMe(6,90,62,5,100);
//	delay_ms(100);
//	crazyMe(5,65,95,5,100);
//	delay_ms(100);
//crazyMe(6,62,90,5,100);
//	delay_ms(100);
 //	Color_identify();

   crazyMe(3,90,126,5,120);//转到a物块上方
	delay_ms(200);
	crazyMe(2,115,82,5,100);//放下爪子钩住
	delay_ms(100);
	crazyMe(3,126,135,5,120);//转到摄像头面前
	delay_ms(100);
//	Color_identify();
	 crazyMe(3,123,90,5,120);
	delay_ms(100);
	


//.............
}
void ready_catch1_2()
{
	
	crazyMe(1,90,85,7,80);
	crazyMe(6,90,62,5,100);
	delay_ms(100);
	crazyMe(5,65,100,5,100);
	delay_ms(100);
crazyMe(6,62,90,5,100);
	delay_ms(100);
 //	Color_identify();

//   crazyMe(3,90,123,5,120);//转到a物块上方
//	delay_ms(200);
//	crazyMe(2,115,87,5,100);//放下爪子钩住
//	delay_ms(100);
//	crazyMe(3,123,135,5,120);//转到摄像头面前
//	delay_ms(100);
////	Color_identify();
//	 crazyMe(3,123,90,5,120);
//	delay_ms(100);
//	


//.............
}



void ready_catch2()
{
	//抓住f点的ce物块
	crazyMe(1,90,85,7,80);

		crazyMe(6,90,68,5,90);
	delay_ms(100);
	crazyMe(5,65,97,5,90);
	delay_ms(100);
//	crazyMe(6,68,50,5,90);
//	color_sort[0]=colour_type;
//crazyMe(6,50,90,5,90);
	crazyMe(6,68,110,5,90);
	
	delay_ms(200);
    crazyMe(3,90,125,5,90);
	delay_ms(200);
	crazyMe(2,115,82,5,90);
	delay_ms(100);
	 crazyMe(3,125,138,5,90);
//		color_sort[1]=colour_type;
//	crazyMe(3,125,90,5,90);

//	crazyMe(5,90,70,5,120);
//	crazyMe(9,90,108,10,100);
	
//.............
}
void ready_catch3()
{
	//用来钩住c处的物块
	crazyMe(1,90,85,7,80);

    crazyMe(3,90,125,5,120);
	delay_ms(200);
	crazyMe(2,115,81,5,100);
	delay_ms(100);
	 crazyMe(3,125,90,5,120);
	delay_ms(200);
	

}

void ready_catch4()
{
	
	crazyMe(1,90,85,7,80);
    crazyMe(3,90,138,5,120);
	delay_ms(200);
	crazyMe(2,115,89,5,100);
	delay_ms(100);
	 crazyMe(3,138,90,5,120);
	delay_ms(200);
	

}
void tao_catch1()
{
	//套
//	delay_ms(300);
crazyMe(9,60,120,5,80);//张开套筒，
	delay_ms(300);
	crazyMe(1,90,135,7,80);//伸下去
				delay_ms(300);
				crazyMe(9,120,60,5,80);//闭合套筒
				 delay_ms(300);
				crazyMe(1,135,90,7,80);//抬起
	
//.............
}

void tao_catch2()
{
	//套
	
	delay_ms(300);
crazyMe(1,90,120,7,80);
	delay_ms(300);
	crazyMe(9,60,83,5,80);
				delay_ms(300);

crazyMe(1,120,135,7,80);
				crazyMe(9,83,60,5,80);
				 delay_ms(300);
				crazyMe(1,135,90,7,80);
	
//.............
}

void tao_lay1()
{
	
//	//用于放置夹了三个物块但是只放下两个物块
//	delay_ms(300);
//crazyMe(1,90,132,7,80);
//	delay_ms(300);
//	crazyMe(9,60,90,5,80);
//				delay_ms(300);

//crazyMe(1,132,120,7,80);
//	delay_ms(300);
//crazyMe(9,90,60,5,80);
//		delay_ms(300);
//	crazyMe(9,60,90,5,80);
//				delay_ms(300);
//crazyMe(1,120,90,7,80);
//	delay_ms(300);
//				crazyMe(9,90,60,5,80);
//				 delay_ms(300);
//	crazyMe(1,90,85,7,80);
////				crazyMe(1,135,90,7,80);
	
		delay_ms(300);
crazyMe(1,90,126,7,80);
	delay_ms(300);
	crazyMe(9,60,90,5,80);
				delay_ms(300);

crazyMe(1,126,120,7,80);
	delay_ms(300);
crazyMe(9,90,60,5,80);
		delay_ms(300);
	crazyMe(9,60,125,5,80);
				delay_ms(300);
crazyMe(1,120,90,7,80);
				crazyMe(9,90,60,5,80);
				 delay_ms(300);
//.............
}
void tao_lay2()
{
	//任务一放下
	delay_ms(300);
crazyMe(1,90,135,7,80);
	delay_ms(300);
	crazyMe(9,67,125,5,80);
				delay_ms(300);

crazyMe(1,135,90,7,80);
				crazyMe(9,125,67,5,80);
				 delay_ms(300);
//				crazyMe(1,135,90,7,80);
	
//.............
}

void tao_lay3()
{
	//用于放置夹了两个物块并且只放下两个物块，但是要叠起三个物块
	delay_ms(300);
crazyMe(1,90,126,7,80);
	delay_ms(300);
	crazyMe(9,60,90,5,80);
				delay_ms(300);

crazyMe(1,126,120,7,80);
	delay_ms(300);
crazyMe(9,90,60,5,80);
		delay_ms(300);
	crazyMe(9,60,125,5,80);
				delay_ms(300);
crazyMe(1,120,90,7,80);
//				crazyMe(9,90,60,5,80);
				 delay_ms(300);
	
//.............
}

void tao_lay4()
{
	
	//用于放置夹了两个个物块但是只放下1个物块
	delay_ms(300);
crazyMe(1,90,132,7,80);
	delay_ms(300);
	crazyMe(9,60,90,5,80);
				delay_ms(300);

crazyMe(1,132,120,7,80);
	delay_ms(300);
crazyMe(9,90,60,5,80);
		delay_ms(300);
	crazyMe(9,60,90,5,80);
				delay_ms(300);
crazyMe(1,120,90,7,80);
	delay_ms(300);
				crazyMe(9,90,60,5,80);
				 delay_ms(300);
	crazyMe(1,90,85,7,80);
//				crazyMe(1,135,90,7,80);
	
//.............
}


/********任务二抓4后，抬起爪子动作，在ready_catch4（）基础上******/



//void ready_catch4()
//{
//    crazyMe(3,100,43,5,120);
//	crazyMe(1,128,100,10,80);//包住4号物块*********调100
//	crazyMe(4,95,70,5,120);	
//	crazyMe(8,30,110,10,80);//爪子距离地面******151调  下面也调
//}



void ready_catch5()
{

	 crazyMe(3,100,43,5,120);
	crazyMe(1,145,120,5,120);//相对于抓4 抓五号物块，机械臂更往里摆*********110调
	crazyMe(4,95,70,5,120);
	
	crazyMe(8,70,112,10,120);//爪子距离地面******151调  下面也调

}




//动作
void close()//用于闭上套筒
{               //   0 1 2 3 4 5 6 7  8  9  10  11 12 13 14 15 
	s16 pose0[16]={  0,0,-33,0,0,32,0,0,61,62,  0, 0, 0, 0, 0, 0  };
	s16 pose1[16]={  0,0,-34,0,0,32,0,0,0,0, 0, 0, 0, 0, 0, 0   };
//	s16 pose2[16]={  0,51,-33,0,0,32,0,0,106,107,0,0, 0, 0, 0, 0  };
//  s16 pose3[16]={  0,0,0,0,0,0,0,0,106,107,0,0, 0, 0, 0, 0 };
//	s16 pose4[16]={  0,0,0,0,0,0,0,0,45,46,0, 0, 0, 0, 0, 0 };
//  s16 pose5[16]={  0,0,0,0,0,0,0,0,45,46,0,0,0,0,0,0  };
//	s16 pose6[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose7[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose8[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose9[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose10[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose11[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose12[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };

	SlowAngle(pose0,pose1,20,15);
	delay_ms(100);
//	SlowAngle(pose1,pose2,35,20);
//	delay_ms(400);
//	SlowAngle(pose2,pose3,35,20);
//	delay_ms(100);
//	
//	SlowAngle(pose3,pose4,35,20);
//	delay_ms(100);
//	SlowAngle(pose4,pose5,35,20);
//	SlowAngle(pose5,pose6,10,10);
//	SlowAngle(pose6,pose7,10,10);
//	SlowAngle(pose7,pose8,15,15);
//	SlowAngle(pose8,pose9,15,15);
//	SlowAngle(pose9,pose10,10,15);
//	SlowAngle(pose10,pose11,15,15);
//	SlowAngle(pose11,pose1,15,15);
//	
	
}
void zhixian2()//用于抓取一个物块（任务二第一轮f）
{               // 0 1 2 3 4 5 6 7  8  9  10  11 12 13 14 15 
	s16 pose0[16]={  0,0,-33,0,0,35,0,0,0,0,0, 0, 0, 0, 0, 0  };
	s16 pose1[16]={  0,0,-33,0,0,35,0,0,61,62,0,0,0,0,0,0  };//张开套筒
	s16 pose2[16]={  0,51,-33,0,0,35,0,0,61,62,0,0,0,0,0,0  };
  s16 pose3[16]={  0,51,-33,0,0,35,0,0,61,62,0,0,0,0,0,0  };//伸下去
	s16 pose4[16]={  0,51,-33,0,0,35,0,0,0,0,0,0,0,0,0,0  };
  s16 pose5[16]={  0,0,-33,0,0,35,12,0,0,0,0,0,0,0,0,0  };///抬起来
//	s16 pose6[16]={  0,0,-33,0,0,35,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose7[16]={  0,0,0,0,0,35,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose8[16]={  0,0,0,0,0,33,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose9[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose10[16]={ 0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose11[16]={ 0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose12[16]={ 0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };

	SlowAngle(pose0,pose1,25,15);
	SlowAngle(pose1,pose2,25,15);
	SlowAngle(pose2,pose3,25,15);
	delay_ms(300);
	
	SlowAngle(pose3,pose4,25,15);
	SlowAngle(pose4,pose5,25,15);
//	SlowAngle(pose5,pose6,10,10);
//	SlowAngle(pose6,pose7,10,10);
//	SlowAngle(pose7,pose8,15,15);
//	SlowAngle(pose8,pose9,15,15);
//	SlowAngle(pose9,pose10,10,15);
//	SlowAngle(pose10,pose11,15,15);
//	SlowAngle(pose11,pose1,15,15);
//	
	
}

void catch2()//用于抓两个及以上物块
{               // 0 1 2 3 4 5 6 7  8  9  10  11 12 13 14 15 
	s16 pose0[16]={  0,0,-33,0,0,35,0,0,0,0,0, 0, 0, 0, 0, 0  };
	s16 pose1[16]={  0,23,-33,0,0,35,0,0,0,0,0,0,0,0,0,0  };//浅伸下去
	s16 pose2[16]={  0,23,-33,0,0,35,0,0,25,26,0,0,0,0,0,0   };//套筒微张
  s16 pose3[16]={  0,23,-33,0,0,35,0,0,61,62,0,0,0,0,0,0  };//套筒张开
	s16 pose4[16]={  0,51,-33,0,0,35,0,0,61,62,0,0,0,0,0,0  };//伸下去
  s16 pose5[16]={  0,51,-33,0,0,35,0,0,0,0,0,0,0,0,0,0  };//套筒闭合
	s16 pose6[16]={  0,0,-33,0,0,35,0,0,0,0,0,0,0,0,0,0 };//抬起来
//  s16 pose7[16]={  0,0,-33,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose8[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose9[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose10[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose11[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose12[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };

	SlowAngle(pose0,pose1,25,15);
	delay_ms(150);
	SlowAngle(pose1,pose2,25,15);
	delay_ms(150);
	SlowAngle(pose2,pose3,25,15);
	delay_ms(150);
	
	SlowAngle(pose3,pose4,25,15);
	delay_ms(500);
	SlowAngle(pose4,pose5,25,15);
	delay_ms(150);
	SlowAngle(pose5,pose6,20,15);
//	SlowAngle(pose6,pose7,10,10);
//	SlowAngle(pose7,pose8,15,15);
//	SlowAngle(pose8,pose9,15,15);
//	SlowAngle(pose9,pose10,10,15);
//	SlowAngle(pose10,pose11,15,15);
//	SlowAngle(pose11,pose1,15,15);
//	
	
}

void release3()//用于放下三个物块
{               // 0 1 2 3 4 5 6 7  8  9  10  11 12 13 14 15 
	s16 pose0[16]={  0,0,-34,0,0,35,0,0,0,0,0, 0, 0, 0, 0, 0  };
	s16 pose1[16]={  0,42,-34,0,0,35,0,0,0,0,0, 0, 0, 0, 0, 0  };//张开套筒
	s16 pose2[16]={  0,42,-34,0,0,35,0,0,61,62,0,0,0,0,0,0  };
  s16 pose3[16]={  0,42,-34,0,0,35,0,0,0,0,0,0,0,0,0,0  };//伸下去
	s16 pose4[16]={  0,42,-34,0,0,35,0,0,61,62,0,0,0,0,0,0  };
  s16 pose5[16]={  0,0,-34,0,0,35,0,0,61,62,0,0,0,0,0,0  };///抬起来
//	s16 pose6[16]={  0,0,-34,0,0,35,0,0,45,46,0,0,0,0,0,0  };
//  s16 pose7[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose8[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose9[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose10[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose11[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose12[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };

	SlowAngle(pose0,pose1,25,15);
	SlowAngle(pose1,pose2,25,15);
	SlowAngle(pose2,pose3,25,15);
	delay_ms(500);
	
	SlowAngle(pose3,pose4,25,15);
	SlowAngle(pose4,pose5,25,15);
//	SlowAngle(pose5,pose6,28,20);
//	SlowAngle(pose6,pose7,10,10);
//	SlowAngle(pose7,pose8,15,15);
//	SlowAngle(pose8,pose9,15,15);
//	SlowAngle(pose9,pose10,10,15);
//	SlowAngle(pose10,pose11,15,15);
//	SlowAngle(pose11,pose1,15,15);
//	
	
}
void release1()//用于放下一个物块
{               // 0 1 2 3 4 5 6 7  8  9  10  11 12 13 14 15 
	s16 pose0[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, 0, 107, 0, 0  };
	s16 pose1[16]={  0,42,0,0,0,0,0,0,0,0,0, 0, 0, 107, 0, 0  };//张开套筒
	s16 pose2[16]={  0,42,0,0,0,0,0,0,61,62,0,0,0,107,0,0  };
    s16 pose3[16]={  0,0,0,0,0,0,0,0,61,62,0,0,0,107,0,0  };//伸下去
	s16 pose4[16]={  0,0,0,0,0,0,0,0,0,0,0,0,0,107,0,0  };
//  s16 pose5[16]={  0,0,0,0,0,0,0,0,106,107,0,0,0,0,0,0  };///抬起来
//	s16 pose6[16]={  0,0,0,0,0,0,0,0,45,46,0,0,0,0,0,0  };
//  s16 pose7[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose8[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose9[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose10[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose11[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose12[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };

	SlowAngle(pose0,pose1,25,15);
	SlowAngle(pose1,pose2,25,15);
	SlowAngle(pose2,pose3,25,15);
	delay_ms(100);
	SlowAngle(pose3,pose4,25,15);
//	SlowAngle(pose4,pose5,25,20);
//	SlowAngle(pose5,pose6,25,20);
//	SlowAngle(pose6,pose7,10,10);
//	SlowAngle(pose7,pose8,15,15);
//	SlowAngle(pose8,pose9,15,15);
//	SlowAngle(pose9,pose10,10,15);
//	SlowAngle(pose10,pose11,15,15);
//	SlowAngle(pose11,pose1,15,15);
//	
	
}

void catch1()//用于抓取一个物块（任务一）
{               //   0 1 2 3 4 5 6 7  8  9 10 11 12 13 14 15 
	s16 pose0[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0  };
	s16 pose1[16]={  0,0,0,0,0,0,0,0,61,62,0,0,0, 0, 0, 0  };//张开套筒
	s16 pose2[16]={  0,45,0,0,0,0,0,0,61,62,0,0,0,0 ,0, 0  };
	s16 pose3[16]={  0,45,0,0,0,0,0,0,61,62,0,0,0,0,0,0  };//伸下去
	s16 pose4[16]={  0,51,0,0,0,0,0,0,0,0,0,0,0,0,0,0  };
	s16 pose5[16]={  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0  };///抬起来
//	s16 pose6[16]={  0,0,-34,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose7[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose8[16]={  0,0,0,0,0,0,27,0,100,520,0,0,0,0,0,0  };
//  s16 pose9[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose10[16]={ 0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose11[16]={ 0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose12[16]={ 0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };

	SlowAngle(pose0,pose0,25,15);
	SlowAngle(pose1,pose2,25,15);
	SlowAngle(pose2,pose3,25,15);
	delay_ms(300);
	
	SlowAngle(pose3,pose4,25,15);
	SlowAngle(pose4,pose5,25,15);
//	SlowAngle(pose5,pose6,10,10);
//	SlowAngle(pose6,pose7,10,10);
//	SlowAngle(pose7,pose8,15,15);
//	SlowAngle(pose8,pose9,15,15);
//	SlowAngle(pose9,pose10,10,15);
//	SlowAngle(pose10,pose11,15,15);
//	SlowAngle(pose11,pose1,15,15);
//	
	
}
void zhixian7()//用于放下三个物块
{               // 0 1 2 3 4 5 6 7  8  9  10  11 12 13 14 15 
	s16 pose0[16]={  0,0,-34,0,0,35,0,0,0,0,0, 0, 0, 0, 0, 0  };
	s16 pose1[16]={  0,22,-34,0,0,35,0,0,0,0,0, 0, 0, 0, 0, 0  };//张开套筒
	s16 pose2[16]={  0,22,-34,0,0,35,0,0,41,42,0,0,0,0,0,0  };
  s16 pose3[16]={  0,42,-34,0,0,35,0,0,41,42,0,0,0,0,0,0  };//伸下去
	s16 pose4[16]={  0,42,-34,0,0,35,0,0,0,0,0,0,0,0,0,0  };//抱住
//  s16 pose5[16]={  0,42,-34,0,0,35,0,0,106,107,0,0,0,0,0,0  };///抬起来
//	s16 pose6[16]={  0,0,-34,0,0,35,0,0,106,107,0,0,0,0,0,0  };
//  s16 pose7[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose8[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose9[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose10[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose11[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose12[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };

	SlowAngle(pose0,pose1,25,15);
	SlowAngle(pose1,pose2,25,15);
	SlowAngle(pose2,pose3,25,15);
	delay_ms(300);
	
	SlowAngle(pose3,pose4,30,20);
	delay_ms(200);
//	SlowAngle(pose4,pose5,30,20);
//	SlowAngle(pose5,pose6,28,20);
//	SlowAngle(pose6,pose7,10,10);
//	SlowAngle(pose7,pose8,15,15);
//	SlowAngle(pose8,pose9,15,15);
//	SlowAngle(pose9,pose10,10,15);
//	SlowAngle(pose10,pose11,15,15);
//	SlowAngle(pose11,pose1,15,15);
//	
	
}
void open()//用于张开套筒
{               // 0 1 2 3 4 5 6 7  8  9  10  11 12 13 14 15 
	s16 pose0[16]={  0,42,-34,0,0,33,0,0,0,0,0, 0, 0, 0, 0, 0  };
	s16 pose1[16]={  0,42,-34,0,0,33,0,0,68,69,0, 0, 0, 0, 0, 0  };//张开套筒
	s16 pose2[16]={  0,42,-34,0,0,33,0,0,68,69,0,0,0,0,0,0  };
//  s16 pose3[16]={  0,42,-34,0,0,33,0,0,86,87,0,0,0,0,0,0  };//伸下去
//	s16 pose4[16]={  0,42,-34,0,0,33,0,0,45,46,0,0,0,0,0,0  };//抱住
//  s16 pose5[16]={  0,42,-34,0,0,33,0,0,106,107,0,0,0,0,0,0  };///抬起来
//	s16 pose6[16]={  0,0,-34,0,0,33,0,0,106,107,0,0,0,0,0,0  };
//  s16 pose7[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose8[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose9[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose10[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose11[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose12[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };

	SlowAngle(pose0,pose1,25,25);
	SlowAngle(pose1,pose2,25,25);
//	SlowAngle(pose2,pose3,25,15);
//	delay_ms(500);
//	
//	SlowAngle(pose3,pose4,30,20);
//	SlowAngle(pose4,pose5,30,20);
//	SlowAngle(pose5,pose6,28,20);
//	SlowAngle(pose6,pose7,10,10);
//	SlowAngle(pose7,pose8,15,15);
//	SlowAngle(pose8,pose9,15,15);
//	SlowAngle(pose9,pose10,10,15);
//	SlowAngle(pose10,pose11,15,15);
//	SlowAngle(pose11,pose1,15,15);
//	
	
}
void lowerright()//左上拨开
{

	s16 pose0[16]={  0,0,20,-20,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0  };
	s16 pose1[16]={  0,0,20,-50,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0  };
	s16 pose2[16]={  0,0,20,-78,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0  };
    s16 pose3[16]={  0,0,-10,-78,0,0,0,0,0,0,0, 0, 0, 0, 0, 0  };//
	s16 pose4[16]={  0,0,-10,-84,0,0,0,0,0,0,0, 0, 0, 0, 0, 0  };//
//  s16 pose5[16]={  0,42,-34,0,0,33,0,0,106,107,0,0,0,0,0,0  };//
//	s16 pose6[16]={  0,0,-34,0,0,33,0,0,106,107,0,0,0,0,0,0  };
//  s16 pose7[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose8[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose9[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose10[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose11[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose12[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };

	SlowAngle(pose0,pose1,25,25); 
	SlowAngle(pose1,pose2,25,25);
	SlowAngle(pose2,pose3,40,25);
	delay_ms(500);
	SlowAngle(pose3,pose4,40,25);
//	

//	SlowAngle(pose4,pose5,30,20);
//	SlowAngle(pose5,pose6,28,20);
//	SlowAngle(pose6,pose7,10,10);
//	SlowAngle(pose7,pose8,15,15);
//	SlowAngle(pose8,pose9,15,15);
//	SlowAngle(pose9,pose10,10,15);
//	SlowAngle(pose10,pose11,15,15);
//	SlowAngle(pose11,pose1,15,15);



}

void lowerleft()//左上拨开
{

	s16 pose0[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, -20, 20  };
	s16 pose1[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, -20, 50  };
	s16 pose2[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, -20, 75  };
    s16 pose3[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0,  10, 75  };//
	s16 pose4[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0,  10, 75  };//
//  s16 pose5[16]={  0,42,-34,0,0,33,0,0,106,107,0,0,0,0,0,0  };//
//	s16 pose6[16]={  0,0,-34,0,0,33,0,0,106,107,0,0,0,0,0,0  };
//  s16 pose7[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose8[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose9[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose10[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose11[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose12[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };

	SlowAngle(pose0,pose1,25,25); 
	SlowAngle(pose1,pose2,25,25);
	SlowAngle(pose2,pose3,40,25);
	delay_ms(500);
	SlowAngle(pose3,pose4,40,25);
//	

//	SlowAngle(pose4,pose5,30,20);
//	SlowAngle(pose5,pose6,28,20);
//	SlowAngle(pose6,pose7,10,10);
//	SlowAngle(pose7,pose8,15,15);
//	SlowAngle(pose8,pose9,15,15);
//	SlowAngle(pose9,pose10,10,15);
//	SlowAngle(pose10,pose11,15,15);
//	SlowAngle(pose11,pose1,15,15);



}
void upperleft()//左上拨开
{

	s16 pose0[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, -20, 70, 0, 0  };
	s16 pose1[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, -40, 107, 0, 0  };
	s16 pose2[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, 0, 107, 0, 0  };
//    s16 pose3[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0  };//
//	s16 pose4[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0  };//
//  s16 pose5[16]={  0,42,-34,0,0,33,0,0,106,107,0,0,0,0,0,0  };//
//	s16 pose6[16]={  0,0,-34,0,0,33,0,0,106,107,0,0,0,0,0,0  };
//  s16 pose7[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose8[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose9[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose10[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose11[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose12[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };

	SlowAngle(pose0,pose1,25,25); 
	SlowAngle(pose1,pose2,25,25);
//	SlowAngle(pose2,pose3,40,25);
//	delay_ms(500);
//	SlowAngle(pose3,pose4,40,25);
//	

//	SlowAngle(pose4,pose5,30,20);
//	SlowAngle(pose5,pose6,28,20);
//	SlowAngle(pose6,pose7,10,10);
//	SlowAngle(pose7,pose8,15,15);
//	SlowAngle(pose8,pose9,15,15);
//	SlowAngle(pose9,pose10,10,15);
//	SlowAngle(pose10,pose11,15,15);
//	SlowAngle(pose11,pose1,15,15);



}
void an_upperleft()//左上拨开
{

	s16 pose0[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, 0, 107, 0, 0  };
	s16 pose1[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, -40, 107, 0, 0  };
	s16 pose2[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, -20, 70, 0, 0  };
    s16 pose3[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0  };//
//	s16 pose4[16]={  0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0  };//
//  s16 pose5[16]={  0,42,-34,0,0,33,0,0,106,107,0,0,0,0,0,0  };//
//	s16 pose6[16]={  0,0,-34,0,0,33,0,0,106,107,0,0,0,0,0,0  };
//  s16 pose7[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose8[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose9[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose10[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//  s16 pose11[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };
//	s16 pose12[16]={  0,0,0,0,0,0,0,0,100,520,0,0,0,0,0,0  };

	SlowAngle(pose0,pose1,25,25); 
	SlowAngle(pose1,pose2,25,25);
	SlowAngle(pose2,pose3,40,25);
//	delay_ms(500);
//	SlowAngle(pose3,pose4,40,25);
//	

//	SlowAngle(pose4,pose5,30,20);
//	SlowAngle(pose5,pose6,28,20);
//	SlowAngle(pose6,pose7,10,10);
//	SlowAngle(pose7,pose8,15,15);
//	SlowAngle(pose8,pose9,15,15);
//	SlowAngle(pose9,pose10,10,15);
//	SlowAngle(pose10,pose11,15,15);
//	SlowAngle(pose11,pose1,15,15);



}
