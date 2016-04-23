/*
* UltraSon
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

#include <xc.h>
#include <stdio.h>
#include "main.h"
#include <timer.h>


// principe : petit spike sur la pin (qq usecs) pin en sortie
// puis attente, avec mesure du temps à 1       pin en entrée
// attente 50 ms entre 2 spikes

// aussi en externe
volatile uint8_t Etat_Ultrason = 0;
volatile uint16_t Mesure_Timer_Ultrason = 0xFFFF;     // mesure brutale du timer
volatile uint16_t Mesure_Distance_Ultrason = 3000;  // distance en mm
uint8_t Sector_Ultrason = 0;

// debug
volatile uint8_t Debug_Ultrason = 0;
volatile uint16_t count_Debug_Ultrason = 0;

volatile char Ative_Motion_Free_Ultrason = 1;

// pas en externe
volatile uint8_t nb_Coups_Timers = 0;

void Init_Ultrasons (void)
{
    TRIS_ULTRASON = 1;          // mise en input de la pin
    PIN_CN_ULTRASON_IE = 0;     // desactivation de l'IT
    CloseTimer4();
    __delay_ms(50); // attente de 50 ms pour bien tuer l'IT
    Etat_Ultrason = U_ETAT_OFF;
    Mesure_Timer_Ultrason = 0xFFFF;     // mesure brutale du timer
    Mesure_Distance_Ultrason = 3000;  // distance en mm
    Sector_Ultrason = 1;        // sector ok
    nb_Coups_Timers = 0;

    OpenTimer4(T4_ON & T4_GATE_OFF & T4_PS_1_8 & T4_SOURCE_INT, 0xFFFF );
    // FCY = 40Meg   prescaler à 8 donc F timer = 5Meg
    // 1 coup = 200 ns = 0.2us
    // max = 65535 => 13.107 ms     // ce qui correspondra à de l'overshoot

    // configuration des interruptions
    ConfigIntTimer4(T4_INT_PRIOR_3 & T4_INT_ON);        // meme priorité que CN
    
    Init_CN();
    
    Etat_Ultrason = U_ETAT_FOR_SEND1;
    
    
}


void Init_CN()
{

    IPC4bits.CNIP = 3;      //Interrupt level 3
    IFS1bits.CNIF = 0;      // Reset CN interrupt
    IEC1bits.CNIE = 1;      // Enable CN interrupts
}


void __attribute__((interrupt,auto_psv)) _T4Interrupt(void) {
    // attente pour envoi : on envoie et on passe à l'état suivant
    if (Etat_Ultrason & U_ETAT_FOR_SEND1) {
        count_Debug_Ultrason++;
        if (count_Debug_Ultrason == 50) {
            count_Debug_Ultrason = 0;
        }
        if (!count_Debug_Ultrason && Debug_Ultrason) { printf("$START_SPIKE;"); }
        PIN_ULTRASON = 1;
        TRIS_ULTRASON = 0;      // pin en sortie
        PR4 = 200;              // 40 us pour le spike de début
        Etat_Ultrason = U_ETAT_SEND1;
    } else if (Etat_Ultrason & U_ETAT_SEND1) {      // spike en cours => il faut le finir + lancer le truc de mesure
        if (!count_Debug_Ultrason && Debug_Ultrason) { printf("$END_SPIKE;"); }
        PIN_ULTRASON = 0;
        Etat_Ultrason = U_ETAT_WAIT1;
        PR4 = 0xFFFF;           // 13.107 ms (overshoot)
        nb_Coups_Timers = 0;
        PIN_CN_ULTRASON_IE = 1; // activation IT sur PIN
        TRIS_ULTRASON = 1;      // on relache la pin
    } else if (Etat_Ultrason & U_ETAT_WAIT1) {
        // attente de la remontée de la pin du capteur qui a visiblement pas déclenché...
        // on va redémarrer ...
        if (!count_Debug_Ultrason && Debug_Ultrason) { printf("$ERROR_PIN;"); }
        PIN_CN_ULTRASON_IE = 0;
        PR4 = 0xFFFF;
        nb_Coups_Timers = 1;
        Etat_Ultrason = U_ETAT_WAIT_FOR_RESTART;
    } else if (Etat_Ultrason & U_ETAT_WAIT0) {      // attente que la pin du capteur repasse à 0
        // cette attente a overshooté donc capteur super loin...
        nb_Coups_Timers = 1;
        Etat_Ultrason = U_ETAT_WAIT0_OVERSHOOT;
    } else if (Etat_Ultrason & U_ETAT_WAIT0_OVERSHOOT) {      // attente que la pin du capteur repasse à 0
        // cette attente a multi-overshooté donc capteur super loin...
        nb_Coups_Timers ++;
    } else if (Etat_Ultrason & U_ETAT_WAIT_FOR_RESTART) {
        nb_Coups_Timers ++;
        if (nb_Coups_Timers > 3) {
            Etat_Ultrason = U_ETAT_FOR_SEND1;
            if (!count_Debug_Ultrason && Debug_Ultrason) { printf("meas %dmm;", Mesure_Distance_Ultrason); }
        }
    }

    _T4IF = 0;  // baisse du flag
}

/**********************************************/
// CN interrupt for ultrasson 
void __attribute__ ((__interrupt__, no_auto_psv)) _CNInterrupt(void)
{
    uint32_t val32;
    
    // baisse le flag puis récup des etats de pins, 
    // si les pins rebougent durant ce laps tres court, ça redéclenchera une IT directe apres,
    // mais avec old_ ça doit tenir
    IFS1bits.CNIF = 0; // Clear CN interrupt
    uint8_t Etat_Pin_Ultrason = PIN_ULTRASON;



    // si Etat_Ultrason mérite que l'on s'occupe de lui
    if (Etat_Ultrason & (U_ETAT_WAIT1 + U_ETAT_WAIT0 + U_ETAT_WAIT0_OVERSHOOT)) {
        if (Etat_Pin_Ultrason) {
            if (Etat_Ultrason & U_ETAT_WAIT1) {
                //if (!count_Debug_Ultrason && Debug_Ultrason) { printf("$START_MESURE;"); }
                TMR4 = 0;                       // restart du timer pour la mesure
                Etat_Ultrason = U_ETAT_WAIT0;
            }
        } else {
            if (Etat_Ultrason & U_ETAT_WAIT0) {     // si attente standard => récup mesure
                PIN_CN_ULTRASON_IE = 0;     // desactivation de cette IT
                Mesure_Timer_Ultrason = TMR4;       // 1 = 0.2us
                //if (!count_Debug_Ultrason && Debug_Ultrason) { printf("$END_MESURE;"); }
                // à base de vitesse du son (/2 pour l'aller-retour)  340.29 m/s
                // => 1 coup = 34 us 
                // pour avoir distance en mm, il faut diviser par 29.39
                // donc multiplication par 1115 puis division par 32768 (2^15)
                // passage obligé en 32 bits
                val32 = 1115 * (uint32_t)(Mesure_Timer_Ultrason);
                Mesure_Distance_Ultrason = (uint16_t)((val32 >> 15));
                if (Sector_Ultrason) {
                    if (Mesure_Distance_Ultrason < (ULTRASON_THRESOLD - ULTRASON_THRESOLD_TRIGGER)) {
                        if (Ative_Motion_Free_Ultrason) {
                            motion_free();
                        }
                        Sector_Ultrason = 0;            // passage en sector  occupé
                        DetectUltrason();		// on previent la PI
                    }
                } else {
                    if (Mesure_Distance_Ultrason > (ULTRASON_THRESOLD + ULTRASON_THRESOLD_TRIGGER)) {
                        Sector_Ultrason = 1;    // passage en sector ok
                        ReleaseUltrason();              // on previent la PI
                    }
                }
                Etat_Ultrason = U_ETAT_WAIT_FOR_RESTART;   // attente fin du timer pour restart...
            } else if (Etat_Ultrason & U_ETAT_WAIT0_OVERSHOOT) {    // si attente overshoot => fabrication d'une mesure max
                //if (!count_Debug_Ultrason && Debug_Ultrason) { printf("$END_MESURE_OVER;"); }
                PIN_CN_ULTRASON_IE = 0;     // desactivation de cette IT
                Mesure_Timer_Ultrason = 0xFFFF;
                Mesure_Distance_Ultrason = 3000;            // 3m
                Etat_Ultrason = U_ETAT_WAIT_FOR_RESTART;    // attente fin du timer pour restart...
            }
        }
    }
}


void Start_Stop_Debug_Ultrason(void)
{
    if (Debug_Ultrason) {
        Debug_Ultrason = 0;
    } else {
        Debug_Ultrason = 1;
    }
}

void Enable_Ultrason (char enable)
{
    Ative_Motion_Free_Ultrason = enable;
}


