INCL = -I../include
FLAGS = -c -O3
OBJS = ../obj
EXTRA = 
cc = gcc

all: tshtest tsh

tshtest: tshtest.c helpers.o built_ins.o non_built_in_parsing.o
	$(cc) $(EXTRA) $(INCL) -g -o tshtest tshtest.c helpers.o built_ins.o non_built_in_parsing.o -L$(OBJS) -lsng

tsh: tsh.c operations.o built_ins.o non_built_in_parsing.o helpers.o
	$(cc) $(EXTRA) $(INCL) -g -o tsh tsh.c operations.o built_ins.o non_built_in_parsing.o helpers.o -L$(OBJS) -lsng

operations.o: operations.c
	$(cc) $(FLAGS) $(INCL) -o operations.o operations.c

helpers.o: helpers.c
	$(cc) $(FLAGS) $(INCL) -o helpers.o helpers.c

built_ins.o: built_ins.c
	$(cc) $(FLAGS) $(INCL) -o built_ins.o built_ins.c

non_built_in_parsing.o: non_built_in_parsing.c
	$(cc) $(FLAGS) $(INCL) -o non_built_in_parsing.o non_built_in_parsing.c

clean:
	rm tshtest tsh *.o