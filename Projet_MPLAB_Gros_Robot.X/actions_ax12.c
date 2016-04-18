#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <stdio.h>
#include <uart.h>
#include <delay.h>

#include "main.h"


#define maxtork_claw 650
#define maxspeed_claw 800
#define delay_min_ax 30

/******************************************************************************/
/*************************** Arm Specification ********************************/
/******************************************************************************/

// PIN TEAM = COTE D'EQUIPE VIOLET !!

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
            case AX12_CATCH_BRAS:
                Catch_bras();
                break;
            case AX12_OPENFULL_BRAS:
                Openfull_bras();
                break;
            case AX12_CLOSE_BRAS:
                Close_bras();
                break;
            case AX12_FUNNY_ACTION:
                Funny_action();
                break;
        }
        Num_Action_Done = num;
    }
}

void Init_ax12() {

    PutAX(Fish_AvG, 	AX_TORQUE_LIMIT, maxtork_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Fish_AvD, 	AX_TORQUE_LIMIT, maxtork_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Fish_ArG, 	AX_TORQUE_LIMIT, maxtork_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Fish_ArD, 	AX_TORQUE_LIMIT, maxtork_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Magnet_AvG, 	AX_TORQUE_LIMIT, maxtork_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Magnet_AvD, 	AX_TORQUE_LIMIT, maxtork_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Magnet_ArG, 	AX_TORQUE_LIMIT, maxtork_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Magnet_ArD, 	AX_TORQUE_LIMIT, maxtork_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Bras_G, 	AX_TORQUE_LIMIT, maxtork_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Bras_C, 	AX_TORQUE_LIMIT, maxtork_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Bras_D, 	AX_TORQUE_LIMIT, maxtork_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Bras_parasol, AX_TORQUE_LIMIT, maxtork_claw);
                        __delay_ms(delay_min_ax);

    PutAX(Fish_AvG, 	AX_MOVING_SPEED, 70);
                        __delay_ms(delay_min_ax);
    PutAX(Fish_AvD, 	AX_MOVING_SPEED, 70);
                        __delay_ms(delay_min_ax);
    PutAX(Fish_ArG, 	AX_MOVING_SPEED, 70);
                        __delay_ms(delay_min_ax);
    PutAX(Fish_ArD, 	AX_MOVING_SPEED, 70);
                        __delay_ms(delay_min_ax);
    PutAX(Magnet_AvG, 	AX_MOVING_SPEED, maxspeed_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Magnet_AvD, 	AX_MOVING_SPEED, maxspeed_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Magnet_ArG, 	AX_MOVING_SPEED, maxspeed_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Magnet_ArD, 	AX_MOVING_SPEED, maxspeed_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Bras_G, 	AX_MOVING_SPEED, maxspeed_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Bras_C, 	AX_MOVING_SPEED, maxspeed_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Bras_D, 	AX_MOVING_SPEED, maxspeed_claw);
                        __delay_ms(delay_min_ax);
    PutAX(Bras_parasol, AX_MOVING_SPEED, maxspeed_claw);
                        __delay_ms(delay_min_ax);

                     
    PutAX(Magnet_AvG, 	AX_GOAL_POSITION, 195);
                        __delay_ms(delay_min_ax);
    PutAX(Magnet_AvD, 	AX_GOAL_POSITION, 830);
                        __delay_ms(delay_min_ax);
    PutAX(Magnet_ArG, 	AX_GOAL_POSITION, 812);
                        __delay_ms(delay_min_ax);
    PutAX(Magnet_ArD, 	AX_GOAL_POSITION, 820);
                        __delay_ms(delay_min_ax);
    PutAX(Fish_AvG, 	AX_GOAL_POSITION, 527);
                        __delay_ms(delay_min_ax);
    PutAX(Fish_AvD, 	AX_GOAL_POSITION, 492);
                        __delay_ms(delay_min_ax);
    PutAX(Fish_ArG, 	AX_GOAL_POSITION, 195);
                        __delay_ms(delay_min_ax);
    PutAX(Fish_ArD, 	AX_GOAL_POSITION, 834);
                        __delay_ms(delay_min_ax);
    PutAX(Bras_G, 	AX_GOAL_POSITION, 830);
                        __delay_ms(delay_min_ax);
    PutAX(Bras_C, 	AX_GOAL_POSITION, 670);
                        __delay_ms(delay_min_ax);
    PutAX(Bras_D, 	AX_GOAL_POSITION, 200);
                        __delay_ms(delay_min_ax);
    PutAX(Bras_parasol, AX_GOAL_POSITION, 470);
                        __delay_ms(delay_min_ax);

}

// PIN TEAM = 1 pour violet, 0 pour vert

 void Deploy_fish_Av(void)		// Déploie le bras de pêche Avant.
 {
    if(!PIN_TEAM)       // Côté Vert.
    {    
        PutAX(Fish_AvG,AX_GOAL_POSITION,220);
    }
    else                // Côté Violet.
    {
        PutAX(Fish_AvD,AX_GOAL_POSITION,800);
    }
    __delay_ms(delay_min_ax);
 }

 void Deploy_fish_Ar(void)		// Déploie le bras de pêche Arriere.
 {
    if(!PIN_TEAM)
    {    
        PutAX(Fish_ArG,AX_GOAL_POSITION,500);
    }
    else
    {    
        PutAX(Fish_ArD,AX_GOAL_POSITION,520);
    }
    __delay_ms(delay_min_ax);
 }

 void Moveup_fish_Av(void)		// Releve legerement le bras de pêche Avant.
 {
    if(!PIN_TEAM)
    {    
        PutAX(Fish_AvG,AX_GOAL_POSITION,300);
    }
    else
    {    
        PutAX(Fish_AvD,AX_GOAL_POSITION,700);
    }
    __delay_ms(delay_min_ax);
 }

 void Moveup_fish_Ar(void)		// Releve legerement le bras de pêche Arriere.
 {
    if(!PIN_TEAM)
    {
        PutAX(Fish_ArG,AX_GOAL_POSITION,420);
    }
    else
    {
        PutAX(Fish_ArD,AX_GOAL_POSITION,620);
    }
    __delay_ms(delay_min_ax);
}

 void Rlz_fish_Av(void)		// Leve le bras d'aimants Avant.
 {
    Deploy_fish_Av();   // Positionnement des bras.
    if(!PIN_TEAM)
	{
		PutAX(Magnet_AvG,       AX_GOAL_POSITION,512);	// Lâchez les poissons !!!!
		__delay_ms(200);
		PutAX(Magnet_AvG, 	AX_GOAL_POSITION, 215); // Rangement du bras a aimants.
        __delay_ms(delay_min_ax);                           	
        PutAX(Fish_AvG, 	AX_GOAL_POSITION, 520); // Rangement du bras de pêche.
	}
    else
    {
		PutAX(Magnet_AvD,       AX_GOAL_POSITION,512);	// Lâchez les poissons !!!!
		__delay_ms(200);
		PutAX(Magnet_AvD, 	AX_GOAL_POSITION, 930); // Rangement du bras a aimants.
        __delay_ms(delay_min_ax);                           	
        PutAX(Fish_AvD, 	AX_GOAL_POSITION, 492); // Rangement du bras de pêche.
	}
    __delay_ms(delay_min_ax);
 }

 void Rlz_fish_Ar(void)		// Leve le bras d'aimants Avant.
 {
    Deploy_fish_Ar();   // Positionnement des bras.
    if(!PIN_TEAM)
	{
        PutAX(Magnet_ArG,       AX_GOAL_POSITION,712);	// Lâchez les poissons !!!!
        __delay_ms(200);
        PutAX(Magnet_ArG, 	AX_GOAL_POSITION, 812); // Rangement du bras a aimants.
        __delay_ms(delay_min_ax);
        PutAX(Fish_ArG, 	AX_GOAL_POSITION, 195); // Rangement du bras de pêche.
	}
    else
    {
		PutAX(Magnet_ArD,       AX_GOAL_POSITION,700);	// Lâchez les poissons !!!!
		__delay_ms(200);
		PutAX(Magnet_ArD, 	AX_GOAL_POSITION, 820); // Rangement du bras a aimants.
        __delay_ms(delay_min_ax);
        PutAX(Fish_ArD, 	AX_GOAL_POSITION, 834); // Rangement du bras de pêche.
	}
    __delay_ms(delay_min_ax);
 }


void Open_bras(void)
{
    if(!PIN_TEAM)
	{
        PutAX(Bras_D,AX_GOAL_POSITION,512);
        __delay_ms(delay_min_ax);
        PutAX(Bras_C,AX_GOAL_POSITION,350); //reouvre
    }
    else
	{
        PutAX(Bras_G,AX_GOAL_POSITION,512);
        __delay_ms(delay_min_ax);
        PutAX(Bras_C,AX_GOAL_POSITION,1000); //reouvre
    }
    __delay_ms(delay_min_ax);
}

void Openfull_bras (void) 
{	// Ouverture à 180° des bras pour fermer les portes.
    PutAX(Bras_D,AX_GOAL_POSITION,800);
    __delay_ms(delay_min_ax);
    PutAX(Bras_C,AX_GOAL_POSITION,670);
    __delay_ms(delay_min_ax);
    PutAX(Bras_G,AX_GOAL_POSITION,200);
    __delay_ms(delay_min_ax);
}

void Catch_bras(void)
{ // Resserrage des bras contre les blocs de sable.
    if(!PIN_TEAM)
	{
        PutAX(Bras_D,AX_GOAL_POSITION,487);
        __delay_ms(700);
        PutAX(Bras_C,AX_GOAL_POSITION,375);
    }
    else
	{
        PutAX(Bras_G,AX_GOAL_POSITION,535);
        __delay_ms(700);
        PutAX(Bras_C,AX_GOAL_POSITION,965);
    }
    __delay_ms(delay_min_ax);
}

void Close_bras(void)
{ // Rangement des bras.
    PutAX(Bras_G, 	AX_GOAL_POSITION, 830);
                        __delay_ms(delay_min_ax);
    PutAX(Bras_C, 	AX_GOAL_POSITION, 670);
                        __delay_ms(delay_min_ax);
    PutAX(Bras_D, 	AX_GOAL_POSITION, 200);
                        __delay_ms(delay_min_ax);
}

void Funny_action(void)
{ // Déploiement du bras pour tendre le 'parasol'.
    PutAX(Bras_parasol, AX_GOAL_POSITION, 222);
    __delay_ms(delay_min_ax);
}

/******************************************************************************/