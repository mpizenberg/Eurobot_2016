#!/usr/bin/env python3

import serial
import functions
import functions_macro
from UrgenceReleveException import UrgenceReleveException


ser = serial.Serial("/dev/ttyAMA0",57600)

functions.reset_pic()
functions.init_ax(ser)
#ouverture du fichier
continuer = True
while continuer:

    #lecture du fichier pour savoir si l'on sort de la boucle
    mon_fichier = open("/home/pi/Eurobot_2016/RasPi/octobot/quitter.txt","r")
    if mon_fichier.read()=="exit\n":
        mon_fichier.close()
        continuer = False
        break
    mon_fichier.close()

    try:
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

	## Script de recalage ##

	functions_macro.Script_Recalage(ser,team)

	##Reattente du start

	print "waiting for start"
        answer = functions.get_ans(ser)
        while answer != "$STRT;":
            answer = functions.get_ans(ser)
            print answer

        ### SCRIPTS DE MATCH ###

#        functions.set_t(ser,team*(45))

        functions_macro.Prise_Colonne_De_Sable(ser,team,1.50,0.633)
	
#	functions_macro.Prise_Colonne_De_Sable(ser,team,0.5,0)
#        functions_macro.Prise_Colonne_De_Sable(ser,team,1.4,0.6)
        #functions_macro.Prise_Colonne_De_Sable(ser,team,1.4,0.6)
        #functions_macro.Prise_Colonne_De_Sable(ser,team,1.4,0.6)
    
    except UrgenceReleveException as e:
        print e.value

ser.close()
