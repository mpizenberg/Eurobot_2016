/*
* Sick
* Compiler : Microchip xC16
* �C : 33FJ64MC804
* Mai 2014
*    ____________      _           _
*   |___  /| ___ \    | |         | |
*      / / | |_/ /___ | |__   ___ | |_
*     / /  |    // _ \| '_ \ / _ \| __|
*    / /   | |\ \ (_) | |_) | (_) | |_
*   /_/    |_| \_\___/|____/ \___/'\__|
*			      7robot.fr
*/

#ifndef __EVITEMENTLOC_H
#define	__EVITEMENTLOC_H


/******************************************************************************/
/* Function Prototypes                                                        */
/******************************************************************************/

void Init_Evitement(void);

void Choose_Enabled_Sicks(int Sicks_En);

void New_Order_Evitement_Handling(void);

void Must_do_Gestion_Evitement(void);

void Gestion_Evitement_Every_few_ms(void);

#endif	

