/*
 * File:   main.c
 * Author: Robot
 *
 * Created on 13 avril 2016, 09:48
 */

#include <xc.h>

#include "main.h"
#include "time.h"


// on est sensé tourner de base à 8MHz

void main(void) {
    
    PORTA = 0;
    TRISA = 0;
    
    PORTCbits.RC2 = 0;
    TRISCbits.TRISC2 = 0;   // autre bit motopompe 
    
    TRISCbits.TRISC3 = 1;   // I2C SCL => POMPE HAUTE
    TRISCbits.TRISC4 = 1;   // I2C SDA => POMPE BASSE
    
    
    TRIS_LED = 0; 
    
    while (1) {
        POMPE_BASSE = PORTCbits.RC4;
        POMPE_HAUTE = PORTCbits.RC3;
        
        LED = (PORTCbits.RC4 || PORTCbits.RC3);
    }

}