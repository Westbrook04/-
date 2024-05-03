#ifndef __DRIVE_MOTOR_H
#define __DRIVE_MOTOR_H

#include "sys.h"

void Set_Motor(s32 leftspeed,s32 rightseepd);
void CarAdvance(u8 speed);
void CarRetreat(u8 speed);
void DriveLeftWhell(u8 left_direction,u8 speed);
void DriveRightWhell(u8 right_direction,u8 speed);

void Car_Advance35(void);
void Car_Retreat35(void);
void Car_Advance30(void);
void Car_Advance28(void);
void Car_Retreat28(void);
void Car_Advance35pian(void);
void Car_Advance22(void);
void Car_Advance20(void);
void Car_Retreat20(void);
void Car_Advance27pian(void);
void Set_Motor_rpm(s32 leftspeed,s32 rightseepd);
void SET_Motor(s32 leftspeed_f,s32 rightseepd_f,s32 leftspeed_b,s32 rightseepd_b);
#endif
