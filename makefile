#Version 1.3
CC=gcc
CFLAGS= `pkg-config --cflags gtk+-2.0` -std=gnu11 -no-pie
LIBS=`pkg-config --libs gtk+-2.0`

serialgui: serialgui.c serialgui.h Constants.h makefile
	$(CC) serialgui.c $(CFLAGS) $(LIBS) -o $@ 
