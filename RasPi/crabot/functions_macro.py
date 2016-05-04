#!/usr/bin/env python3

####
# CONFIGURATIONS
# 0 -> Configuration de recalage OK
# 1 -> OK - recul sur petit tas de sable a ameliorer
# 2 -> La fin est a revoir, possible fusionner avec 3
# 3 -> OK
# 4 -> OK enlever actions inutiles a la fin.
# 5 -> Fin a refaire.
# 6 -> Script d'homologation
####
import serial
import functions
from time import sleep

def Script_Recalage (ser,team):
	functions.enable_sicks(ser,'0')
	functions.set_speed(ser,0.4)
	functions.move_speed(ser,-0.2,0)
	sleep(0.5)

    functions.set_x(ser,0.25)
    functions.set_y(ser,team*(-0.94))
	functions.set_t(ser,team*(90))

	functions.move_pos(ser,0.25,0)
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
		answer = functions.get_ans(ser)

	functions.rotate(ser,0)
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
		answer = functions.get_ans(ser)

	functions.move_pos(ser,0,0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)

	functions.move_speed(ser,-0.2,0)
	sleep(0.5)

	functions.set_x(ser,0)
	functions.set_y(ser,0)
	functions.move_pos(ser,0,0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	functions.enable_sicks(ser,'F')

def Prise_Petit_Tas_De_Sable(ser,team,configuration):
	functions.set_speed(ser,0.4)
	####################################
	#### PRISE DU MINI TAS DE SABLE ####
	
	### Ouverture des bras
	functions.open_bras(ser)
	sleep(0.2)
	### PRISE DU SABLE ET POSE DANS LA ZONE DE CONSTRUCTION
	functions.move_push(ser,1.1,0,0.2)
	functions.enable_sicks(ser,'0')
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
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
	functions.enable_sicks(ser,'F')
	functions.close_bras(ser)
	print "Prise du Petit Tas fait : +16 points potentiels !"
	
def Recaler_Coquillage(ser,team,configuration):
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

	print "Coquillage en place !"

def Fermeture_Portes(ser,team):
	functions.open_full_bras(ser)

	### Fermeture des portes
	functions.move_push(ser,0.33,team*(0.79),0.3)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	functions.enable_sicks(ser,'0')
	
	functions.move_push(ser,0.35,team*(0.79),0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	functions.move_speed(ser,0.2,0)
	sleep(0.2)
	
	### RECUL & FERMETURE DES BRAS
	functions.move_push(ser,0.35,team*0.6,0.1)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
		
	functions.enable_sicks(ser,'F')
	functions.close_bras(ser)
	
	print "Les Portes sont fermees, +20 potentiels mon capitaine."
	
def Prise_Grand_Tas_De_Sable(ser,team,configuration):
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
	functions.set_acc(ser,0.4,12,0.9)
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
		
	functions.rotate(ser,team*(-45))
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
				
	functions.move_push(ser,0.60,team*(-0.16),0.2)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	functions.move_push(ser,1.05,team*(-0.4),0)

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
			
	print "Et un tas de sable en plus! Un ! +24 points potentiels."
	
def Prise_Poissons(ser,team):
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
		 
	print "Avouons-le, la peche a la moule c est mieux... +40 points potentiels."
	
def Prise_Coquillages_1(ser,team,configuration):
	if configuration==1:		### CONFIGURATION 1 OK ###
		functions.move_push(ser,0.35,team*(-0.85),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)

		functions.move_push(ser,0.15,team*(-0.7),0)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
			 
		functions.move_push(ser,0.1,team*(0.05),0.15)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
			 
		print "Ce sont pas des moules mais on s en contentera ! +8 points potentiels."

	elif configuration==3:		### CONFIGURATION 3 A MODIFIER ###
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
			 
	elif (configuration==2) or (configuration==4) or (configuration==5):### OK ###
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
	
def Prise_Coquillages_2(ser,team,configuration):
	### LA CONFIGURATION 1 A UNE SEULE PRISE DE COQUILLAGES ###
	
	if configuration==2:	### CONFIGURATION 2 ###
		### RECALAGE AVANT DEPART
		functions.rotate(ser,0)
                answer = functions.get_ans(ser)
                while answer != "$DONE;":
                         answer = functions.get_ans(ser)
		functions.move_speed(ser,-0.1,0)
		sleep(0.3)
		functions.set_x(ser,0)
		functions.set_t(ser,0)
		
		### On va au fond du board
		functions.move_push(ser,0.4,team*(-0.8),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)

		functions.move_push(ser,1.7,team*(-0.82),0.2)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)

		functions.move_push(ser,2.2,team*(-0.8),0.25)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
			
		 ### On ramene tout sur le passage
		functions.move_push(ser,1.6,team*(-0.7),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
		functions.move_push(ser,0.6,team*(-0.68),0.15)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
		functions.move_push(ser,0.2,team*(-0.6),0)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)

		### On fait le tour pour tout pousser dans la serviette de depart.
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

		print "Ce sont pas des moules mais on s en contentera ! +12 points potentiels."


        if configuration==3:    ### CONFIGURATION 3 ###
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
						 
		print "Ce sont pas des moules mais on s en contentera ! +10 points potentiels."


	elif configuration==4:		 ### CONFIGURATION 4 A MODIFIER ###
		functions.move_push(ser,0.35,team*(-0.85),0.2)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)

		functions.move_push(ser,0.9,team*(-0.85),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
			 
		functions.move_push(ser,1.1,team*(-0.85),0.1)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
			 
		functions.move_push(ser,1.3,team*(-0.85),0)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
			 
		functions.rotate(ser,team*5)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
		functions.rotate(ser,180)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
		functions.move_push(ser,1.7,team*(-0.85),0)

		functions.rotate(ser,team*10)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)

		functions.move_push(ser,0,0,0.05)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
			 
		print "Ce sont pas des moules mais on s en contentera ! +10 points potentiels."

		
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
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			 answer = functions.get_ans(ser)
			 
		print "Ce sont pas des moules mais on s en contentera ! +10 points potentiels."


def Homologation(ser,team):
	functions.set_speed(ser,0.2)
	functions.set_speed(ser,1)

	functions.open_bras(ser)

	functions.move_pos(ser,0.85,0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
	    answer = functions.get_ans(ser)

	functions.move_pos(ser,0.4,0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
	    answer = functions.get_ans(ser)
	
	functions.rotate(ser,team*1.5708)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
	    answer = functions.get_ans(ser)
	
	functions.move_pos(ser,0.4,team*0.45)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	
	functions.rotate(ser,0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)

	while answer !='$END9;':
		functions.move_pos(ser,1.1,team*0.45)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
	
		functions.move_pos(ser,0.2,team*0.45)
		answer = functions.get_ans(ser)
		while answer != "$DONE;":
			answer = functions.get_ans(ser)
