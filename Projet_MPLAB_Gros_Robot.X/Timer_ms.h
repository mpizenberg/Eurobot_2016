#ifndef __TIMER_MS_H
#define __TIMER_MS_H



extern volatile char Delay_90_Over;

void Timer_ms_Init(void);

unsigned int Get_Maxtime_Seq_AX12(void);
void Set_Maxtime_Seq_AX12(unsigned int val);

void Set_Maxtime(unsigned int val);
char Get_Maxtime(void);

#endif