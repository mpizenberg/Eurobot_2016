#!/usr/bin/env python3

import serial
import functions
from time import sleep

ser = serial.Serial("/dev/ttyAMA0",57600)

functions.reset_pic()
functions.init_ax(ser)

# Attente du start
answer = functions.get_ans(ser)
while answer != "$STRT;":
	print "waiting for start"
	answer = functions.get_ans(ser)
	print answer
#on a souci avec le bouton qui semble ne pas marcher 
# Demande de l'equipe
team = 0
while team==0:
	team = functions.ask_team(ser)

#################################
## DEBUT SCRIPT D'HOMOLOGATION ##
#################################

### LA POSITION INITIALE EST PENCHEE !!
functions.set_x(ser,0)
functions.set_y(ser,0)
functions.set_t(ser,team*45)
# Deplacement
functions.move_pos(ser,0.15,team*0.54)
functions.enable_US(ser,'0')
answer = functions.get_ans(ser)
while answer != "$DONE;":
	answer=function.get_ans(ser)
	print answer
functions.move_speed(ser,0.15,0)
sleep(1)
functions.motion_free(ser)
functions.enable_US(ser,'3')

	
while answer!="$END9":
	functions.move_pos(ser,0.2,0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	functions.move_pos(ser,0.2,team*(-0.6))
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)		
ser.close
