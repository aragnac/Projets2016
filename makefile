
CC=gcc

all:	cli	ser


lib2016BNSF.o:	lib2016BNSF.c	lib2016BNSF.h	data.h	
		echo "compilation de lib2016"
		$(CC) lib2016BNSF.c -c 

admin.o:	admin.c admin.h
		echo "compilation de admin"
		$(CC) admin.c -c

udplib.o:	../udplib/udplib.c ../udplib/udplib.h
	echo "Compilation de udplib.o"
		$(CC) ../udplib/udplib.c -c	

cli:	cli.c udplib.o admin.o lib2016BNSF.o
	echo "Compilation de client"
	$(CC) cli.c udplib.o admin.o lib2016BNSF.o -o cli

ser:	ser.c udplib.o admin.o lib2016BNSF.o
	echo "Compilation de serveur"
	$(CC) ser.c udplib.o admin.o lib2016BNSF.o -o ser

