INCL = -I../include
FLAGS = -c -O3 
OBJS = ../obj
EXTRA = 
cc = gcc

all: tshtest tsh shell

tshtest: tshtest.c
	$(cc) $(EXTRA) $(INCL) -g -o tshtest tshtest.c -L$(OBJS) -lsng

tsh: tsh.c
	$(cc) $(EXTRA) $(INCL) -g -o tsh tsh.c -L$(OBJS) -lsng

shell: helpers.o built_ins.o non_built_in_parsing.o operations.o
	gcc -o shell shell.c helpers.o built_ins.o non_built_in_parsing.o operations.o -Wall -Werror
helpers.o: helpers.c
	gcc -c helpers.c
built_ins.o: built_ins.c
	gcc -c built_ins.c
non_built_in_parsing.o: non_built_in_parsing.c
	gcc -c non_built_in_parsing.c
operations.o: operations.c
	gcc -c operations.c

clean: 
	rm tshtest tsh *.o shell