#include <xc.h>

#include <stdint.h>        /* Includes uint16_t definition   */
#include <stdbool.h>       /* Includes true/false definition */
#include <timer.h>
#include <uart.h>
#include <stdio.h>

//#include "extern_globals.h"

#include "main.h"

//debug
#include "uart.h"

volatile char Active_Delay_90 = 0;
volatile long Delay_90 = 0;
volatile char Delay_90_Over = 0;

void InitTimers()
{

    _NSTDIS = 0; // activation de la priorité des interruptions
    AD1PCFGL = 0xFFFF; //Pins analogiques en numérique pour que ATP marche !!


    
    // activation du Timer2
    OpenTimer2(T2_ON &
                T2_IDLE_CON &
                T2_GATE_OFF &
                T2_PS_1_64 &
                T2_SOURCE_INT, 3125 ); // 3125 pour 5ms
    // configuration des interruptions
    ConfigIntTimer2(T2_INT_PRIOR_4 & T2_INT_ON);

    // activation du Timer3
    OpenTimer3(T3_ON &
                T3_IDLE_CON &
                T3_GATE_OFF &
                T3_PS_1_64 &
                T3_SOURCE_INT, 625 ); // 625 pour 1ms
    // configuration des interruptions
    ConfigIntTimer3(T3_INT_PRIOR_2 & T3_INT_ON);
    TMR3 = 312;     // pour d�phasage de entre Timer2 et 3...

    // info : timer 5 est utilis� par la mesure des sicks
    // info : timer 4 est utilis� par la mesure de l'ultrason
    
    // Ici interruption des actions des bras
    //IFS2bits.SPI2IF = 0; // Flag SPI2 Event Interrupt Priority
    //IPC8bits.SPI2IP = 2; // Priority SPI2 Event Interrupt Priority
    //IEC2bits.SPI2IE = 1; //Enable SPI2 Event Interrupt Priority


    

}

void Init_CN()
{

    IPC4bits.CNIP = 3;      //Interrupt level 3
    IFS1bits.CNIF = 0;      // Reset CN interrupt
    IEC1bits.CNIE = 1;      // Enable CN interrupts
}

/******************************************************************************/
/* Interrupt Vector Options                                                   */
/******************************************************************************/
/*                                                                            */
/* Refer to the C30 (MPLAB C Compiler for PIC24F MCUs and dsPIC33F DSCs) User */
/* Guide for an up to date list of the available interrupt options.           */
/* Alternately these names can be pulled from the device linker scripts.      */
/*                                                                            */
/* dsPIC33F Primary Interrupt Vector Names:                                   */
/*                                                                            */
/* _INT0Interrupt      _C1Interrupt                                           */
/* _IC1Interrupt       _DMA3Interrupt                                         */
/* _OC1Interrupt       _IC3Interrupt                                          */
/* _T1Interrupt        _IC4Interrupt                                          */
/* _DMA0Interrupt      _IC5Interrupt                                          */
/* _IC2Interrupt       _IC6Interrupt                                          */
/* _OC2Interrupt       _OC5Interrupt                                          */
/* _T2Interrupt        _OC6Interrupt                                          */
/* _T3Interrupt        _OC7Interrupt                                          */
/* _SPI1ErrInterrupt   _OC8Interrupt                                          */
/* _SPI1Interrupt      _DMA4Interrupt                                         */
/* _U1RXInterrupt      _T6Interrupt                                           */
/* _U1TXInterrupt      _T7Interrupt                                           */
/* _ADC1Interrupt      _SI2C2Interrupt                                        */
/* _DMA1Interrupt      _MI2C2Interrupt                                        */
/* _SI2C1Interrupt     _T8Interrupt                                           */
/* _MI2C1Interrupt     _T9Interrupt                                           */
/* _CNInterrupt        _INT3Interrupt                                         */
/* _INT1Interrupt      _INT4Interrupt                                         */
/* _ADC2Interrupt      _C2RxRdyInterrupt                                      */
/* _DMA2Interrupt      _C2Interrupt                                           */
/* _OC3Interrupt       _DCIErrInterrupt                                       */
/* _OC4Interrupt       _DCIInterrupt                                          */
/* _T4Interrupt        _DMA5Interrupt                                         */
/* _T5Interrupt        _U1ErrInterrupt                                        */
/* _INT2Interrupt      _U2ErrInterrupt                                        */
/* _U2RXInterrupt      _DMA6Interrupt                                         */
/* _U2TXInterrupt      _DPIN_LAISSEMA7Interrupt                               */
/* _SPI2ErrInterrupt   _C1TxReqInterrupt                                      */
/* _SPI2Interrupt      _C2TxReqInterrupt                                      */
/* _C1RxRdyInterrupt     PIN_LAISSE                                           */
/*                                                                            */
/* dsPIC33E Primary Interrupt Vector Names:                                   */
/*                                                                            */
/* _INT0Interrupt     _IC4Interrupt      _U4TXInterrupt                       */
/* _IC1Interrupt      _IC5Interrupt      _SPI3ErrInterrupt                    */
/* _OC1Interrupt      _IC6Interrupt      _SPI3Interrupt                       */
/* _T1Interrupt       _OC5Interrupt      _OC9Interrupt                        */
/* _DMA0Interrupt     _OC6Interrupt      _IC9Interrupt                        */
/* _IC2Interrupt      _OC7Interrupt      _PWM1Interrupt                       */
/* _OC2Interrupt      _OC8Interrupt      _PWM2Interrupt                       */
/* _T2Interrupt       _PMPInterrupt      _PWM3Interrupt                       */
/* _T3Interrupt       _DMA4Interrupt     _PWM4Interrupt                       */
/* _SPI1ErrInterrupt  _T6Interrupt       _PWM5Interrupt                       */
/* _SPI1Interrupt     _T7Interrupt       _PWM6Interrupt                       */
/* _U1RXInterrupt     _SI2C2Interrupt    _PWM7Interrupt                       */
/* _U1TXInterrupt     _MI2C2Interrupt    _DMA8Interrupt                       */
/* _AD1Interrupt      _T8Interrupt       _DMA9Interrupt                       */
/* _DMA1Interrupt     _T9Interrupt       _DMA10Interrupt                      */
/* _NVMInterrupt      _INT3Interrupt     _DMA11Interrupt                      */
/* _SI2C1Interrupt    _INT4Interrupt     _SPI4ErrInterrupt                    */
/* _MI2C1Interrupt    _C2RxRdyInterrupt  _SPI4Interrupt                       */
/* _CM1Interrupt      _C2Interrupt       _OC10Interrupt                       */
/* _CNInterrupt       _QEI1Interrupt     _IC10Interrupt                       */
/* _INT1Interrupt     _DCIEInterrupt     _OC11Interrupt                       */
/* _AD2Interrupt      _DCIInterrupt      _IC11Interrupt                       */
/* _IC7Interrupt      _DMA5Interrupt     _OC12Interrupt                       */
/* _IC8Interrupt      _RTCCInterrupt     _IC12Interrupt                       */
/* _DMA2Interrupt     _U1ErrInterrupt    _DMA12Interrupt                      */
/* _OC3Interrupt      _U2ErrInterrupt    _DMA13Interrupt                      */
/* _OC4Interrupt      _CRCInterrupt      _DMA14Interrupt                      */
/* _T4Interrupt       _DMA6Interrupt     _OC13Interrupt                       */
/* _T5Interrupt       _DMA7Interrupt     _IC13Interrupt                       */
/* _INT2Interrupt     _C1TxReqInterrupt  _OC14Interrupt                       */
/* _U2RXInterrupt     _C2TxReqInterrupt  _IC14Interrupt                       */
/* _U2TXInterrupt     _QEI2Interrupt     _OC15Interrupt                       */
/* _SPI2ErrInterrupt  _U3ErrInterrupt    _IC15Interrupt                       */
/* _SPI2Interrupt     _U3RXInterrupt     _OC16Interrupt                       */
/* _C1RxRdyInterrupt  _U3TXInterrupt     _IC16Interrupt                       */
/* _C1Interrupt       _USB1Interrupt     _ICDInterrupt                        */
/* _DMA3Interrupt     _U4ErrInterrupt    _PWMSpEventMatchInterrupt            */
/* _IC3Interrupt      _U4RXInterrupt     _PWMSecSpEventMatchInterrupt         */
/*                                                                            */
/* For alternate interrupt vector naming, simply add 'Alt' between the prim.  */
/* interrupt vector name '_' and the first character of the primary interrupt */
/* vector name.  There is no Alternate Vector or 'AIVT' for the 33E family.   */
/*                                                                            */
/* For example, the vector name _ADC2Interrupt becomes _AltADC2Interrupt in   */
/* the alternate vector table.                                                */
/*                                                                            */
/* Example Syntax:                                                            */
/*                                                                            */
/* void __attribute__((interrupt,auto_psv)) <Vector Name>(void)               */
/* {                                                                          */
/*     <Clear Interrupt Flag>                                                 */
/* }                                                                          */
/*                                                                            */
/* For more comprehensive interrupt examples refer to the C30 (MPLAB C        */
/* Compiler for PIC24 MCUs and dsPIC DSCs) User Guide in the                  */
/* <C30 compiler instal directory>/doc directory for the latest compiler      */
/* release.  For XC16, refer to the MPLAB XC16 C Compiler User's Guide in the */
/* <XC16 compiler instal directory>/doc folder.                               */
/*                                                                            */
/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/


// 5 ms
void __attribute__((interrupt,auto_psv)) _T2Interrupt(void) {
    
   
    // compteurs QEI gauche et droit
    static int tics_g, tics_d;
    // commandes gauches et droite
    static float commande_g, commande_d;

    // récupération des données des compteurs qei gauche et droit
    tics_g = (int)POS1CNT;
    tics_d = (int)POS2CNT;
    // effectuer un pas de déplacement
    motion_step(tics_g,tics_d, &commande_g, &commande_d);
    // mettre ici les pwm gauche et droit
    //PWM_Moteurs(commande_g, commande_d);

   _T2IF = 0;   // on baisse le flag
}



void __attribute__((interrupt, no_auto_psv)) _SPI2Interrupt(void)
{
    led=1;
    IFS2bits.SPI2IF = 0;
}

volatile unsigned int Maxtime_Seq_AX12 = 0;

unsigned int Get_Maxtime_Seq_AX12(void)
{   return Maxtime_Seq_AX12;    }

void Set_Maxtime_Seq_AX12(unsigned int val)
{   Maxtime_Seq_AX12 = val;    }

// every ms
void __attribute__((interrupt,auto_psv)) _T3Interrupt(void) 
{
    static uint8_t Etat_Laisse = 0;
    static uint8_t Count_Laisse = 0;
    uint8_t Etat_Pin_Laisse = PIN_LAISSE;
    
    if (Etat_Pin_Laisse) {
        if (Count_Laisse < 30)
            Count_Laisse ++;
    } else {
        if (Count_Laisse)
            Count_Laisse --;
    }
    
    if (Etat_Laisse) {
        if (!Count_Laisse) {
            Etat_Laisse = 0;
            Active_Delay_90 = 1;
            Delay_90 = 0;
            SendStart();
            //Debug_Asserv_Start();
            //Debug_PWM_Start();
        }
    } else {
        if (Count_Laisse == 30) {
            Etat_Laisse = 1;
            Active_Delay_90 = 0;
            Delay_90 = 0;
        }
    }
    
    if (Delay_TimeOut_AX12) {
        Delay_TimeOut_AX12 --;
    }
    if (Maxtime_Seq_AX12) {
        Maxtime_Seq_AX12 --;
    }
    
    if (Delay_90 < 90000) {
        if (Active_Delay_90) {
            Delay_90 ++;
        } else {
            Delay_90 = 0;
        }
        Delay_90_Over = 0;
    } else if (Delay_90 == 90000) {
        Delay_90 ++;
        SendEnd();
        Delay_90_Over = 1;
    } else {
        motion_free();
        Delay_90_Over = 1;
        if (!Active_Delay_90) {
            Delay_90 = 0;
        }
    }

   _T3IF = 0;   // on baisse le flag
}


