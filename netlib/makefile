INCL = -I../include
FLAGS = -c -O3 
OBJS = ../obj
EXTRA = 
cc = gcc

all : netlib.o wall_clock.o archive ranl move tshlib tsh

wall_clock.o : wall_clock.c
	$(cc) $(EXTRA) $(INCL) $(FLAGS) wall_clock.c $(TAIL)
netlib.o : netlib.c $(TAIL)
	$(cc) $(EXTRA)  $(INCL) $(FLAGS)  netlib.c $(TAIL)
archive : 
	ar rcv libb.a *.o
ranl:
move :
	mv libb.a ../obj/libsng.a
	/bin/rm -f *.o
tshlib: tshlib.c
	$(cc) $(EXTRA) $(INCL) -g -o tshlib tshlib.c -L$(OBJS) -lsng

tsh: tsh.c
	$(cc) $(EXTRA) $(INCL) -g -o tsh tsh.c -L$(OBJS) -lsng

clean: 
	rm tshlib tsh
