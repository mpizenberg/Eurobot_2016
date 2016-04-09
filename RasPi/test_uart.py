import serial


ser = serial.Serial("/dev/ttyAMA0",57600)

#declare le demarrage de 90s de jeu
s=ser.read(1)
chaine=""
while s!=';' :
	chaine += s
	s=ser.read(1)
chaine += s
print chaine

chaine="$TEAM;"
ser.write(chaine)

s=ser.read(1)
chaine=""
while s!=';' :
	chaine += s
        s=ser.read(1)
chaine += s
print chaine

