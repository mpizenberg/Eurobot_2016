#!/usr/bin/env python3

import serial
import functions
import Functions_battle
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

configuration = 2
while configuration==0:
	configuration = functions.ask_conf(ser)
	
ReDo = 0;
###############################
## DEBUT DE ROUTINE DE MATCH ##
###############################

IsDone = Prise_Petit_Tas_De_Sable(ser,team,configuration)
#	if IsDone > ReDo:
#		ReDo = IsDone
IsDone = Recaler_Coquillage(ser,team,configuration)
IsDone = Fermeture_Portes(ser,team)
IsDone = Prise_Grand_Tas_De_Sable(ser,team,configuration)
IsDone = Prise_Poissons(ser,team)
IsDone = Prise_Coquillages_1(ser,team,configuration)
IsDone = Prise_Coquillages_2(ser,team,configuration)

'''	
if ReDo == 0:
	print "J'ai fini !"
elif ReDo == 1:
	Recaler_Coquillage(ser,team,configuration)
elif ReDo == 2:
	Prise_Coquillages_1(ser,team,configuration)
elif ReDo == 3:
	Prise_Petit_Tas_De_Sable(ser,team,configuration)
elif ReDo == 4:
	Fermeture_Portes(ser,team)
elif ReDo == 6:
	Prise_Grand_Tas_De_Sable(ser,team,configuration)
elif ReDo == 5:
	Prise_Poissons(ser,team)
'''

ser.close()

