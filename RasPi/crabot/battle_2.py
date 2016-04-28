#!/usr/bin/env python3

import serial
import functions
from time import sleep

ser = serial.Serial("/dev/ttyAMA0",57600)

functions.reset_pic()
functions.init_ax(ser)

# Attente du start
print "waiting for start"
answer = functions.get_ans(ser)
while answer != "$STRT;":
     answer = functions.get_ans(ser)
     print answer

# demande de l'equipe
team = 0
while team==0 :
	team = functions.ask_team(ser)

###############################
## DEBUT DE ROUTINE DE MATCH ##
###############################
functions.set_speed(ser,0.4)
####################################
#### PRISE DU MINI TAS DE SABLE ####

### Ouverture des bras
functions.open_bras(ser)
sleep(0.2)
### PRISE DU SABLE ET POSE DANS LA ZONE DE CONSTRUCTION
functions.move_push(ser,0.85,0,0.4)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)
functions.catch(ser)
functions.move_push(ser,1.1,0,0)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)
functions.open_bras(ser)
functions.set_speed(ser,0)	### On enleve la limite de vitesse
sleep(0.2)
###################################
#### FERMETURE DES PORTES #########
### FERMETURE DES BRAS
functions.move_push(ser,0.60,0,0.1)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)
functions.close_bras(ser)
functions.move_push(ser,0.38,team*(-0.58),0.3)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)

### GO vers les portes
functions.open_full_bras(ser)

### Fermeture des portes
functions.move_pos(ser,0.35,team*(0.8))
answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)
#######################################   functions.move_speed(ser,0.2,0)
sleep(0.5)

################################
#### PRISE DU TAS DE SABLE #####
### Recul & Fermeture des bras

functions.move_push(ser,0.35,team*0.6,0.1)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)
functions.close_bras(ser)

### Rotation vers les blocs de sable
functions.move_push(ser,0.828,team*0.5,0)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)
functions.open_bras(ser)

### Avancee vers les blocs de sable
functions.rotate(ser,team*90)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)
functions.move_pos(ser,0.828,team*0.68)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)
functions.rotate(ser,team*90)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)

### Prise des blocs & Limite d acceleration
functions.move_speed(ser,0.1,0)
sleep(0.5)
functions.set_y(ser,team*0.71)
sleep(0.01)
functions.move_pos(ser,0.828,team*0.712)
functions.catch(ser)
sleep(0.7)
### functions.set_acc(ser,0.2,6,0.3)	###########################
functions.set_speed(ser,0.2)	### AJOUTER LIMITE VITESSE DE ROTATION !

### Recul
functions.move_push(ser,0.828,team*0.50,0.1)
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
functions.rotate(ser,team*60)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)
functions.open_bras(ser)
sleep(1)
### functions.set_acc(ser,0,0,0)  ### contraintes d'acceleration par defaut

functions.move_push(ser,0.72,team*(-0.8),0.2)
answer = functions.get_ans(ser)
while answer != "$DONE;":
        answer = functions.get_ans(ser)
functions.close_bras(ser)
functions.move_push(ser,0.72,team*(-0.8),0)
answer = functions.get_ans(ser)
while answer != "$DONE;":
        answer = functions.get_ans(ser)

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

##### A voir si on ajoute un autre aller retour

### PRISE DES COQUILLAGES
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

### SECONDE PRISE
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
functions.move_push(ser,0.15,team*(0.05),0.1)
answer = functions.get_ans(ser)
while answer != "$DONE;":
     answer = functions.get_ans(ser)

functions.move_push(ser,0.5,team*(-0.8),0.15)
answer = functions.get_ans(ser)
while answer != "$DONE;":
     answer = functions.get_ans(ser)
functions.move_push(ser,2.2,team*(-0.85),0.1)
answer = functions.get_ans(ser)
while answer != "$DONE;":
     answer = functions.get_ans(ser)


ser.close()

