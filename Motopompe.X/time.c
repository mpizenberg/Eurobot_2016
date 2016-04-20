/*
 * File:   time.c
 * Author: Robot
 *
 * Created on 13 avril 2016, 09:54
 */

#include <xc.h>

#include "main.h"
#include "time.h"

void time(void)
{
     int j = 0;
        while (j < 50) { //Permet d'attendre 1 seconde, selon la configuration du Timer 2.
            if (PIR1bits.TMR2IF) { //TMR2IF = Flag du timer 2
                j++;
                PIR1bits.TMR2IF = 0;
            }
        }
}