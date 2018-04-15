import serial

ser = serial.Serial('/dev/ttyACM0',9600)
v1=open("volt1.txt",'a')
v2=open("volt2.txt",'a')
while True:
	read_serial1=str(int(ser.readline(),10))
	read_serial2=str(int(ser.readline(),10))
	v1.write(read_serial1/n)
	v2.write(read_serial2/n)
	print read_serial1
	print read_serial2
