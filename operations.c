/*
Author: Eric Reizas
This file is meant to provide functions for execution of programs and redirection of input and output.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "non_built_in_parsing.h"
/*This function is meant to redirect input of a process from the specified file.
@param file name of the file to redirect input from
@return 0 on success and -1 on failure*/
int redirec_input(char *file)
{
    int fd;
    if((fd=open(file,O_RDONLY))==-1)
    {
        perror("open");
        return -1;
    }
    if(dup2(fd,STDIN_FILENO)==-1)
    {
        perror("dup2");
        return -1;
    }
    return 0;
}
/*This function is meant to redirect output to a specified file
@param file file name to redirect output to
@return 0 on success and -1 on failure*/
int redirec_output(char *file)
{
    int fd;
    if((fd=open(file,O_WRONLY|O_CREAT|O_TRUNC))==-1)
    {
        perror("open");
        return -1;
    }
    if(dup2(fd,STDOUT_FILENO)==-1)
    {
        perror("dup2");
        return -1;
    }
    return 0;
}
/*This function is meant to execute with or without redirection but not for pipes
@param input_file name of file that input is redirected from (NULL if none specified)
@param output_file name of file that output is redirected to (NULL if none specified)
@param exec_name name of the executable file
@param cmd list of string arguments passed to shell (null terminated after last argument)
@param bckgrnd : boolean for whether the process should run in the background*/
void execute(char *input_file, char *output_file, char *exec_name, char **cmd, _Bool bckgrnd)
{
    pid_t fork_ret = 0; int wait_status = 0;
    if((fork_ret=fork())==-1)
    {
        perror("fork");
        exit(1);
    }
    else if(fork_ret==0)
    {
        if(input_file!=NULL)
        {
            if(redirec_input(input_file)==-1)
            {
                return;
            }
        }
        if(output_file!=NULL)
        {
            if(redirec_output(output_file)==-1)
            {
                return;
            }
        }
        if(execv(exec_name,cmd)==-1)
        {
            perror("execv");
            exit(1);
        }
    }
    else
    {
        if(!bckgrnd)
        {
            if(waitpid(fork_ret,&wait_status,0)==-1)
            {
                perror("waitpid");
            }
        }
        else
        {
            if(waitpid(fork_ret,&wait_status,WNOHANG)==-1)
            {
                perror("waitpid");
            }
        }
    }
}
/*This is meant to create pipes and fork and execute program with input redirected as necessary according to the pipes.
@param args : array of string arguments in shell
@param num_pipes : number of pipe characters in args
@param bckgrnd : boolean for whether the process should run in the background*/
void pipe_loop(char **args, int num_pipes, _Bool bckgrnd)
{
    //array of all the pipes needed for the program
    int pipes[num_pipes][2];
    for(int i = 0; i<num_pipes; ++i)
    {
        if(pipe(pipes[i])==-1)
        {
            perror("pipe");
            exit(1);
        }
    }
    for(int i = 0; i<num_pipes+1;++i)
    {
        int ret = 0;
        if((ret = fork())==-1)
        {
            perror("fork");
            return;
        }
        else if(ret==0)
        {
            if(i==0) //edge case where first process can only have output redirected
            {
                if(dup2(pipes[0][1],STDOUT_FILENO)==-1)
                {
                    perror("dup2");
                    return;
                }
            }
            else if(i==num_pipes) //edge case where last process can only have input redirected
            {
                if(dup2(pipes[num_pipes-1][0],STDIN_FILENO)==-1)
                {
                    perror("dup2");
                    return;
                }
            }
            else //non-edge cases
            {
                if(dup2(pipes[i-1][0],STDIN_FILENO)==-1)
                {
                    perror("dup2");
                    return;
                }
                if(dup2(pipes[i][1],STDOUT_FILENO)==-1)
                {
                    perror("dup2");
                    return;
                }
            }
            //closing all the pipes because the necessary ones were duplicated
            for(int j = 0; j<num_pipes; ++j)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            //keeps track of number of pipes passed to help move args pointer to current process's executable name
            int num_pipes_passed = 0;
            //moves args pointer to correct executable name based on which iteration the forked process is part of
            while(num_pipes_passed<i)
            {
                if(!strcmp(*args,"|"))
                {
                    num_pipes_passed++;
                }
                args++;
            }
            char *exec_name = *args; char **cmdline = args;
            while(*args!=NULL && strcmp(*args,"|"))
            {
                args++;
            }
            //null terminates command at | char if encountered (checking for NULL first makes sure that strcmp() does not throw error)
            if(*args!=NULL && !strcmp(*args,"|"))
            {
                *args=NULL;
            }
            if(*exec_name!='.' && *exec_name!='/' && *exec_name!='~')
            {
                char *parse_env_ret = parse_env(exec_name); 
                if(parse_env_ret!=NULL)
                {
                    exec_name=parse_env_ret;
                    //makes sure that cmdline[0] is also full path to executable
                    if((cmdline[0]=strdup(exec_name))==NULL)
                    {
                        perror("strdup");
                        exit(1);
                    }
                }                      
            }
            if(execv(exec_name,cmdline)==-1)
            {
                perror("execv");
                exit(1);
            }
        }
        else
        {
            if(i>0)
            {
                close(pipes[i-1][0]);
            }
            if(i<num_pipes)
            {
                close(pipes[i][1]);
            }
            int wait_status;
            if(!bckgrnd)
            {
                if(waitpid(ret,&wait_status,0)==-1)
                {
                    perror("waitpid");
                }
            }
            else
            {
                if(waitpid(ret,&wait_status,WNOHANG)==-1)
                {
                    perror("waitpid");
                }
            }
        }
    }
    for(int j = 0; j<num_pipes; ++j)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
    }
}
