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
	rm *.o shell
