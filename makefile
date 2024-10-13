shell: helpers.o built_ins.o non_built_in_parsing.o operations.o proc_list.o
	gcc -o shell shell.c helpers.o built_ins.o non_built_in_parsing.o operations.o proc_list.o -Wall -Werror
helpers.o: helpers.c
	gcc -c helpers.c
built_ins.o: built_ins.c
	gcc -c built_ins.c
non_built_in_parsing.o: non_built_in_parsing.c
	gcc -c non_built_in_parsing.c
operations.o: operations.c
	gcc -c operations.c
proc_list.o: proc_list.c
	gcc -c proc_list.c
clean:
	rm *.o shell
