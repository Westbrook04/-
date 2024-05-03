#ifndef __FINAL_TASK_H
#define __FINAL_TASK_H

#include "sys.h"









//决赛任务一,二
void Final_Task_one(void);
void Final_Task_two(void);

void task_one(void);
void task_two(void);
void task_two2(void);
/*****************************任务一各函数****************************/

/*************各情况的抓取回中心函数**************/
void Car_Correctline(void);
//有障碍抓1或3
void HaveObstacle_Grap_1or3(void);
void HaveObstacle_Grap_1or2(void);
void HaveObstacle_Grap_1or1(void);
void A_obTo_centre(void);

//有障碍抓2
void HaveObstacle_Grap_2(void);
void C_obTo_centre(void);

//有障碍抓3
//void HaveObstacle_Grap_3(void);
void D_obTo_centre(void);

//有障碍抓4
void HaveObstacle_Grap_4(void);
void HaveObstacle_Grap_1or4(void);
void B_obTo_centre(void);

//没障碍物的抓取回家函数
void Noobstacle_Grab_Block(void);
void Noobstacle_Grab_Block1(void);
void Noobstacle_Grab_Block2(void);
void Noobstacle_Grab_Block180(void);
void Noobstacle_To_Centre(void);
void Noobstacle_To_Centre1(void);
void Noobstacle_To_Centre2(void);
void Noobstacle_Grab_Block4(void);
//颜色识别函数
void Color_turnplate(void);
void Color_identify (void);

//放置物块函数
void Lay_Block(void);
void Error3_Lay_Block(void);

//回家函数
void Black_gogome(void);
void Green_gogome(void);

//卡位放置函数
void Ka_socre(void);
//卡位放白色
void redKa_socre(void);

void WhiteKa_socre(void);
void Haveblack_relasegreen(void);
void Black_relase(void);
void Noblack_relasegreen(void);
/**********************************任务二各函数**********************************/
void TenKa_score(void);
//void HomeLeftTo_Grap(void);
void HomeRightTo_Grap(void);

void Init_position(void);
//void Grab_ABCDE(void);
void New_Grab_ABCDE(void);

void Lay_A(void);
void Lay_B(void);
void Lay_C(void);
void Lay_D(void);
void QitaLay_B(void);
void QitaLay_A(void);
void Go_homefromD(void);

void new_catch_4(void);

void Ka_score_9(void);
void Ka_score_10(void);
void Ka_score_11(void);
void Ka_score10(void);
void Ka_scoreBCD(void);
void layBCD_correct(void);
void Pick_Up_task2(void);
void kong_white(void);

void lay_E_white(void);
void lay_E_blue(void);
void lay_E_black(void);
void lay_E_green(void);
void lay_E_red(void);


void houtui(void);

void catch_1(void);
void catch_4(void);
void catch_5(void);

void catch_2(void);
void catch_3(void);
void catch_12345(void);



//以下工程赛专用函数

void color_init(void);
void color_init1(void);

void Obstacle_detcetion(void);
void HaveObstacle_Grap_1(void);
void HaveObstacle_To_Centre(void);
void colour_error(void);
void Nobstacle_To_Centre(void);

void color_error(void);

void lay_red(void);
void lay_white(void);
void lay_green(void);
void lay_black(void);
void lay_blue(void);



	void ka_f_one(void);
	void ka_g_one(void);//第一轮
	void ka_f_two(void);//第二轮
	void ka_g_two(void);
	void ka_three(void);//第三轮
void right_into_tong(void);
	void left_into_tong(void);
	void ready_catch1_1(void);
		void ready_catch1_2(void);
void	go_back_centre(void);



void go_straight(void);

void pick_e(void);
void pick_a(void);
void go_lay(void);
void chose_to_lay(void);
	void die(void);
	void lay1(void);
	void lay2(void);
	
	void A_color(void);
	void E_color(void);
	
	void A_put(void);
	void B_put(void);
	void C_put(void);
	void E_put(void);
	void D_put(void);
	void D_colorjudgment(void);
	void task2BT(void);
//	void task2AT1(void);
	
    void task2T(u8 v);
	void task2T1(u8 v);
	
	
	
	void position(void);
	
	
	
#endif
