#!/usr/bin/env python3

import serial
import functions
from time import sleep

def Prise_Petit_Tas_De_Sable(ser,team,configuration):
	IsDone = 0;
	functions.set_speed(ser,0.4)
	####################################
	#### PRISE DU MINI TAS DE SABLE ####
	
	### Ouverture des bras
	functions.open_bras(ser)
	sleep(0.2)
	### PRISE DU SABLE ET POSE DANS LA ZONE DE CONSTRUCTION
	functions.move_push(ser,1.1,0,0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	functions.open_bras(ser)
	functions.set_speed(ser,0)	### On enleve la limite de vitesse
	sleep(0.2)
	### RECUL
	if configuration==1:
		functions.move_push(ser,0.85,0,0.2)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
	else :
		functions.move_push(ser,0.60,0,0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)

	### FERMETURE DES BRAS
	functions.close_bras(ser)
	print "Prise du Petit Tas fait : +16 points potentiels !"
	return IsDone;
	
def Recaler_Coquillage(ser,team,configuration):
	IsDone = 0;
	if configuration==1:
		functions.move_push(ser,0.1,team*(-0.5),0.3)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
		functions.move_push(ser,0.4,team*(-0.3),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
	elif (configuration==2) or (configuration==3):
		functions.move_push(ser,0.38,team*(-0.58),0.3)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
	elif (configuration==4) or (configuration==5):
		functions.move_push(ser,0.35,team*(-0.4),0.2)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
	return IsDone;
	
def Fermeture_Portes(ser,team):
	IsDone = 0;
	functions.open_full_bras(ser)

	### Fermeture des portes
	functions.move_pos(ser,0.35,team*(0.79))
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	#######################################   functions.move_speed(ser,0.2,0)
	sleep(0.2)
	
	### RECUL & FERMETURE DES BRAS
	functions.move_push(ser,0.35,team*0.6,0.1)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	functions.close_bras(ser)
	return IsDone;
	
def Prise_Grand_Tas_De_Sable(ser,team,configuration):
	IsDone = 0;
	### Rotation vers les blocs de sable
	functions.move_push(ser,0.83,team*0.5,0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	functions.open_bras(ser)

	### Avancee vers les blocs de sable
	functions.rotate(ser,team*90)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	functions.move_pos(ser,0.83,team*0.68)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	functions.rotate(ser,team*90)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)

	### CALAGE SUR LES BLOCS
	functions.move_speed(ser,0.1,0)
	sleep(0.5)
	functions.set_y(ser,team*0.7)
	sleep(0.01)
	functions.move_pos(ser,0.83,team*0.7)

	### PRISE DES BLOCS
	functions.catch(ser)
	sleep(1.2)
	### functions.set_acc(ser,0.2,6,0.3)	###########
	functions.set_speed(ser,0.2)
	functions.set_speed_ang(ser,1)

	### Recul
	functions.move_push(ser,0.83,team*0.50,0.1)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)

	### CHEMIN VERS LES ZONE DE CONSTRUCTION
	functions.move_push(ser,0.35,team*(0.1),0.2)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	functions.move_push(ser,0.60,team*(-0.16),0.2)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	functions.move_push(ser,1.1,team*(-0.4),0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
		
	### LACHER DU SABLE
	functions.rotate(ser,team*50)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	functions.open_bras(ser)
	sleep(1)
	
	### CONTRAINTES DE VITESSE PAR DEFAUT
	functions.set_speed(ser,0)
	functions.set_speed_ang(ser,4)
	
	if configuration<4:
		functions.move_push(ser,0.72,team*(-0.8),0.2)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
				answer = functions.get_ans(ser)
		functions.close_bras(ser)
		functions.move_push(ser,0.72,team*(-0.8),0)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
				answer = functions.get_ans(ser)
	elif (configuration==4) or (configuration==5):
		functions.move_push(ser,0.7,team*(-0.65),0.16)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
		functions.close_bras(ser)
		functions.move_push(ser,0.1,team*(-0.6),0.15)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
	return IsDone;
	
def Prise_Poissons(ser,team):
	IsDone = 0;
	functions.move_push(ser,0.3,team*(-0.88),0.1)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		 answer = functions.get_ans(ser)

	### Placement en centre de bassin et deploiement des bras
	functions.move_push(ser,0.55,team*(-0.90),0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		 answer = functions.get_ans(ser)
	functions.deploy_fish(ser)

	### Rotation pour s'aligner avec la mer
	functions.rotate(ser,0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		 answer = functions.get_ans(ser)

	### Changement de vitesse max
	functions.set_speed(ser,0.2)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		 answer = functions.get_ans(ser)

	### Et 3 pas en avant !!
	functions.move_pos(ser,0.69,team*(-0.90))
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		 answer = functions.get_ans(ser)
	functions.rotate(ser,0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
			answer = functions.get_ans(ser)

	### Et 3 pas en arriere !!
	functions.move_pos(ser,0.47,team*(-0.90))
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		 answer = functions.get_ans(ser)
	functions.rotate(ser,0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
			answer = functions.get_ans(ser)

	### RANGEMENT DES BRAS POUR LES AMENER AU FILET
	functions.moveup_fish_av(ser)
	functions.moveup_fish_ar(ser)
	sleep(2)


	### DEPLACEMENT VERS LE FILET
	functions.set_speed(ser,0.5)
	functions.move_push(ser,0.90,team*(-0.85),0.1)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		 answer = functions.get_ans(ser)
	functions.move_push(ser,1.1,team*(-0.90),0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		 answer = functions.get_ans(ser)
	functions.rotate(ser,0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		 answer = functions.get_ans(ser)

	 ### LACHEZ LES POISSON !!
	functions.rlz_fish(ser)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		 answer = functions.get_ans(ser)
	return IsDone;
	
def Prise_Coquillages_1(ser,team,configuration):
	IsDone = 0;
	if configuration==1:		### CONFIGURATION 1 ###
		functions.move_push(ser,0.35,team*(-0.85),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)

		functions.move_push(ser,0.15,team*(-0.7),0)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,0.1,team*(0.05),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
	
	elif configuration==2:		### CONFIGURATION 2 & 3 ###
		functions.move_push(ser,2.2,team*(-0.85),0.25)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,1.6,team*(-0.7),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,0.6,team*(-0.68),0)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,0.05,team*(0.05),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
			 
	elif configuration==3:		### CONFIGURATION 3 A MODIFIER ###
		functions.move_push(ser,2.2,team*(-0.85),0.25)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,1.6,team*(-0.7),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,0.6,team*(-0.68),0)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,0.05,team*(0.05),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
			 
	elif (configuration==4) or (configuration==5):		### CONFIGURATION 4 & 5 ###
		functions.move_push(ser,0.90,team*(-0.85),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)

		functions.move_push(ser,0.4,team*(-0.85),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)

		functions.move_push(ser,0.07,team*(-0.65),0.05)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,0.07,team*(0.1),0.15)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
	return IsDone;
	
def Prise_Coquillages_2(ser,team,configuration):
	IsDone = 0;
	### LA CONFIGURATION  A QU'UNE PRISE DE COQUILLAGES ###
	
	if (configuration==2) or (configuration==3):	### CONFIGURATION 2 & 3 ###
		functions.move_push(ser,0.5,team*(-0.5),0.15)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,0.5,team*(-1),0.2)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,0.15,team*(-0.7),0)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,0.12,team*(0.05),0.25)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
	elif configuration==4:		 ### CONFIGURATION 4 A MODIFIER ###
		functions.move_push(ser,0.35,team*(-0.85),0.2)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)

		functions.move_push(ser,0.9,team*(-0.85),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,1.1,team*(-0.88),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,1.3,team*(-0.88),0)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.rotate(ser,5)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.rotate(ser,180)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,1.7,team*(-0.88),0)

		functions.rotate(ser,10)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)

		functions.move_push(ser,0,0,0.05)
		
	elif configuration==5:		 ### CONFIGURATION 5 ###
		functions.move_push(ser,0.35,team*(-0.85),0.2)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)

		functions.move_push(ser,0.9,team*(-0.85),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,1.1,team*(-0.88),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,1.3,team*(-0.88),0)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.rotate(ser,5)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.rotate(ser,180)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
		functions.move_push(ser,1.7,team*(-0.88),0)

		functions.rotate(ser,10)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)

		functions.move_push(ser,0,0,0.05)
		return IsDone;
