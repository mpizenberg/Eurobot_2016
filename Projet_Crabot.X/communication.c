/*
 * Template dsPIC33F
 * Compiler : Microchip xC16
 * µC : 33FJ128MC804
 * Avril 2016
 *
 *    ______ _____      _           _
 *   |___  /| ___ \    | |         | |
 *      / / | |_/ /___ | |__   ___ | |_
 *     / /  |    // _ \| '_ \ / _ \| __|
 *    / /   | |\ \ (_) | |_) | (_) | |_
 *   /_/    |_| \_\___/|____/ \___/'\__|
 *			      7robot.fr
 */

#include <uart.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "uart.h"

char ReceivedStringFromPi[SIZE_BUFFER_COM] = {0};
int CharFromPiNumber = 0;
volatile char Buffer_To_Send[SIZE_BUFFER_COM] = {0};
volatile char Last_Buffer_To_Send[SIZE_BUFFER_COM] = {0};
volatile int Buffer_To_Send_TODO = 0, Buffer_To_Send_DONE = 0;
volatile int try = 1;

void Init_Communication_RasPi(void)
{
        OpenUART1(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_FLOW
        & UART_UEN_00 & UART_DIS_WAKE & UART_DIS_LOOPBACK
        & UART_DIS_ABAUD & UART_UXRX_IDLE_ONE & UART_BRGH_SIXTEEN
        & UART_NO_PAR_8BIT & UART_1STOPBIT,
          UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO
        & UART_SYNC_BREAK_DISABLED & UART_TX_ENABLE & UART_TX_BUF_NOT_FUL & UART_INT_RX_CHAR
        & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR,
          BRGVALRASPI);


    ConfigIntUART1(UART_RX_INT_PR6 & UART_RX_INT_EN
                 & UART_TX_INT_PR6 & UART_TX_INT_DIS);
    
    Buffer_To_Send_TODO = 0;
    Buffer_To_Send_DONE = 0;
    
    // init
    //_U1TXIF = 1;
        //Remapage uart 1
    _U1RXR = 18;
    _RP4R = 0b0011;  // RP4 = U1TX (p.167)
    
}


void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void){
    // Receive Byte
    char b = ReadUART1();
    AnalyzeCommandFromPi(b);
    _U1RXIF = 0; // On baisse le FLAG
}

void __attribute__((__interrupt__, no_auto_psv)) _U1TXInterrupt(void){
//    if (try) {
//        _U1TXIF = 0; // clear TX interrupt flag
//        U1TXREG = Buffer_To_Send[Buffer_To_Send_DONE];
//
//        Buffer_To_Send_DONE ++;
//        if (Buffer_To_Send_DONE == SIZE_BUFFER_COM)
//            Buffer_To_Send_DONE = 0;
//
//        if (Buffer_To_Send_DONE == Buffer_To_Send_TODO) {
//            _U1TXIE = 0;    // 
//        }
//    }
//    else {
        _U1TXIF = 0; // clear TX interrupt flag
//    }
}


void AnalyzeCommandFromPi (char b)
{
    // If byte is "$" symbol, the string can be valid
    if (b == '$')
    {
        ReceivedStringFromPi[0] = '$';
        CharFromPiNumber = 1;
    }
    // Here we are collecting all the char from the frame
    else if (CharFromPiNumber) {
        if (CharFromPiNumber == SIZE_BUFFER_COM) {
            CharFromPiNumber = 0;  // commande trop longue => on la drope, retourne attendre le prochain '$'
        } else if (b == ';') {     // si on a reçu le carractère de fin...
            ReceivedStringFromPi[CharFromPiNumber] = ';';
            CharFromPiNumber = 0;
            SelectActionFromPi();
        } else {
            ReceivedStringFromPi[CharFromPiNumber] = b;
            CharFromPiNumber++;
        }
    }
}

void SelectActionFromPi(void)
{
    int cursorPosition, floatLength;
    float ANGLE;
    float valf;
    Position MOVE;
    Speed VITESSE;
    //uint8_t val8;
    char valc;
    int vali;
    
    
    //**************************************************************************//
    //************** PARTIE ORDRES MOUVEMENTS **********************************//
    //**************************************************************************//
    if (!Delay_90_Over) {
        // MOVE
        if(ReceivedStringFromPi[1]=='M' 
		&& ReceivedStringFromPi[2]=='O' 
		&& ReceivedStringFromPi[3]=='V' 
		&& ReceivedStringFromPi[4]=='E')
        {
            cursorPosition=6;
            for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=',';floatLength++); // Return the number of char taken by the float in the command line
            ReceivedStringFromPi[cursorPosition+floatLength] = 0;
            MOVE.x = atof(&ReceivedStringFromPi[cursorPosition]);
            ReceivedStringFromPi[cursorPosition+floatLength] = ',';

            cursorPosition+=floatLength+1;
            for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=',';floatLength++); // Return the number of char taken by the float in the command line
            ReceivedStringFromPi[cursorPosition+floatLength] = 0;
            MOVE.y = atof(&ReceivedStringFromPi[cursorPosition]);
            ReceivedStringFromPi[cursorPosition+floatLength] = ',';

            cursorPosition+=floatLength+1;
            for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=';';floatLength++); // Return the number of char taken by the float in the command line
            ReceivedStringFromPi[cursorPosition+floatLength] = 0;
            MOVE.t = atof(&ReceivedStringFromPi[cursorPosition]);
            ReceivedStringFromPi[cursorPosition+floatLength] = ';';

            motion_pos(MOVE);
        }
        
        // PUSH
        if(ReceivedStringFromPi[1]=='P' 
		&& ReceivedStringFromPi[2]=='U' 
		&& ReceivedStringFromPi[3]=='S' 
		&& ReceivedStringFromPi[4]=='H')
        {
            cursorPosition=6;
            for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=',';floatLength++); // Return the number of char taken by the float in the command line
            ReceivedStringFromPi[cursorPosition+floatLength] = 0;
            MOVE.x = atof(&ReceivedStringFromPi[cursorPosition]);
            ReceivedStringFromPi[cursorPosition+floatLength] = ',';

            cursorPosition+=floatLength+1;
            for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=',';floatLength++); // Return the number of char taken by the float in the command line
                ReceivedStringFromPi[cursorPosition+floatLength] = 0;
            MOVE.y = atof(&ReceivedStringFromPi[cursorPosition]);
            ReceivedStringFromPi[cursorPosition+floatLength] = ',';

            cursorPosition+=floatLength+1;
            for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=',';floatLength++); // Return the number of char taken by the float in the command line
            ReceivedStringFromPi[cursorPosition+floatLength] = 0;
            MOVE.t = atof(&ReceivedStringFromPi[cursorPosition]);
            ReceivedStringFromPi[cursorPosition+floatLength] = ',';
            cursorPosition+=floatLength+1;
            
            for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=';';floatLength++); // Return the number of char taken by the float in the command line
            ReceivedStringFromPi[cursorPosition+floatLength] = 0;
            valf = atof(&ReceivedStringFromPi[cursorPosition]);
            ReceivedStringFromPi[cursorPosition+floatLength] = ';';

            motion_push(MOVE, valf);
        }
        
        // SPED
        if(ReceivedStringFromPi[1]=='S' 
		&& ReceivedStringFromPi[2]=='P' 
		&& ReceivedStringFromPi[3]=='E' 
		&& ReceivedStringFromPi[4]=='D')
        {
            cursorPosition=6;
            for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=',';floatLength++); // Return the number of char taken by the float in the command line
            ReceivedStringFromPi[cursorPosition+floatLength] = 0;
            VITESSE.v = atof(&ReceivedStringFromPi[cursorPosition]);
            ReceivedStringFromPi[cursorPosition+floatLength] = ',';
            
            cursorPosition+=floatLength+1;
            for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=',';floatLength++); // Return the number of char taken by the float in the command line
            ReceivedStringFromPi[cursorPosition+floatLength] = 0;
            VITESSE.vt = atof(&ReceivedStringFromPi[cursorPosition]);
            ReceivedStringFromPi[cursorPosition+floatLength] = ';';
            
            
            motion_linear_speed(VITESSE);
        }


        // ANGL
        if(ReceivedStringFromPi[1]=='A' 
		&& ReceivedStringFromPi[2]=='N' 
		&& ReceivedStringFromPi[3]=='G' 
		&& ReceivedStringFromPi[4]=='L')
        {
            cursorPosition=6;

            for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=';';floatLength++); // Return the number of char taken by the float in the command line
            ReceivedStringFromPi[cursorPosition+floatLength] = 0;
            ANGLE = atof(&ReceivedStringFromPi[cursorPosition]);
            ReceivedStringFromPi[cursorPosition+floatLength] = ';';

            motion_angle(ANGLE);
        }
        
    }
    
    // FREE
    if(ReceivedStringFromPi[1]=='F' 
    && ReceivedStringFromPi[2]=='R' 
    && ReceivedStringFromPi[3]=='E' 
    && ReceivedStringFromPi[4]=='E')
    {
        motion_free();
    }
    
    //**************************************************************************//
    //************** PARTIE RECALAGES DES POSITIONS ****************************//
    //**************************************************************************//
    // SET
    if(ReceivedStringFromPi[1]=='S' 
    && ReceivedStringFromPi[2]=='E' 
    && ReceivedStringFromPi[3]=='T')
    {
        // SETX
        if (ReceivedStringFromPi[4]=='X')
        {
            cursorPosition=6;

            for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=';';floatLength++); // Return the number of char taken by the float in the command line
            ReceivedStringFromPi[cursorPosition+floatLength] = 0;
            valf = atof(&ReceivedStringFromPi[cursorPosition]);
            ReceivedStringFromPi[cursorPosition+floatLength] = ';';

            set_position_x(valf);
        }
        // SETY
        else if (ReceivedStringFromPi[4]=='Y')
        {
            cursorPosition=6;

            for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=';';floatLength++); // Return the number of char taken by the float in the command line
            ReceivedStringFromPi[cursorPosition+floatLength] = 0;
            valf = atof(&ReceivedStringFromPi[cursorPosition]);
            ReceivedStringFromPi[cursorPosition+floatLength] = ';';

            set_position_y(valf);
        }
        // SETA
        else if(ReceivedStringFromPi[4]=='A')
        {
            cursorPosition=6;

            for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=';';floatLength++); // Return the number of char taken by the float in the command line
            ReceivedStringFromPi[cursorPosition+floatLength] = 0;
            valf = atof(&ReceivedStringFromPi[cursorPosition]);
            ReceivedStringFromPi[cursorPosition+floatLength] = ';';

            set_position_t(valf);
        }
                
    }
        
    
    
    //**************************************************************************//
    //************** PARTIE LIMITES DE VITESSES, ACCELERATIONS... **************//
    //**************************************************************************//
    
    // VMAX     choisi une vitesse max
    if(ReceivedStringFromPi[1]=='V' 
    && ReceivedStringFromPi[2]=='M' 
    && ReceivedStringFromPi[3]=='A' 
    && ReceivedStringFromPi[4]=='X')
    {
        cursorPosition=6;
        for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=';';floatLength++); // Return the number of char taken by the float in the command line
        ReceivedStringFromPi[cursorPosition+floatLength] = 0;
        valf = atof(&ReceivedStringFromPi[cursorPosition]);
        ReceivedStringFromPi[cursorPosition+floatLength] = ';';
        set_Constraint_vitesse_max(valf);
    }

    // VTMA     choisi une vitesse angulaire max
    if(ReceivedStringFromPi[1]=='V'
    && ReceivedStringFromPi[2]=='T'
    && ReceivedStringFromPi[3]=='M'
    && ReceivedStringFromPi[4]=='A')
    {
        cursorPosition=6;
        for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=';';floatLength++); // Return the number of char taken by the float in the command line
        ReceivedStringFromPi[cursorPosition+floatLength] = 0;
        valf = atof(&ReceivedStringFromPi[cursorPosition]);
        ReceivedStringFromPi[cursorPosition+floatLength] = ';';
        set_Constraint_vt_max(valf);
    }

    // AMAX     choisi une acceleration max pour des mouvements 'doux'
    if(ReceivedStringFromPi[1]=='A'
    && ReceivedStringFromPi[2]=='M'
    && ReceivedStringFromPi[3]=='A'
    && ReceivedStringFromPi[4]=='X')
    {
        cursorPosition=6;
        for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=',';floatLength++); // Return the number of char taken by the float in the command line
        ReceivedStringFromPi[cursorPosition+floatLength] = 0;
        float al_max = atof(&ReceivedStringFromPi[cursorPosition]);
        ReceivedStringFromPi[cursorPosition+floatLength] = ',';

        cursorPosition+=floatLength+1;
        for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=',';floatLength++); // Return the number of char taken by the float in the command line
            ReceivedStringFromPi[cursorPosition+floatLength] = 0;
        float at_max = atof(&ReceivedStringFromPi[cursorPosition]);
        ReceivedStringFromPi[cursorPosition+floatLength] = ',';

        cursorPosition+=floatLength+1;
        for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=',';floatLength++); // Return the number of char taken by the float in the command line
        ReceivedStringFromPi[cursorPosition+floatLength] = 0;
        float a_max = atof(&ReceivedStringFromPi[cursorPosition]);
        ReceivedStringFromPi[cursorPosition+floatLength] = ',';
        cursorPosition+=floatLength+1;

        set_Constraint_acceleration_max(al_max, at_max, a_max);
    }
        
        

    // INIT
    if(ReceivedStringFromPi[1]=='I' 
    && ReceivedStringFromPi[2]=='N' 
    && ReceivedStringFromPi[3]=='I' 
    && ReceivedStringFromPi[4]=='T')
    {   Init_All(1);    }
    
    
    //**************************************************************************//
    //************** PARTIE ACTIONS AX12 ***************************************//
    //**************************************************************************//
    
    // AXIN
    if(ReceivedStringFromPi[1]=='A' 
    && ReceivedStringFromPi[2]=='X' 
    && ReceivedStringFromPi[3]=='I' 
    && ReceivedStringFromPi[4]=='N')
    {   Add_Action_AX12(AX12_INIT_AX12);    }
    
    // DF       // Deploy
    if(ReceivedStringFromPi[1]=='D' 
    && ReceivedStringFromPi[2]=='F') {
        // DFA
        if (ReceivedStringFromPi[3]=='A') {
            // DFAV
            if (ReceivedStringFromPi[4]=='V')
            {   Add_Action_AX12(AX12_DEPLOY_FISH_AV);   }
            // DFAR
            else if (ReceivedStringFromPi[4]=='R')
            {   Add_Action_AX12(AX12_DEPLOY_FISH_AR);   }
        }
        // DFIS
        else if (ReceivedStringFromPi[3]=='I'
              && ReceivedStringFromPi[4]=='S')
        {   Add_Action_AX12(AX12_DEPLOY_FISH);  }
    }
    
    // UP  
    if(ReceivedStringFromPi[1]=='U'
    && ReceivedStringFromPi[2]=='P') {
        // UPA
        if(ReceivedStringFromPi[3]=='A') {
            // UPAV
            if (ReceivedStringFromPi[4]=='V')
            {   Add_Action_AX12(AX12_MOVEUP_FISH_AV);   }
            // UPAR
            else if(ReceivedStringFromPi[4]=='R')
            {   Add_Action_AX12(AX12_MOVEUP_FISH_AR);   }
        }
    }
    
    // RF   // Release Fish
    if(ReceivedStringFromPi[1]=='R' 
    && ReceivedStringFromPi[2]=='F') {
        // RFA
        if(ReceivedStringFromPi[3]=='A') {
            if (ReceivedStringFromPi[4]=='V')
            {   Add_Action_AX12(AX12_RLZ_FISH_AV);  }
            // RFAR
            else if(ReceivedStringFromPi[4]=='R')
            {   Add_Action_AX12(AX12_RLZ_FISH_AR);  }
        }
        // RFIS (All Fish)
        else if (ReceivedStringFromPi[3]=='I'
              && ReceivedStringFromPi[4]=='S')
        {   Add_Action_AX12(AX12_RLZ_FISH); }
    }
    
    // OP   // OPEN BRAS
    if(ReceivedStringFromPi[1]=='O' 
    && ReceivedStringFromPi[2]=='P') {
        // OPNB
        if(ReceivedStringFromPi[3]=='N' 
        && ReceivedStringFromPi[4]=='B')
        {   Add_Action_AX12(AX12_OPEN_BRAS);    }
        // OPFB
        else if(ReceivedStringFromPi[3]=='F' 
             && ReceivedStringFromPi[4]=='B')
        {   Add_Action_AX12(AX12_OPENFULL_BRAS);    }
    }
    
    // CATB
    if(ReceivedStringFromPi[1]=='C'
    && ReceivedStringFromPi[2]=='A'
    && ReceivedStringFromPi[3]=='T'
    && ReceivedStringFromPi[4]=='B')
    {   Add_Action_AX12(AX12_CATCH_BRAS);   }

    // CLOB
    if(ReceivedStringFromPi[1]=='C' 
    && ReceivedStringFromPi[2]=='L' 
    && ReceivedStringFromPi[3]=='O' 
    && ReceivedStringFromPi[4]=='B')
    {   Add_Action_AX12(AX12_CLOSE_BRAS);   }
        
    
    // FUNA
    if(ReceivedStringFromPi[1]=='F' 
    && ReceivedStringFromPi[2]=='U' 
    && ReceivedStringFromPi[3]=='N' 
    && ReceivedStringFromPi[4]=='A')
    {   Add_Action_AX12(AX12_FUNNY_ACTION); }
    
    
    //**************************************************************************//
    //************** PARTIE SICKS **********************************************//
    //**************************************************************************//
//    // SIK?			// demande status sick
//    if(ReceivedStringFromPi[1]=='S' 
//    && ReceivedStringFromPi[2]=='I' 
//    && ReceivedStringFromPi[3]=='K' 
//    && ReceivedStringFromPi[4]=='?')
//    {
//        val8 = ReceivedStringFromPi[6] -48; // traduction décimal - ascii : 48 en ascii  = 0
//        if (val8 >= NUMBER_OF_SICK) {
//                val8 = 0;
//        }
//        //__delay_ms(10);
//        SendSick_Status(val8);
//        //__delay_ms(10);
//    }
//
//    // DBSI			// start/stop debug sick
//    if(ReceivedStringFromPi[1]=='D' 
//    && ReceivedStringFromPi[2]=='B' 
//    && ReceivedStringFromPi[3]=='S' 
//    && ReceivedStringFromPi[4]=='I')
//    {   Start_Stop_Debug_Sick();    }

    // ENSI         // active ou pas le motion_free des sicks  à l'unitée
    if(ReceivedStringFromPi[1]=='E' 
    && ReceivedStringFromPi[2]=='N' 
    && ReceivedStringFromPi[3]=='S' 
    && ReceivedStringFromPi[4]=='I')
    {
        // l'utilisateur a juste droit à de 0 à F
        valc = ReceivedStringFromPi[6];
        if (valc >= '0' && valc <= '9') {
            vali = valc - '0';
        } else if (valc >= 'A' && valc <= 'F') {
            vali = valc - 'A' + 10;
        } else {
            vali = 0x0F;
        }
        Choose_Enabled_Sicks(vali);
    }
//    
//    // ULS?			// demande status sick
//    if(ReceivedStringFromPi[1]=='U' 
//    && ReceivedStringFromPi[2]=='L' 
//    && ReceivedStringFromPi[3]=='S' 
//    && ReceivedStringFromPi[4]=='?')
//    {   SendUltrason_Status();  }

    
    
    
    //**************************************************************************//
    //************** PARTIE AUTRES MOUVEMENTS **********************************//
    //**************************************************************************//
    // TEAM
    if(ReceivedStringFromPi[1]=='T' 
    && ReceivedStringFromPi[2]=='E' 
    && ReceivedStringFromPi[3]=='A' 
    && ReceivedStringFromPi[4]=='M')
    {   SendTeam(PIN_TEAM); }
    
    // CONF
    if(ReceivedStringFromPi[1]=='C' 
    && ReceivedStringFromPi[2]=='O' 
    && ReceivedStringFromPi[3]=='N' 
    && ReceivedStringFromPi[4]=='F')
    {   SendNum_Config(); }


    // VBAT			// récupère la tension baterie
    if(ReceivedStringFromPi[1]=='V' 
    && ReceivedStringFromPi[2]=='B' 
    && ReceivedStringFromPi[3]=='A' 
    && ReceivedStringFromPi[4]=='T')
    {
        //__delay_ms(10);
        printf("$VBAT,%d;", Get_VBat());
        //__delay_ms(10);
    }
    
//    // DBUS			// start/stop debug ultrason
//    if(ReceivedStringFromPi[1]=='D' 
//    && ReceivedStringFromPi[2]=='B' 
//    && ReceivedStringFromPi[3]=='U' 
//    && ReceivedStringFromPi[4]=='S')
//    {   Start_Stop_Debug_Ultrason();    }
//        
//    // DTUS			// change la distance de detection des ultrasons
//    if(ReceivedStringFromPi[1]=='D'
//    && ReceivedStringFromPi[2]=='T'
//    && ReceivedStringFromPi[3]=='U'
//    && ReceivedStringFromPi[4]=='S')
//    {
//        cursorPosition = 6;
//        for(floatLength=0;ReceivedStringFromPi[cursorPosition+floatLength]!=';';floatLength++); // Return the number of char taken by the float in the command line
//        ReceivedStringFromPi[cursorPosition+floatLength] = 0;
//        valf = atof(&ReceivedStringFromPi[cursorPosition]);
//        ReceivedStringFromPi[cursorPosition+floatLength] = ';';
//        Set_Threshold_US(valf*1000);
//    }
//
//    // ENUS         // active ou pas le motion_free de l'ultrason
//    if(ReceivedStringFromPi[1]=='E' 
//    && ReceivedStringFromPi[2]=='N' 
//    && ReceivedStringFromPi[3]=='U' 
//    && ReceivedStringFromPi[4]=='S')
//    {
//        valc = ReceivedStringFromPi[6];
//        if (valc >= '0' && valc <= '3') {
//            valc -= '0';
//            Choose_Enabled_US(valc);
//        }
    
}

void SendDone(void)
{
    //__delay_ms(50);
	Raz_Delay_WatchDone();
    //Add_String_To_Send_Buff("$DONE;");
    printf("$DONE;");
    //__delay_ms(50);
}

void SendStart(void)
{
    //__delay_ms(50);
    //Add_String_To_Send_Buff("$STRT;");
    printf("$STRT;");
    //__delay_ms(50);
}

void SendEnd (void)
{
    //__delay_ms(10);
    printf("$END9;");
    //Add_String_To_Send_Buff("$END9;");
    //__delay_ms(10);
}

void SendFailAX12(void)
{
    //__delay_ms(10);
    printf("$FAAX;");
    //Add_String_To_Send_Buff("$FAAX;");
    //__delay_ms(10);
}

void DetectSick(int channel)
{
//    char loc_str[20];
//    sprintf(loc_str, "$DSI%d;", channel);
//    Add_String_To_Send_Buff(&loc_str[0]);
    printf("$DSI%d;", channel);
}

void ReleaseSick (int channel)
{
//    char loc_str[20];
//    sprintf(loc_str, "$RSI%d;", channel);
//    Add_String_To_Send_Buff(&loc_str[0]);
    printf("$RSI%d;", channel);
}

void SendSick_Status(int val8)
{
    //__delay_ms(50);
//    char loc_str[40];
//    sprintf(loc_str, "$SICK,%d,%d,%d;", val8, Get_Sick(val8), Get_Sick_Sector(val8) );
//    Add_String_To_Send_Buff(&loc_str[0]);
    printf("$SICK,%d,%d,%d;", val8, Get_Sick(val8), Get_Sick_Sector(val8) );
	//__delay_ms(50);
}

void DetectUltrason(void)
{
    //Add_String_To_Send_Buff("$DULS;");
    printf("$DULS;");
}

void ReleaseUltrason(void)
{
    //Add_String_To_Send_Buff("$RULS;");
    printf("$RULS;");
}

void SendUltrason_Status(void)
{
    //__delay_ms(50);
    //printf("$SULS,%d,%d,%d;", Sector_Ultrason, Mesure_Distance_Ultrason, Mesure_Timer_Ultrason);
//    char loc_str[30];
//    sprintf(loc_str, "$SULS,%d,%d,%d;", 0, 0, 0);
//    Add_String_To_Send_Buff(&loc_str[0]);
    printf("$SULS,%d,%d,%d;", 0, 0, 0);
    //__delay_ms(50);
}

void SendTeam (int team)
{
    //__delay_ms(50);
//    switch(team) {
//        case 0 : Add_String_To_Send_Buff("$VERT;");  break;
//        case 1 : Add_String_To_Send_Buff("$VIOL;");  break;
//    }
    switch(team) {
        case 0 : printf("$VERT;");  break;
        case 1 : printf("$VIOL;");  break;
    }
    //__delay_ms(50);
}

void SendNum_Config (void)
{
//    char loc_str[20];
    printf("$CON%d;", Get_Number_Config());
    //Add_String_To_Send_Buff(&loc_str[0]);
    //sprintf(loc_str, "$CON%d;", Get_Number_Config());
    //Add_String_To_Send_Buff(&loc_str[0]);
}

void SendUrge(void){
    //Add_String_To_Send_Buff ("$URGE;");
    printf ("$URGE;");
}


void Add_String_To_Send_Buff (char *string)
{
    /*
    int sended = 0;
    int i = 0;
    _U1TXIE = 0;    // mise en pause de la transmission
    while (*string) {
        //Buffer_To_Send_DONE
        Buffer_To_Send[Buffer_To_Send_TODO] = *string;
        Last_Buffer_To_Send[i] = *string;
        i++;
        Buffer_To_Send_TODO++;
        if (Buffer_To_Send_TODO == SIZE_BUFFER_COM)
            Buffer_To_Send_TODO = 0;
        string++;
        sended = 1;
    }
    if (sended) {
        sended++;
        sended++;
        sended++;
        _U1TXIE = 1;
    }
    */
}