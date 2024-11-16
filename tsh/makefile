INCL = -I../include
FLAGS = -c -O3 
OBJS = ../obj
EXTRA = 
cc = gcc

all: tshtest tsh

tshtest: tshtest.c
	$(cc) $(EXTRA) $(INCL) -g -o tshtest tshtest.c -L$(OBJS) -lsng

tsh: tsh.c
	$(cc) $(EXTRA) $(INCL) -g -o tsh tsh.c -L$(OBJS) -lsng

clean: 
	rm tshtest tsh