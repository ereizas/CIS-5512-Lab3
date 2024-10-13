/*
Author: Eric Reizas
This is the main file in which the shell will be ran.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "built_ins.h"
#include "non_built_in_parsing.h"
#include "proc_list.h"
#include "operations.h"
int main(int argc, char *argv[])
{
    Proc_List proc_list = create_proc_list();
    while(1)
    {
        printf("%s", "<My_Shell>:");
        pwd(1);
        printf("%c",'$');
        char *line; size_t len;
        if((line=malloc(LINE_MAX))==NULL)
        {
            perror("malloc");
            exit(1);
        }
        if(getline(&line,&len,stdin)==-1)
        {
            perror("getline");
            free(line);
            continue;
        }
        int num_args = 0;
        //using the parse() helpers.c fxn
        char **shell_args = parse(line," \n",&num_args);
        if(shell_args!=NULL)
        {
            if (!handle_builtins(shell_args, num_args)) {
                execute_non_built_ins(shell_args, num_args,&proc_list);
            }
            free(shell_args);
        }
        free(line);
    }
    free(proc_list.pids);
}