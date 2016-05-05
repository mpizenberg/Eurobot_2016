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


#include <stdint.h>        // Includes uint16_t definition
#include <stdio.h>         // Includes sprintf
#include <stdbool.h>       // Includes true/false definition
#include <math.h>

#include "main.h"

void reglage_asserv(void);

int main(int argc, char** argv) {
    Init_All(0);
    //reglage_asserv();
    while (1)
    {
        Faire_Actions_AX12();
        Gestion_IO_AU_Loop();
    }
}


void reglage_asserv(void)
{
//    int i;
//    Position Pos0, Pos1, Pos2, Pos3;
//    Speed Speed1;
//    Choose_Enabled_US(0);
//    Pos0.x = 0;     Pos0.y = 0;
//    Speed1.v = 0.3;
//    Speed1.vt = 0;
//    Pos1.x = 1;   Pos1.y = 0;
//    Pos2.x = 1;   Pos2.y = 1;
//    Pos3.x = 0;   Pos3.y = 1;
//    for (i = 1; i < 6; i++) {
//        set_Constraint_vitesse_max(0.1*i);
//        motion_pos(Pos1);
//        while (!pos_asserv.done);
//        motion_pos(Pos2);
//        while (!pos_asserv.done);
//        motion_pos(Pos3);
//        while (!pos_asserv.done);
//        motion_pos(Pos0);
//        while (!pos_asserv.done);
//    }
//    debug_count = 0;
//    motion_speed(Speed1);
//    __delay_ms(2500);
//    motion_free();
//    __delay_ms(2500);
//    
//    motion_pos(Pos0);
}

void Debug_Asserv_Start(void)
{
    while (PIN_LAISSE);
    Position pos1 = {0.40,0,0};
    Position pos2 = {0.40,0.40,0};
    motion_push(pos1,0.15);
    motion_push(pos2,0);
    //motion_speed(MOVE);
}

void Debug_Asserv_Start2(void)
{
    while (PIN_LAISSE);
    Position pos1 = {0.40,0,0};
    Position pos2 = {0.40,0.40,0};
    motion_pos(pos1);
    while(!motion_done());
    motion_pos(pos2);
    //motion_speed(MOVE);
}