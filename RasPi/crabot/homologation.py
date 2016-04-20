#!/usr/bin/env python3


import serial
import functions

ser = serial.Serial("/dev/ttyAMA0",57600)

functions.reset_pic()
functions.init_ax(ser)

# Attente du start
print "waiting for start"
answer = functions.get_ans(ser)
while answer != "$STRT;":
    answer = functions.get_ans(ser)
    print answer

# Demande de l'equipe
team = functions.ask_team(ser)

functions.open_bras(ser)

functions.move_pos(ser,0.85,0)

answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)

functions.move_pos(ser,0.4,0)

answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)

functions.rotate(ser,team*1.5708)

answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)

functions.move_pos(ser,0.4,team*0.45)

answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)

functions.rotate(ser,0)

answer = functions.get_ans(ser)
while answer != "$DONE;":
    answer = functions.get_ans(ser)

while True:
   functions.move_pos(ser,1.1,team*0.45)
  
   answer = functions.get_ans(ser)
   while answer != "$DONE;":
      answer = functions.get_ans(ser)

   functions.move_pos(ser,0.2,team*0.45)
   answer = functions.get_ans(ser)
   while answer != "$DONE;":
       answer = functions.get_ans(ser)

ser.close()
