shell: helpers.o  non_built_in_parsing.o operations.o
	gcc -o shell shell.c helpers.o non_built_in_parsing.o operations.o -Wall -Werror
helpers.o: helpers.c
	gcc -c helpers.c
non_built_in_parsing.o: non_built_in_parsing.c
	gcc -c non_built_in_parsing.c
operations.o: operations.c
	gcc -c operations.c
clean:
	rm *.o shell
