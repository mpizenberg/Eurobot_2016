#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <stdio.h>
#include <uart.h>
#include <delay.h>

#include "main.h"


#define maxtork_claw 650
#define maxspeed_claw 800
#define delay_ax 30

/******************************************************************************/
/*************************** Arm Specification ********************************/
/******************************************************************************/


/******************************************************************************/
/****************************** Init Position *********************************/
/******************************************************************************/

volatile int Num_Action_Done = 0;
volatile int Num_Action_ToDo = 0;
volatile char Tab_Actions_ToDo [NUM_ACTIONS_BUFFER] = {0};

void Add_Action_AX12(char Action_ToDo)
{
    int num = Num_Action_ToDo;
    num++;
    if (num == NUM_ACTIONS_BUFFER) {
        num = 0;
    }
    Tab_Actions_ToDo[num] = Action_ToDo;
    Num_Action_ToDo = num;
}

void Faire_Actions_AX12(void)
{
    int num = Num_Action_Done;
    char Action_ToDo;
    if (num != Num_Action_ToDo && !Delay_90_Over) {
        num++;
        if (num == NUM_ACTIONS_BUFFER) {
            num = 0;
        }
        Action_ToDo = Tab_Actions_ToDo[num];
        switch (Action_ToDo)
        {
            case AX12_INIT_AX12 :
                Init_ax12();
                break;
            case AX12_DEPLOY_FISH_AV :
                Deploy_fish_Av();
                break;
            case AX12_DEPLOY_FISH_AR :
                Deploy_fish_Ar();
                break;
            case AX12_RLZ_FISH_AV:
                Rlz_fish_Av();
                break;
            case AX12_RLZ_FISH_AR:
                Rlz_fish_Ar();
                break;
            case AX12_OPEN_BRAS:
                Open_bras();
                break;
            case AX12_OPENFULL_BRAS:
                Openfull_bras();
                break;
            case AX12_CLOSE_BRAS:
                Close_bras();
                break;
        }
        Num_Action_Done = num;
    }
}


void Init_ax12() {

    PutAX(Fish_AvG, 	AX_TORQUE_LIMIT, maxtork_claw);
						__delay_ms(delay_ax);
    PutAX(Fish_AvD, 	AX_TORQUE_LIMIT, maxtork_claw);
						__delay_ms(delay_ax);
	PutAX(Fish_ArG, 	AX_TORQUE_LIMIT, maxtork_claw);
						__delay_ms(delay_ax);
	PutAX(Fish_ArD, 	AX_TORQUE_LIMIT, maxtork_claw);
						__delay_ms(delay_ax);
	PutAX(Magnet_AvG, 	AX_TORQUE_LIMIT, maxtork_claw);
						__delay_ms(delay_ax);
        PutAX(Magnet_AvD, 	AX_TORQUE_LIMIT, maxtork_claw);
						__delay_ms(delay_ax);
	PutAX(Magnet_ArG, 	AX_TORQUE_LIMIT, maxtork_claw);
						__delay_ms(delay_ax);
	PutAX(Magnet_ArD, 	AX_TORQUE_LIMIT, maxtork_claw);
						__delay_ms(delay_ax);
	PutAX(Bras_G, 		AX_TORQUE_LIMIT, maxtork_claw);
						__delay_ms(delay_ax);
	PutAX(Bras_C, 		AX_TORQUE_LIMIT, maxtork_claw);
						__delay_ms(delay_ax);	
	PutAX(Bras_D, 		AX_TORQUE_LIMIT, maxtork_claw);
						__delay_ms(delay_ax);
	PutAX(Bras_parasol, AX_TORQUE_LIMIT, maxtork_claw);
						__delay_ms(delay_ax);
	
	PutAX(Fish_AvG, 	AX_MOVING_SPEED, maxspeed_claw);
						__delay_ms(delay_ax);
        PutAX(Fish_AvD, 	AX_MOVING_SPEED, maxspeed_claw);
						__delay_ms(delay_ax);
	PutAX(Fish_ArG, 	AX_MOVING_SPEED, maxspeed_claw);
						__delay_ms(delay_ax);
	PutAX(Fish_ArD, 	AX_MOVING_SPEED, maxspeed_claw);
						__delay_ms(delay_ax);
	PutAX(Magnet_AvG, 	AX_MOVING_SPEED, maxspeed_claw);
						__delay_ms(delay_ax);
        PutAX(Magnet_AvD, 	AX_MOVING_SPEED, maxspeed_claw);
						__delay_ms(delay_ax);
	PutAX(Magnet_ArG, 	AX_MOVING_SPEED, maxspeed_claw);
						__delay_ms(delay_ax);
	PutAX(Magnet_ArD, 	AX_MOVING_SPEED, maxspeed_claw);
						__delay_ms(delay_ax);
	PutAX(Bras_G, 		AX_MOVING_SPEED, maxspeed_claw);
						__delay_ms(delay_ax);
	PutAX(Bras_C, 		AX_MOVING_SPEED, maxspeed_claw);
						__delay_ms(delay_ax);	
	PutAX(Bras_D, 		AX_MOVING_SPEED, maxspeed_claw);
						__delay_ms(delay_ax);
	PutAX(Bras_parasol, AX_MOVING_SPEED, maxspeed_claw);
						__delay_ms(delay_ax);


	// PutAX(Fish_AvG, 	AX_GOAL_POSITION, /*position init*/);
						// __delay_ms(/*delay optimal*/);
        // PutAX(Fish_AvD, 	AX_GOAL_POSITION, /*position init*/);
						// __delay_ms(/*delay optimal*/);
	// PutAX(Fish_ArG, 	AX_GOAL_POSITION, /*position init*/);
						// __delay_ms(/*delay optimal*/);
	// PutAX(Fish_ArD, 	AX_GOAL_POSITION, /*position init*/);
						// __delay_ms(/*delay optimal*/);
	// PutAX(Magnet_AvG, 	AX_GOAL_POSITION, /*position init*/);
						// __delay_ms(/*delay optimal*/);
        // PutAX(Magnet_AvD, 	AX_GOAL_POSITION, /*position init*/);
						// __delay_ms(/*delay optimal*/);
	// PutAX(Magnet_ArG, 	AX_GOAL_POSITION, /*position init*/);
						// __delay_ms(/*delay optimal*/);
	// PutAX(Magnet_ArD, 	AX_GOAL_POSITION, /*position init*/);
						// __delay_ms(/*delay optimal*/);
	// PutAX(Bras_G, 		AX_GOAL_POSITION, /*position init*/);
						// __delay_ms(/*delay optimal*/);
	// PutAX(Bras_C, 		AX_GOAL_POSITION, /*position init*/);
						// __delay_ms(/*delay optimal*/);	
	// PutAX(Bras_D, 		AX_GOAL_POSITION, /*position init*/);
						// __delay_ms(/*delay optimal*/);
	// PutAX(Bras_parasol, AX_GOAL_POSITION, /*position init*/);
						// __delay_ms(/*delay optimal*/);

}

 void Deploy_fish_Av(void)		// Déploie le bras de pêche Avant.
 {
    if(!PIN_TEAM)
    {    // PutAX(Fish_AvG,AX_GOAL_POSITION,/*TBA*/);
    }
    else
    {    // PutAX(Fish_AvD,AX_GOAL_POSITION,/*TBA*/);
    }
    // __delay_ms(/*TBA*/);
 }

 void Deploy_fish_Ar(void)		// Déploie le bras de pêche Arriere.
 {
    if(!PIN_TEAM)
    {    // PutAX(Fish_ArG,AX_GOAL_POSITION,/*TBA*/);
    }
    else
    {    // PutAX(Fish_ArD,AX_GOAL_POSITION,/*TBA*/);
    }
    // __delay_ms(/*TBA*/);
 }

 void Moveup_fish_Av(void)		// Releve legerement le bras de pêche Avant.
 {
    if(!PIN_TEAM)
    {    // PutAX(Fish_AvG,AX_GOAL_POSITION,/*TBA*/);
    }else
    {    // PutAX(Fish_AvD,AX_GOAL_POSITION,/*TBA*/);
    }
    // __delay_ms(/*TBA*/);
 }

 void Moveup_fish_Ar(void)		// Releve legerement le bras de pêche Arriere.
 {
    if(!PIN_TEAM)
    {    // PutAX(Fish_ArG,AX_GOAL_POSITION,/*TBA*/);
    }
    else
    {    // PutAX(Fish_ArD,AX_GOAL_POSITION,/*TBA*/);
    }
    // __delay_ms(/*TBA*/);
}

 void Rlz_fish_Av(void)		// Leve le bras d'aimants Avant.
 {
    if(!PIN_TEAM)
	{
		// PutAX(Fish_AvG,AX_GOAL_POSITION,/*TBA*/);	// Positionnement du bras.
		// __delay_ms(/*TBA*/);
		// PutAX(Magnet_AvG,AX_GOAL_POSITION,/*TBA*/);	// Lâchez les poissons !!!!
		// __delay_ms(/*TBA*/);
		// PutAX(Magnet_AvG,AX_GOAL_POSITION,/*TBA*/);	// Rangement du bras a aimants.
		// __delay_ms(/*TBA*/);
		// PutAX(Fish_AvG,AX_GOAL_POSITION,/*TBA*/);	// Rangement du bras de pêche.
	}
    else
    {
		// PutAX(Fish_AvD,		AX_GOAL_POSITION,/*TBA*/);	// Positionnement du bras.
							// __delay_ms(/*TBA*/);
		// PutAX(Magnet_AvD,	AX_GOAL_POSITION,/*TBA*/);	// Lâchez les poissons !!!!
							// __delay_ms(/*TBA*/);
		// PutAX(Magnet_AvD,	AX_GOAL_POSITION,/*TBA*/);	// Rangement du bras a aimants.
							// __delay_ms(/*TBA*/);
		// PutAX(Fish_AvD,		AX_GOAL_POSITION,/*TBA*/);	// Rangement du bras de pêche.
	}
		// __delay_ms(/*TBA*/);
 }

void Rlz_fish_Ar(void)		// Leve le bras d'aimants Avant.
{
    if(!PIN_TEAM)
	{
		// PutAX(Fish_ArG,		AX_GOAL_POSITION,/*TBA*/);	// Positionnement du bras.
							// __delay_ms(/*TBA*/);
		// PutAX(Magnet_ArG,	AX_GOAL_POSITION,/*TBA*/);	// Lâchez les poissons !!!!
							// __delay_ms(/*TBA*/);
		// PutAX(Magnet_ArG,	AX_GOAL_POSITION,/*TBA*/);	// Rangement du bras a aimants.
							// __delay_ms(/*TBA*/);
		// PutAX(Fish_ArG,		AX_GOAL_POSITION,/*TBA*/);	// Rangement du bras de pêche.
	}
    else
    {
		// PutAX(Fish_ArD,		AX_GOAL_POSITION,/*TBA*/);	// Positionnement du bras.
							// __delay_ms(/*TBA*/);
		// PutAX(Magnet_ArD,	AX_GOAL_POSITION,/*TBA*/);	// Lâchez les poissons !!!!
							// __delay_ms(/*TBA*/);
		// PutAX(Magnet_ArD,	AX_GOAL_POSITION,/*TBA*/);	// Rangement du bras a aimants.
							// __delay_ms(/*TBA*/);
		// PutAX(Fish_ArD,		AX_GOAL_POSITION,/*TBA*/);	// Rangement du bras de pêche.
	}
		// __delay_ms(/*TBA*/);
}

void Open_bras(void)
{
    if(!PIN_TEAM)
	{
        // PutAX(rabd,AX_GOAL_POSITION,330); //rabat la piece
        // __delay_ms(700);
        // PutAX(rabd,AX_GOAL_POSITION,620); //reouvre
        // __delay_ms(500);
        // PutAX(rabg,AX_GOAL_POSITION,820); //rabat la piece
        // __delay_ms(700);
        // PutAX(rabg,AX_GOAL_POSITION,390); //reouvre
        // __delay_ms(50);
    }
    else
	{
        // PutAX(rabg,AX_GOAL_POSITION,820); //rabat la piece
        // __delay_ms(700);
        // PutAX(rabg,AX_GOAL_POSITION,390); //reouvre
        // __delay_ms(500);
        // PutAX(rabd,AX_GOAL_POSITION,330); //rabat la piece
        // __delay_ms(700);
        // PutAX(rabd,AX_GOAL_POSITION,620); //reouvre
        // __delay_ms(50);
    }

}

void Openfull_bras (void) 
{	// Ouverture à 180° des bras pour fermer les portes.

}

void Close_bras(void)
{ // Resserrage des bras contre les blocs de sable.

}

void Funny_action(void)
{ // Déploiement du bras pour tendre le 'parasol'.

}

/******************************************************************************/