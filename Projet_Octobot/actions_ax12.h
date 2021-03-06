/*
 * File:   actions_ax12.h
 * Author: zoltarius
 *
 * Created on 4 avril 2014, 18:41
 */

#ifndef ACTIONS_AX12_H
#define	ACTIONS_AX12_H

/*
 * NUMEROTATION DES ACTIONNEURS DU ROBOT :
 _______________
| \           / |
|  \ 1     2 /  |
|   �       �   |
| \           / |
|  \         /  |
|   \ 3   4 /   |
|    �     �    |
|       O       |
| ______O______ |
*/

#define Wing_1		6	// Bras haut - gauche pour tenir 3e etage de blocs de sable
#define Wing_2		12	// Bras haut - droite
#define Wing_3		13      // Bras bas - gauche pour tenir 1e et 2e etage de blocs de sable
#define Wing_4          10	// Bras bas - droite


// CLLC
// CLRO

#define NUM_ACTIONS_BUFFER 20


void Add_Action_AX12(char Action_ToDo);
void Faire_Actions_AX12(void);

#define AX12_INIT_AX12              1
void Init_ax12(void);
#define AX12_DEPLOY_WINGS_BAS       2		// Deploiement des ailes superieurs
void Deploy_wings_B(void);
#define AX12_DEPLOY_WINGS_HAUT      3		// Deploiement des ailes inferieurs
void Deploy_wings_H(void);
#define AX12_DEPLOY_WINGS           4           // Deploiement des 2 paires d'ailes en m�me temps + SendDone().
void Deploy_wings(void);
#define AX12_IBICF                  5		// I Believe I Can Fly !!!
void I_Can_Fly(void);

#endif	/* ACTIONS_AX12_H */