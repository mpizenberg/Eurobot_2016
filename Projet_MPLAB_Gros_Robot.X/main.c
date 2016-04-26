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
#include <stdint.h>        // Includes uint16_t definition
#include <stdio.h>         // Includes sprintf
#include <stdbool.h>       // Includes true/false definition
#include <math.h>

#include "main.h"



int main(int argc, char** argv) {
    
    Init_All(0);

    // __delay_ms(2000);
    // Code de test qui fait bouger le robot doucement :
    // Debug_Asserv_Start2();
    //reglage_asserv();

    while (1) // boucle principale
    {
        Faire_Actions_AX12();
        
    }
    
}


void reglage_asserv(void)
{
    Speed speed;
    Position pos;
    speed.v = 0;
    speed.vt = 5;
    pos.x = 1.2;
    pos.y = 0;
    motion_pos(pos);
    while (!motion_done());
    pos.x = 1.2;
    pos.y = 1.2;
    motion_pos(pos);
    while (!motion_done());
    pos.x = 0;
    pos.y = 1.2;
    motion_pos(pos);
    while (!motion_done());
    pos.x = 0;
    pos.y = 0;
    motion_pos(pos);
    while (!motion_done());
    motion_angle(0);
    debug_count = 0;
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