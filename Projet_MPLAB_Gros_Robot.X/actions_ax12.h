/*
 * File:   actions_ax12.h
 * Author: zoltarius
 *
 * Created on 4 avril 2014, 18:41
 */

#ifndef ACTIONS_AX12_H
#define	ACTIONS_AX12_H



#define Fish_AvG		4	// bras de pêche Avant-Gauche
#define Fish_AvD		1	//                  Avant-Droit
#define Fish_ArG		42      //                  Arrière-Gauche
#define Fish_ArD                14	//                  Arrière-Droit
#define Magnet_AvG              7	// Bras d'aimants de pêche Avant-Gauche
#define Magnet_AvD              17	//                          Avant-Droit
#define Magnet_ArG              20	//                          Arrière-Gauche
#define Magnet_ArD              23	//                          Arrière-Droit
#define Bras_G                  11	// Bras pour Sable de Gauche
#define Bras_C                  21	//                  Centrale
#define Bras_D                  9	//                  de Droite
#define Bras_parasol            16	// Bras pour la Funny Action

// CLLC
// CLRO

#define NUM_ACTIONS_BUFFER 20


void Add_Action_AX12(char Action_ToDo);
void Faire_Actions_AX12(void);

#define AX12_INIT_AX12              1
void Init_ax12(void);
#define AX12_DEPLOY_FISH_AV         2		// Déploiement de bras de pêche.
void Deploy_fish_Av(void);
#define AX12_DEPLOY_FISH_AR         3		// idem
void Deploy_fish_Ar(void);
#define AX12_MOVEUP_FISH_AV         4		// Levage (sans ranger !) de bras de pêche
void Moveup_fish_Av(void);				// pour évacuer le poisson de l'eau.
#define AX12_MOVEUP_FISH_AR         5		// idem
void Moveup_fish_Ar(void);
#define AX12_RLZ_FISH_AV            6		// Ouverture du bras supérieur pour lacher les poissons.
void Rlz_fish_Av(void);
#define AX12_RLZ_FISH_AR            7		// idem
void Rlz_fish_Ar(void);            
#define AX12_OPEN_BRAS              8		// Ouvertures des bras (milieu + G ou D) pour prendre du sable
void Open_bras(void);
#define AX12_OPENFULL_BRAS          9 		// Ouverture des bras pour fermer les portes.
void Openfull_bras(void);
#define AX12_CLOSE_BRAS 	    10		// Fermeture des bras pour attraper le sable.
void Close_bras(void);
#define AX12_FUNNY_ACTION 	    11		// Déploiement du bras pour ouvrir le parasol.
void Funny_action(void);

#endif	/* ACTIONS_AX12_H */