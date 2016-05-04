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

# Deplacement
functions.move_pos(ser,0.15,team*0.59)
answer = functions.get_ans(ser)
while answer != "$DONE;":
	answer = functions.get_ans(ser)
functions.enable_US(ser,'0')

while answer!="$END9":
	functions.move_pos(ser,0,0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
		
	functions.move_pos(ser,0,team*(-0.6))
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)		

ser.close()
