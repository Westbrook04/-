#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

#define M1 PFout(14)
#define M2 PFout(15)
#define M3 PGout(0)
#define M4 PGout(1)


#define M5 PCout(4)
#define M6 PCout(5)
#define M7 PEout(7)
#define M8 PEout(8)



void MOTOR_CONFIG(void);
void TIM5_PWM_Init(u32 arr,u32 psc);
void Motor_Dir(void);

#endif
