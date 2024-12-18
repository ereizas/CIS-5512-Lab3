/*
Author: Eric Reizas
This file is meant to provide built-in functions for the shell.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#define PATH_MAX 4096
#define PSTATUS_PATH_MAX 31
#define STR_MAX 2048
#define PSTATE_DESCR_MAX 38

/*Indicates if the shell's exit command was entered correctly
@param num_args number of arguments passed into the shell*/
_Bool shell_exit(int num_args)
{
    if(num_args==1)
    {
        return 1;
    }
    else
    {
        puts("Too many arguments.");
        return 0;
    }
}

/*This function prints information on built in commands or a specific built in command as specified by arg.
@param num_args number of arguments passed into the shell
@param args the list of string arguments passed to the shell
*/
void help(int num_args, char **args)
{
    if(num_args==1)
    {
        puts("Shell Help Manual:\nThis can run executable files, redirect input to executables and implement a pipe between processes. Executable files, their arguments, and redirection and pipe operators must be space-separated from each other.\nRedirection must be in the form:\n process1 <redirection_operator> file\n\nPiping must be in the form:\nprocess1 | process2\nBuilt in commands:\nexit\thelp (cmd)\npwd\tcd [dir]\nwait");
    }
    else if(num_args>2)
    {
        puts("Too many arguments.");
    }
    else if(!strcmp(args[1],"help"))
    {
        puts("help: help (cmd)\n\tProvides information on built-in commands or command specified by cmd");
    } 
    else if(!strcmp(args[1],"exit"))
    {
        puts("exit: exit\n\tExits the shell.");
    }
    else if(!strcmp(args[1],"pwd"))
    {
        puts("pwd: pwd\n\tPrints the current working directory.");
    }
    else if(!strcmp(args[1],"cd"))
    {
        puts("cd: cd [direc]\n\tChanges the current working directory to direc\n\tdirec must be a valid directory via absolute path or relative path.");
    }
    else if(!strcmp(args[1],"wait"))
    {
        puts("wait: wait\n\tWaits for all background processes to complete");
    }
    else
    {
        puts("Unrecognized command or command is not built in.");
    }
}
/*Prints the current working directory of the shell
@param num_args number of arguments passed into the shell*/
void pwd(int num_args)
{
    if(num_args==1)
    {
        char *path;
        //dynamically allocated bc machine mem doesn't allow for 4096 bytes for char[] to be on stack
        if((path=malloc(PATH_MAX))==NULL)
        {
            perror("malloc");
            return;
        } 
        if((getcwd(path,PATH_MAX))==NULL)
        {
            perror("getcwd");
        }
        printf("%s\n",path);
    }
    else
    {
        puts("Too many arguments.");
    }
}
/*Changes the currrent working directory of the shell to dir
@param num_args number of arguments passed into the shell
@param args string arguments passed into the shell*/
void cd(int num_args,char **args)
{
    if(num_args==2)
    {
        int ret;
        if((ret=chdir(args[1]))==-1)
        {
            perror("chdir");
        }
    }
    else
    {
        puts("cd requires exactly 2 arguments.");
    }
}
/*This function is meant to make the shell wait for all background processes to terminate.
@param num_args number of arguments passed into the shell*/
void shell_wait(int num_args)
{
    if(num_args==1)
    {
        while(waitpid(-1,NULL,0)!=-1){}
    }
    else
    {
        puts("Too many arguments.");
    }
}

/*void ps(int num_args, Proc_List *proc_list){
    for(int i = 0;i<proc_list->num_procs;++i){
        char path[PSTATUS_PATH_MAX];
        snprintf(path,sizeof(path),"/proc/%d/status",proc_list->pids[i]);
        int fd;
        if ((fd=open(path,O_RDONLY))==-1)
        {
            perror("open");
            exit(1);
        }
        char status[PSTATE_DESCR_MAX];
        status[0]='?';
        char buff[STR_MAX];
        while(status[0]=='?'){
            if(read(fd, buff,STR_MAX)==-1){
                perror("read");
                return;
            }
            char state_line_start[8] = "State:\t";
            char *state_line_ptr = strstr(buff,state_line_start);
            if(state_line_ptr){
                state_line_ptr+=strlen(state_line_start);
                while(*state_line_ptr!='('){
                    state_line_ptr++;
                }
                state_line_ptr++;
                int j=0;
                while(*state_line_ptr!=')'){
                    status[j]=*state_line_ptr;
                    j++;
                    state_line_ptr++;
                }
            }
        }
        printf("Process %d: %s\n", proc_list->pids[i], status);
    }
}*/