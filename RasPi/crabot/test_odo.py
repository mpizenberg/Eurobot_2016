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
k=0
while k<5 :
	functions.move_pos(ser,1,0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
	     answer = functions.get_ans(ser)
	
	functions.move_pos(ser,1,1)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
	     answer = functions.get_ans(ser)
	
	functions.move_pos(ser,0,1)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
	     answer = functions.get_ans(ser)
	
	functions.move_pos(ser,0,0)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
	     answer = functions.get_ans(ser)
	k = k+1

functions.rotate(ser,0)
answer = functions.get_ans(ser)
while answer != "$DONE;":
     answer = functions.get_ans(ser)

functions.move_pos(ser,0.5,0)
answer = functions.get_ans(ser)
while answer != "$DONE;":
     answer = functions.get_ans(ser)

functions.move_pos(ser,0,0)
answer = functions.get_ans(ser)
while answer != "$DONE;":
     answer = functions.get_ans(ser)

ser.close()
