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
#include "operations.h"
int main(int argc, char *argv[])
{
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
        }
        else
        {
            int num_args = 0;
            //using the parse() helpers.c fxn
            char **shell_args = parse(line," \n",&num_args);
            if(shell_args!=NULL)
            {
                if(!strcmp(shell_args[0],"exit"))
                {
                    shell_exit(num_args);
                }
                else if(!strcmp(shell_args[0],"help"))
                {
                    help(num_args,shell_args);
                }
                else if(!strcmp(shell_args[0],"pwd"))
                {
                    pwd(num_args);
                }
                else if(!strcmp(shell_args[0],"cd"))
                {
                    cd(num_args,shell_args);
                }
                else if(!strcmp(shell_args[0],"wait"))
                {
                    shell_wait(num_args);
                }
                else
                {
                    if(!strcmp(shell_args[0],"|")||!strcmp(shell_args[0],"<")||!strcmp(shell_args[0],">")||!strcmp(shell_args[num_args-1],"|")||!strcmp(shell_args[num_args-1],"<")||!strcmp(shell_args[num_args-1],">"))
                    {
                        puts("Invalid syntax.");
                    }
                    else
                    {
                        //temporary pointer to keep track of start of shell_args to help free memory later
                        char **temp_start = shell_args;
                        char **cmd = temp_start;
                        //see if exec_name needs a different assignment
                        char *exec_name = *shell_args;
                        //checks for symbolic link
                        if(*exec_name!='.' && *exec_name!='/' && *exec_name!='~')
                        {
                            char *parse_env_ret = parse_env(exec_name); 
                            if(parse_env_ret!=NULL)
                            {
                                exec_name=parse_env_ret;
                            }                      
                        }
                        //checks if last arg is different from "&"
                        _Bool bckgrnd = 0;
                        if(!strcmp(shell_args[num_args-1],"&"))
                        {
                            bckgrnd = 1;
                            shell_args[num_args-1] = NULL;
                        }
                        char *input_file = NULL, *output_file = NULL;
                        char* curr_special=get_first_special(shell_args);
                        if(curr_special!=NULL && *curr_special!='|')
                        {
                            //using helper function to help move pointer to shell args forward
                            shell_args+=find_special(shell_args,curr_special);   
                            *shell_args=NULL;
                            shell_args++;
                            if(*curr_special=='<')
                            {
                                if(find_special(shell_args,"<")==-1)
                                {
                                    input_file=*shell_args;
                                    if(find_special(shell_args,">")!=-1)
                                    {
                                        output_file=*(shell_args+find_special(shell_args,">")+1);                        
                                    }
                                    execute(input_file,output_file,exec_name,cmd, bckgrnd);
                                }
                                else
                                {
                                    puts("Duplicate redirection is not allowed.");
                                }
                            }
                            else if(*curr_special=='>')
                            {
                                if(find_special(shell_args,">")==-1)
                                {
                                    output_file=*shell_args;
                                    if(find_special(shell_args,"<")!=-1)
                                    {
                                        output_file=*(shell_args+find_special(shell_args,"<")+1);
                                    }
                                    execute(input_file,output_file,exec_name, cmd, bckgrnd);
                                }
                                else
                                {
                                    puts("Duplicate redirection is not allowed.");
                                }
                            }
                        }
                        else if(curr_special!=NULL&&*curr_special=='|')
                        {
                            pipe_loop(shell_args,count_pipes(shell_args), bckgrnd);
                        }
                        else
                        {
                            execute(input_file,output_file,exec_name,cmd, bckgrnd);
                        }
                        //moves pointer back to beginning to free it
                        shell_args=temp_start;
                    }
                }
                free(line);
                free(shell_args);
            }
        }
    }
}