#!/usr/bin/env python3

import serial
import functions
import sleep from time

ser = serial.Serial("/dev/ttyAMA0",57600)

functions.reset_pic()
functions.init_ax(ser)

# Attente du start
answer = functions.get_ans(ser)
while answer != "$STRT;":
	answer = functions.get_ans(ser)
	print answer

# Demande de l'équipe
team = 0
while team==0
	team = functions.ask_team(ser)

#################################
## DEBUT SCRIPT D'HOMOLOGATION ##
#################################

### LA POSITION INITIALE EST PENCHEE !!
functions.set_angle(ser,team*45)

# Déplacement
functions.move_pos(ser,0.1,team*0.5)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)





ser.close()
