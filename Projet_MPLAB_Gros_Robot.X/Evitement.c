/*
* Sick
* Compiler : Microchip xC16
* µC : 33FJ64MC804
* Mai 2015
*    ____________      _           _
*   |___  /| ___ \    | |         | |
*      / / | |_/ /___ | |__   ___ | |_
*     / /  |    // _ \| '_ \ / _ \| __|
*    / /   | |\ \ (_) | |_) | (_) | |_
*   /_/    |_| \_\___/|____/ \___/'\__|
*			      7robot.fr
*/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC33E__)
    	#include <p33Exxxx.h>
    #elif defined(__dsPIC33F__)
    	#include <p33Fxxxx.h>
    #endif
#endif

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdio.h>
#include <stdbool.h>       /* Includes true/false definition                  */

#include "main.h"


uint8_t Motion_Free_Activ_Sick[4] = {1,1,1,1};

volatile uint8_t Can_Restart_Order = 0;
volatile uint8_t Old_Blocked_Front = 0, Old_Blocked_Back = 0;


void Init_Evitement(void)
{
    // Soft IT pour la gestion des secteurs
    // qui prend l'IT SPI1 Erreur
    IFS0bits.SPI1EIF = 0;   
    IEC0bits.SPI1EIE = 1;
    IPC2bits.SPI1EIP = 1;   // pas tres prioritaire
    //_SPI1ErrInterrupt
}


void Choose_Enabled_Sicks(int Sicks_En)
{
    int i;
    for (i = 0; i < 4; i++) {
        if (Sicks_En & (1<<i)) {
            Motion_Free_Activ_Sick[i] = 1;
        } else {
            Motion_Free_Activ_Sick[i] = 0;
        }
    }
} 

void New_Order_Evitement_Handling(void)
{   
    Can_Restart_Order = 0;  
    Old_Blocked_Front = 0;
    Old_Blocked_Back = 0;
}

void Must_do_Gestion_Evitement(void)
{
    IFS0bits.SPI1EIF = 1;   
}

void __attribute__ ((interrupt, auto_psv)) _SPI1ErrInterrupt(void)
{
    Gestion_Evitement_Every_few_ms();
    IFS0bits.SPI1EIF = 0;   
}

void Gestion_Evitement_Every_few_ms(void)
{
    
    uint8_t Blocked_Front, Blocked_Back;
    // sector 0 = obstacle detecté, sector 1 = "sûr"
    Blocked_Front = ((!Get_Sick_Sector(0)) && SICK1_IS_FRONT && Motion_Free_Activ_Sick[0]) ||
                    ((!Get_Sick_Sector(1)) && SICK2_IS_FRONT && Motion_Free_Activ_Sick[1]) ||
                    ((!Get_Sick_Sector(2)) && SICK3_IS_FRONT && Motion_Free_Activ_Sick[2]) ||
                    ((!Get_Sick_Sector(3)) && SICK4_IS_FRONT && Motion_Free_Activ_Sick[3]);
    
    Blocked_Back  = ((!Get_Sick_Sector(0)) && SICK1_IS_BACK && Motion_Free_Activ_Sick[0]) ||
                    ((!Get_Sick_Sector(1)) && SICK2_IS_BACK && Motion_Free_Activ_Sick[1]) ||
                    ((!Get_Sick_Sector(2)) && SICK3_IS_BACK && Motion_Free_Activ_Sick[2]) ||
                    ((!Get_Sick_Sector(3)) && SICK4_IS_BACK && Motion_Free_Activ_Sick[3]);
    
    Blocked_Front = Blocked_Front && ((Sens_Vitesse_Deplacement() == 1)  || Old_Blocked_Front);
    Blocked_Back  = Blocked_Back  && ((Sens_Vitesse_Deplacement() == -1) || Old_Blocked_Back);
    
    if (Blocked_Front && !Old_Blocked_Front) {
        if (Is_Asserv_Mode_Pos())
            Can_Restart_Order = 1;
        motion_free();
    } else if (!Blocked_Front && Old_Blocked_Front && Can_Restart_Order) {
        Can_Restart_Order = 0;
        load_last_order();
    }
    
    if (Blocked_Back && !Old_Blocked_Back) {
        if (Is_Asserv_Mode_Pos())
            Can_Restart_Order = 1;
        motion_free();
    } else if (!Blocked_Back && Old_Blocked_Back && Can_Restart_Order) {
        Can_Restart_Order = 0;
        load_last_order();
    }
    
    Old_Blocked_Front = Blocked_Front;
    Old_Blocked_Back = Blocked_Back;
    
//ReleaseSick(channel_conv+1);			// on previent la PI

//DetectSick(channel_conv+1);				// on previent la PI

}


