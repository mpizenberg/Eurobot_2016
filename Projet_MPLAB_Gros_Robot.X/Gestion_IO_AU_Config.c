
#include "main.h"


void Gestion_IO_AU_Config_Init(void)
{
    TRIS_DETECT_10V = 1;
    TRIS_TEAM = 1;  // input for bouton vert/violet(rouge)
    
    TRIS_CONF1 = 1;
    TRIS_CONF2 = 1;
    TRIS_CONF4 = 1;

    PULL_UP_CONF1 = 1;
    PULL_UP_CONF2 = 1;
    PULL_UP_CONF4 = 1;
}

void Gestion_IO_AU_Config_Loop(void){

    static int old_Detect_10V = 0;
    if (PIN_DETECT_10V) {
        if (!old_Detect_10V) {
            Init_All(0);
        }
        old_Detect_10V = 1;
    } else {
        old_Detect_10V = 0;
    }
}

int Get_Number_Config(void)
{
    int val = 0;
    
    if (!PIN_CONF1)
        val += 1;
    if (!PIN_CONF2)
        val += 2;
    if (!PIN_CONF4)
        val += 4;
    
    return val;
}