/*
* Template dsPIC33F
* Compiler : Microchip xC16
* ÂµC : 33FJ64MC804
* Juillet 2012
*    ____________      _           _
*   |___  /| ___ \    | |         | |
*      / / | |_/ /___ | |__   ___ | |_
*     / /  |    // _ \| '_ \ / _ \| __|
*    / /   | |\ \ (_) | |_) | (_) | |_
*   /_/    |_| \_\___/|____/ \___/'\__|
*                 7robot.fr
*/

#include <uart.h>
#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>
#include <delay.h>

#include "main.h"

/******************************************************************************
 * Global Variables
 ******************************************************************************/

#define COM_AX12_IDDLE           0x00
#define COM_AX12_SENDING         0x01
#define COM_AX12_WAIT_ANSWER     0x02

volatile uint8_t Com_AX12_Status = COM_AX12_IDDLE;
volatile uint8_t Time_Since_Last_AX12_Received = 0;

uint8_t AX12_Transmit_Tab[20] = {0xFF, 0xFF, 0};
uint8_t AX12_Transmit_Goal = 0, AX12_Transmit_Ptr = 0;
uint8_t AX12_Receive_Tab[20];
uint8_t AX12_Receive_Ptr = 0;



AX12_Command Liste_Command_AX12[20];
uint8_t Command_AX12_TODO = 0, Command_AX12_DONE = 0;
uint8_t AX12_Cmd_Nb_Try = 0;


void Init_Com_AX12 (void)
{
    TRISBbits.TRISB7=1; //Pin RB7 en entrée pour les AX12
    _ODCB7 = 1; // Open drain sur la pin RB7(pour les AX12)
    
    OpenUART2(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_FLOW
        & UART_UEN_00 & UART_DIS_WAKE & UART_DIS_LOOPBACK
        & UART_DIS_ABAUD & UART_UXRX_IDLE_ONE
        & UART_BRGH_SIXTEEN
        & UART_NO_PAR_8BIT & UART_1STOPBIT,
          UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO
        & UART_SYNC_BREAK_DISABLED & UART_TX_ENABLE & UART_TX_BUF_NOT_FUL & UART_INT_RX_CHAR
        & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR,
          BRGVALAX12);

    ConfigIntUART2(UART_RX_INT_PR2 & UART_RX_INT_DIS
                 & UART_TX_INT_PR2 & UART_TX_INT_DIS);
    
    _U2TXIF = 1;    // mise à 1 du flag en prévision
    Com_AX12_Status = COM_AX12_IDDLE;
    AX12_Cmd_Nb_Try = 0;
    Time_Since_Last_AX12_Received = 0;
    
    TRIS_PIN_REMAPABLE_AX12 = 1;    // pin AX12 en IN pour remapable IN
    OPEN_DRAIN_PIN_REMAPABLE_AX12 = 1; 
    
}



/*************************************************
* TX et RX Interrupt *
*************************************************/
void __attribute__((__interrupt__, no_auto_psv)) _U2RXInterrupt(void)
{
    uint8_t valrx = ReadUART2();
    if (Com_AX12_Status == COM_AX12_WAIT_ANSWER) {
        Time_Since_Last_AX12_Received = 0;
        AX12_Receive_Tab[AX12_Receive_Ptr] = valrx;
        if (AX12_Receive_Ptr < 19)
            AX12_Receive_Ptr ++;
    }
    _U2RXIF = 0; // On baisse le FLAG
}

void __attribute__((__interrupt__, no_auto_psv)) _U2TXInterrupt(void)
{
    // tant qu'il y a des trucs à mettre
    if (AX12_Transmit_Goal != AX12_Transmit_Ptr) {
        WriteUART2(AX12_Transmit_Tab[AX12_Transmit_Ptr]);
        AX12_Transmit_Ptr ++;
        _U2TXIF = 0; // clear TX interrupt flag
    } else {
        // desactive l'IT TX, passe en RX, active l'IT RX
        Com_AX12_Status = COM_AX12_WAIT_ANSWER;
        IEC1bits.U2TXIE = 0;
        Set_AX12_RX();
        ReadUART2();        // juste pour vider les buffer
        AX12_Receive_Ptr = 0;
        Time_Since_Last_AX12_Received = 0;
        _U2RXIF = 0;
        IEC1bits.U2RXIE = 1;
    }
}

/******************************************************************************
 * Wiring dependent functions, that you should customize
 ******************************************************************************/

// du coup, le bit IOLOCK est à 0 au reset du pic,
// donc on va pas y toucher, ça permet de tout faire marcher facile....
void Set_AX12_TX() {
    _U2RXR = 31;                        // disable RX
    PIN_REMAPABLE_AX12_OUT = 0b00101;   // RP10 = U2TX (p.167)      TX => RP10
}

void Set_AX12_RX() {
    _U2RXR = PIN_REMAPABLE_AX12_IN;     // RP10 = U2RX (p.165)      RX <= RP10
    PIN_REMAPABLE_AX12_OUT = 0;         // disable TX

}

// fonction a mettre dans le timer ms
void AX12_Every_ms (void)
{
    uint8_t i, val8, error;
    if (Com_AX12_Status == COM_AX12_IDDLE) {        // si au repos
        if (Command_AX12_TODO != Command_AX12_DONE) {       // si nouvel ordre à faire
            if ((Liste_Command_AX12[Command_AX12_DONE].Command == AX_INST_READ_DATA) || // si ce nouvel ordre est supporté (read ou write)
                (Liste_Command_AX12[Command_AX12_DONE].Command == AX_INST_WRITE_DATA) ) {
                AX12_Transmit_Tab [0] = 0xFF;
                AX12_Transmit_Tab [1] = 0xFF;
                AX12_Transmit_Tab [2] = Liste_Command_AX12[Command_AX12_DONE].AX12_Addr;
                // la longueur du packet, dans le 3, après :

                AX12_Transmit_Tab [4] = Liste_Command_AX12[Command_AX12_DONE].Command;
                AX12_Transmit_Tab [5] = Liste_Command_AX12[Command_AX12_DONE].Reg_Addr;
                
                if (Liste_Command_AX12[Command_AX12_DONE].Command == AX_INST_WRITE_DATA) {
                    for (i = 0; i < Liste_Command_AX12[Command_AX12_DONE].Nb_Data; i++) {
                        AX12_Transmit_Tab [6+i] = Liste_Command_AX12[Command_AX12_DONE].Data[i];
                    }
                    AX12_Transmit_Tab [3] = Liste_Command_AX12[Command_AX12_DONE].Nb_Data + 3;  // ID + CMD + REG + x*datas
                    
                } else if (Liste_Command_AX12[Command_AX12_DONE].Command == AX_INST_READ_DATA) {
                    AX12_Transmit_Tab [6] = Liste_Command_AX12[Command_AX12_DONE].Nb_Data;
                    AX12_Transmit_Tab [3] = 4;             // ID + CMD + Addr_Reg + Nb data to read
                }
                
                AX12_Transmit_Goal = AX12_Transmit_Tab [3] + 4; //  2*FF + Len + [] + chksum
                
                val8 = 0;
                for (i = 2; i < AX12_Transmit_Goal-2; i++) {
                    val8 += AX12_Transmit_Tab[i];
                }
                AX12_Transmit_Tab[AX12_Transmit_Goal-1] = !val8;
                
                AX12_Transmit_Ptr = 0;
                Set_AX12_TX();
                Com_AX12_Status = COM_AX12_SENDING;
                AX12_Cmd_Nb_Try = 0;
                _U2TXIF = 0;
                WriteUART2(AX12_Transmit_Tab[AX12_Transmit_Ptr++]);
                IEC1bits.U2TXIE = 1;
                
            } else {    // si la commande n'est pas suportée par le système
                *Liste_Command_AX12[Command_AX12_DONE].Done = 1;
                Command_AX12_DONE ++;
                if (Command_AX12_DONE == 20)
                    Command_AX12_DONE = 0;
            }
        }
    } else if (Com_AX12_Status == COM_AX12_WAIT_ANSWER) {        // si en reception
        Time_Since_Last_AX12_Received ++;
        if (Time_Since_Last_AX12_Received > 5) {            // on attend 5 ms pour considerer la fin de la liaison
            error = 1;  // on dit que c'est en erreur
            if ( (AX12_Receive_Ptr > 6)  &&                 //si on a recu assez pour faire un paquet
                 (AX12_Receive_Tab[3] == (AX12_Receive_Ptr - 4) ) ) {    // et que la longeur est cohérente
                // calcul du checksum
                val8 = 0;
                for (i = 2; i < (AX12_Receive_Tab[3] + 2); i++)
                    val8 += AX12_Receive_Tab[i];
                // vérif si checksum est bon
                if (val8 == !AX12_Receive_Tab[AX12_Receive_Ptr-1])
                    error = 0;
            }
            if (!error) {   // si le transfert s'est bien passé
                if (Liste_Command_AX12[Command_AX12_DONE].Command == AX_INST_READ_DATA) {   // en cas de lecture, on transfere la donnée là ou c'est demandé
                    for (i = 0; i < Liste_Command_AX12[Command_AX12_DONE].Nb_Data; i++)
                        Liste_Command_AX12[Command_AX12_DONE].Data[i] = AX12_Receive_Tab[i+5];
                }
                *Liste_Command_AX12[Command_AX12_DONE].Status = AX12_Receive_Tab[4];
                *Liste_Command_AX12[Command_AX12_DONE].Done = 1;
                AX12_Cmd_Nb_Try = 0;
            } else {
                AX12_Cmd_Nb_Try++;
                if (AX12_Cmd_Nb_Try > AX12_CMD_NB_MAX_TRY_SEND) {
                    *Liste_Command_AX12[Command_AX12_DONE].Status = 0x80;   // code d'erreur
                    *Liste_Command_AX12[Command_AX12_DONE].Done = 1;
                    error = 0;  // pour forcer à passer à la suite
                }
            }
            
            // traitement fait
            Com_AX12_Status = COM_AX12_IDDLE;
            if (!error) {
                Command_AX12_DONE ++;
                if (Command_AX12_DONE == 20)
                    Command_AX12_DONE = 0;
            }
        }
    }
}


/******************************************************************************
 * Convenience Functions
 ******************************************************************************/

byte RegisterLenAX(byte address) {
    switch (address) {
        case  2: case  3: case  4: case  5: case 11: case 12: case 13: case 16:
        case 17: case 18: case 19: case 24: case 25: case 26: case 27: case 28:
        case 29: case 42: case 43: case 44: case 46: case 47:
            return 1;
            break;
        case  0: case  6: case  8: case 14: case 20: case 22: case 30: case 32:
        case 34: case 36: case 38: case 40: case 48:
            return 2;
            break;
    }
    return 0; // Unexpected.
}

void Add_AX12_Cmd (uint8_t AX12_Addr, uint8_t Command, uint8_t Reg_Addr, uint8_t *Data, uint8_t Nb_Data, uint8_t *Status, uint8_t *Done)
{
    Liste_Command_AX12[Command_AX12_TODO].AX12_Addr = AX12_Addr;
    Liste_Command_AX12[Command_AX12_TODO].Command   = Command;
    Liste_Command_AX12[Command_AX12_TODO].Reg_Addr  = Reg_Addr;
    Liste_Command_AX12[Command_AX12_TODO].Data      = Data;
    Liste_Command_AX12[Command_AX12_TODO].Nb_Data   = Nb_Data;
    Liste_Command_AX12[Command_AX12_TODO].Status    = Status;
    Liste_Command_AX12[Command_AX12_TODO].Done      = Done;
    
    Command_AX12_TODO ++;
    if (Command_AX12_TODO == 20)
        Command_AX12_TODO = 0;
}

void Send_AX(uint8_t id, uint8_t Reg, uint16_t Data)
{
    uint8_t Done = 0, Status;
    uint8_t Data_tab[2];
    Data_tab[0] = Data & 0xFF;
    Data_tab[1] = Data >> 8;
    Add_AX12_Cmd (id, AX_INST_WRITE_DATA, Reg, &Data_tab[0], RegisterLenAX(Reg), &Status, &Done);
    while(!Done);
}

