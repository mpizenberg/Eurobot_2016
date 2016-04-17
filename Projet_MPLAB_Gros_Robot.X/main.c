/*
 * Template dsPIC33F
 * Compiler : Microchip xC16
 * µC : 33FJ128MC804
 * Mars 2016
 *
 *    ______ _____      _           _
 *   |___  /| ___ \    | |         | |
 *      / / | |_/ /___ | |__   ___ | |_
 *     / /  |    // _ \| '_ \ / _ \| __|
 *    / /   | |\ \ (_) | |_) | (_) | |_
 *   /_/    |_| \_\___/|____/ \___/'\__|
 *			      7robot.fr
 */



/********Headers********/
#include <xc.h>
/******************************************************************************/
/* Configuration                                                             */
/******************************************************************************/

// Select Oscillator and switching.
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);
// Select clock.
_FOSC(POSCMD_NONE & OSCIOFNC_ON & IOL1WAY_ON & FCKSM_CSDCMD);
// Watchdog Timer.
_FWDT(FWDTEN_OFF);
// Select debug channel.
_FICD(ICS_PGD3 & JTAGEN_OFF);

_FPOR(PWMPIN_ON);


#include <stdint.h>        // Includes uint16_t definition
#include <stdio.h>         // Includes sprintf
#include <stdbool.h>       // Includes true/false definition
#include <math.h>

#include "main.h"



int main(int argc, char** argv) {
    Init_All(0);

     __delay_ms(2000);
    // Code de test qui fait bouger le robot doucement :
    //Debug_Asserv_Start();
    reglage_asserv();
     while(1);
/*
    while (1) // boucle principale
    {
        Faire_Actions_AX12();
    }*/
}


void reglage_asserv(void)
{
    Speed speed;
    speed.v = 0;
    speed.vt = 3;
    motion_speed(speed);
    debug_count = 0;
    PWM_Moteurs(-100,100);
    __delay_ms(300);
    int i=100;
    for(i=50; i>=0; i--){
        PWM_Moteurs(-2i,2i);
        __delay_ms(5);
    }
    
}
void Debug_Asserv_Start(void)
{
        int k,i;
        for (k = 0; k < 5; k++)
        {
            for (i = 1; i < 6; i++)
            {
                motion_angle((float)(i));
                __delay_ms(500);
            // Faire_Actions_AX12();
            }
            motion_angle(0);
            __delay_ms(500);
        }
        motion_angle(0);


    Speed MOVE;
    
    //asserv_init();
    MOVE.vt = 0.0;
    MOVE.v = 0.5;
    //motion_speed(MOVE);
}
