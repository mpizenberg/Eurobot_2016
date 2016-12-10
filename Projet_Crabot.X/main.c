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
    
    Position p0 = {0,0,0};
    
    Position p1 = {1,0,0};
    Position p2 = {1,1,0};
    Position p3 = {0,1,0};
    Position p4 = {0,2,0};
    Position p5 = {1,2,0};
    
    Position p6 = {0.5,0.2,0};
    Position p7 = {1,-0.2,0};
    Position p8 = {1.5,0.2,0};
    Position p9 = {2,-0.2,0};
    
    while (PIN_LAISSE);
    Init_All(0);
    motion_pos(p1);
    while (!motion_done());
//    motion_angle(PI/2);
//    while (!motion_done());
    motion_pos(p2);
    while (!motion_done());
//    motion_angle(0);
//    while (!motion_done());
    motion_pos(p3);
    while (!motion_done());
//    motion_angle(PI/2);
//    while (!motion_done());
    motion_pos(p4);
    while (!motion_done());
//    motion_angle(0);
//    while (!motion_done());
    motion_pos(p5);
    while (!motion_done());

    motion_pos(p0);
    while (!motion_done());
    
    motion_pos(p6);
    while (!motion_done());
    motion_pos(p7);
    while (!motion_done());
    motion_pos(p8);
    while (!motion_done());
    motion_pos(p9);
    while (!motion_done());
    
    
    while (1) // boucle principale
    {
//        Faire_Actions_AX12();
//        Gestion_IO_AU_Config_Loop();
        
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