
#include "main.h"


void Gestion_IO_AU_Init(void)
{
    TRIS_DETECT_10V = 1;
    TRIS_TEAM = 1;  // input for bouton vert/violet(rouge)
    TRIS_LAISSE = 1;            // input for laisse
}

void Gestion_IO_AU_Loop(void){

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
