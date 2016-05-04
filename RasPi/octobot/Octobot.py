#!/usr/bin/env python3

import serial
import functions
import functions_macro

ser = serial.Serial("/dev/ttyAMA0",57600)

functions.reset_pic()
functions.init_ax(ser)
while 1:

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

	### SCRIPTS DE MATCH ###
	functions_macro.Prise_Colonne_De_Sable(ser,team,1.4,0.6)
	functions_macro.Prise_Colonne_De_Sable(ser,team,1.4,0.6)
	functions_macro.Prise_Colonne_De_Sable(ser,team,1.4,0.6)
	functions_macro.Prise_Colonne_De_Sable(ser,team,1.4,0.6)
	

ser.close()

