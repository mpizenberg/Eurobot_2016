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
def Prise_Colonne_De_Sable(ser,team,x,y):
	functions.move_pos(ser,x-0.3,team*y)
        answer = functions.get_ans(ser)
        while answer != "$DONE;":
                answer = functions.get_ans(ser)
	functions.enable_US(ser,'0')
	functions.move_pos(ser,x+0.04,team*y)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	functions.move_pos(ser,x,team*y)
        answer = functions.get_ans(ser)
        while answer != "$DONE;":
                answer = functions.get_ans(ser)

	functions.rotate(ser,team*(-90))
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
		
	functions.enable_pumps(ser)
	
	functions.move_speed(ser,-0.2,0)
	sleep(1)
	#functions.move_speed(ser,0.01,0)
	functions.set_speed(ser,0.1)
	functions.set_speed_ang(ser,1.5)
	functions.set_acc(ser,0.1)
	sleep(0.05)
	
	#functions.enable_US(ser,'9')
	functions.move_pos(ser,x,team*(y-0.1))
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	
	functions.deploy_wings(ser)
	sleep(1)
	
	functions.move_push(ser,0.35,team*(0.1),0.2)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
				
	functions.move_push(ser,0.60,team*(-0.16),0.2)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
	
	### On s enfonce dans la zone de construction.
	functions.enable_US(ser,'0')
	functions.move_push(ser,x-0.3,team*(y-0.75),0.10)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
		
	functions.disable_pumps(ser)
	functions.close_wings(ser)
	sleep(0.5)
	functions.set_speed(ser,0)
	functions.set_speed(ser,3)
	sleep(0.05)
	
	functions.move_push(ser,0.3,team*(0.2),0.15)
	answer = functions.get_ans(ser)
	while answer != "$DONE;":
		answer = functions.get_ans(ser)
		
	functions.enable_US(ser,'F')

	print "Et une colonne de plus ! Une !"

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
