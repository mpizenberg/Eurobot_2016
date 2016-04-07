/*
 * Template dsPIC33F
 * Compiler : Microchip xC16
 * �C : 33FJ128MC804
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
#include <uart.h>
#include <math.h>

#include "main.h"



int main(int argc, char** argv) {
    Init_All(0);

     Open_bras();
    // Code de test qui fait bouger le robot doucement :
    Debug_Asserv_Start(); 

    while (1) // boucle principale
    {
        Faire_Actions_AX12();

    }
}


void Debug_Asserv_Start(void)
{
    Speed MOVE;
    
    //asserv_init();
    MOVE.vt = 0.0;
    MOVE.v = 0.5;
    motion_speed(MOVE);
    __delay_ms(2000);
    Close_bras();
    
    MOVE.v = -0.5;
    motion_speed(MOVE);
    __delay_ms(2000);
    MOVE.v = 0;
    motion_speed(MOVE);
}
