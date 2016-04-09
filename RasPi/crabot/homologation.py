#!/usr/bin/env python3

import serial
import functions

ser = serial.Serial("/dev/ttyAMA0",57600)

functions.reset_pic()
functions.init_ax(ser)

# Attente du start
#answer = functions.get_ans(ser)
#while answer != "$STRT;":
#    answer = functions.get_ans(ser)

# Demande de l'équipe
team = functions.ask_team(ser)

functions.open_bras(ser)

answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)

functions.move_pos(ser,0.4,0)

answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)

ser.close()
