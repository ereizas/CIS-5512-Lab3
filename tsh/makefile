INCL = -I../include
FLAGS = -c -O3 
OBJS = ../obj
EXTRA = 
cc = gcc

all: tshlib tsh

tshlib: tshlib.c
	$(cc) $(EXTRA) $(INCL) -g -o tshlib tshlib.c -L$(OBJS) -lsng

tsh: tsh.c
	$(cc) $(EXTRA) $(INCL) -g -o tsh tsh.c -L$(OBJS) -lsng

clean: 
	rm tshlib tsh