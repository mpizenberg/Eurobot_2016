


#include <xc.h>
#include "main.h"

#include <timer.h>

volatile char Active_Delay_90 = 0;
volatile long Delay_90 = 0;
volatile char Delay_90_Over = 0;


void Timer_ms_Init(void)
{
	// activation du Timer3
    OpenTimer3(T3_ON &
                T3_IDLE_CON &
                T3_GATE_OFF &
                T3_PS_1_64 &
                T3_SOURCE_INT, 625 ); // 625 pour 1ms
    // configuration des interruptions
    ConfigIntTimer3(T3_INT_PRIOR_2 & T3_INT_ON);
	
}



volatile unsigned int Maxtime_Seq_AX12 = 0;
volatile unsigned int Loc_Maxtime = 0;

unsigned int Get_Maxtime_Seq_AX12(void)
{   return Maxtime_Seq_AX12;    }

void Set_Maxtime_Seq_AX12(unsigned int val)
{   Maxtime_Seq_AX12 = val;    }

void Set_Maxtime(unsigned int val)
{    Loc_Maxtime = val; }

char Get_Maxtime(void)
{
    if (Loc_Maxtime)
        return 1;
    else
        return 0;
}



// every ms
void __attribute__((interrupt,auto_psv)) _T3Interrupt(void) 
{
    static uint8_t Etat_Laisse = 0;
    static uint8_t Count_Laisse = 0;
    uint8_t Etat_Pin_Laisse = PIN_LAISSE;
    
    if (Etat_Pin_Laisse) {
        if (Count_Laisse < 30)
            Count_Laisse ++;
    } else {
        if (Count_Laisse)
            Count_Laisse --;
    }
    
    if (Etat_Laisse) {
        if (!Count_Laisse) {
            Etat_Laisse = 0;
            Active_Delay_90 = 1;
            Delay_90 = 0;
            SendStart();
            //Debug_Asserv_Start();
            //Debug_PWM_Start();
        }
    } else {
        if (Count_Laisse == 30) {
            Etat_Laisse = 1;
            Active_Delay_90 = 0;
            Delay_90 = 0;
        }
    }
    
    if (Delay_TimeOut_AX12) {
        Delay_TimeOut_AX12 --;
    }
    if (Maxtime_Seq_AX12) {
        Maxtime_Seq_AX12 --;
    }
    if (Loc_Maxtime)
        Loc_Maxtime--;
    
    if (Delay_90 < 90000) {
        if (Active_Delay_90) {
            Delay_90 ++;
        } else {
            Delay_90 = 0;
        }
        Delay_90_Over = 0;
    } else if (Delay_90 == 90000) {
        Delay_90 ++;
        SendEnd();
        Add_Action_AX12(AX12_FUNNY_ACTION);
        Delay_90_Over = 1;
    } else {
        motion_free();
        Delay_90_Over = 1;
        if (!Active_Delay_90) {
            Delay_90 = 0;
        }
    }

   _T3IF = 0;   // on baisse le flag
}

