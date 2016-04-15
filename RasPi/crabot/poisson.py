#!/usr/bin/env python3

import serial
import functions

ser = serial.Serial("/dev/ttyAMA0",57600)

functions.reset_pic()

# Attente du start
print "waiting for start"
answer = functions.get_ans(ser)
while answer != "$STRT;":
    answer = functions.get_ans(ser)
    print answer

# Demande de l'equipe
team = functions.ask_team(ser)


#functions.move_pos(ser,0.25,0)
functions.move_pos(ser,0.20,0);

answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)

