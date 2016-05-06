#!/usr/bin/env python3

import serial
import functions
from time import sleep

'''
Quadrillage de la dune :
	 -4 -3 -2 -1 0  1  2  3  4
	 _  _  _  _  _  _  _  _  _
A	|_||_||_||_||_||_||_||_||_|
B			 |_||_||_|
C				(_)
'''
def Script_Recalage (ser,team):
	functions.enable_US(ser,'0')
	sleep(0.1)
	functions.set_speed(ser,0.2)
	sleep(0.1)
	functions.move_speed(ser,0.2,0)
	sleep(0.1)

    	functions.set_x(ser,-0.07)
	sleep(0.1)
    	functions.set_y(ser,team*0.60)
	sleep(0.1)
	functions.set_t(ser,team*(135))
	sleep(0.1)
	functions.move_speed(ser,-0.3,0)
	sleep(0.2)

	functions.move_pos(ser,0.30,0.30*team)
    	answer = functions.get_ans(ser)
    	while answer != "$DONE;":
		answer = functions.get_ans(ser)

	functions.rotate(ser,team*45)
    	answer = functions.get_ans(ser)
    	while answer != "$DONE;":
		answer = functions.get_ans(ser)

	functions.move_pos(ser,0.005,-0.005*team)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)

	functions.enable_US(ser,'0')
	functions.set_speed(ser,0.8)

def Prise_Colonne_De_Sable(ser,team,x,y):
    functions.move_pos(ser,x-0.60,team*(y-0.165))
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
        answer = functions.get_ans(ser)
    functions.enable_US(ser,'0')
    functions.rotate(ser,180)
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
        answer = functions.get_ans(ser)
    functions.move_pos(ser,x,team*(y-0.165))
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
        answer = functions.get_ans(ser)
    functions.move_pos(ser,x-0.190,team*(y-0.300))
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
        answer = functions.get_ans(ser)

    functions.rotate(ser,team*(-90))
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
        answer = functions.get_ans(ser)

    functions.enable_pumps(ser)
    sleep(0.1)

    functions.move_pos(ser,x-0.180,team*(y-0.125))
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
        answer = functions.get_ans(ser)
    functions.move_speed(ser,-0.2,0)
    sleep(0.4)
    functions.motion_free(ser)

    functions.set_speed(ser,0.1)
    sleep(0.1)
    functions.set_speed_ang(ser,1.5)
    sleep(0.1)

    functions.move_pos(ser,x-0.190,team*(y-0.245))
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
        answer = functions.get_ans(ser)

    functions.deploy_wings(ser)
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
        answer = functions.get_ans(ser)

    functions.move_pos(ser,0.40,team*0.15)
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
        answer = functions.get_ans(ser)
   
    functions.rotate(ser,team*100)
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
        answer = functions.get_ans(ser)

    functions.move_pos(ser,0.40,team*(-0.20))
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
        answer = functions.get_ans(ser)

    functions.rotate(ser,team*(170))
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
        answer = functions.get_ans(ser)

    ### On s enfonce dans la zone de construction.
    
    functions.set_speed(ser,0.1)
    sleep(0.1)
    functions.set_speed_ang(ser,1.5)
    sleep(0.1)
  
    functions.enable_US(ser,'0')
    functions.move_pos(ser,1,team*(-0.20))
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
        answer = functions.get_ans(ser)
        
    functions.disable_pumps(ser)
    sleep(0.1)
    functions.close_wings(ser)
    sleep(0.5)
    functions.set_speed(ser,0)
    sleep(0.1)

    functions.move_pos(ser,0.5,team*(-0.2))
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
        answer = functions.get_ans(ser)
    
    functions.move_pos(ser,0,team*0.4)
    answer = functions.get_ans(ser)
    while answer != "$DONE;":
        answer = functions.get_ans(ser)

    functions.enable_US(ser,'F')

    print "Et une colonne de plus ! Une !"

#def Prise_Sable_Adversaire(ser,team):
	

def Homologation(ser,team):
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
