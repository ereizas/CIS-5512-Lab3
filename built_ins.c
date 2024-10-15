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
#include "proc_list.h"
#define PATH_MAX 4096

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
/* Terminates a background process started by the shell
@param num_args number of arguments passed into the shell
@param args args string arguments passed into the shell
@param proc_list pointer to object for list of background process ids
*/
void shell_kill(int num_args, char **args, Proc_List *proc_list){
    if(num_args==2){
        int wait_status = 0;
        pid_t pid = atoi(args[1]);
        if(kill(pid, SIGTERM)==-1){
            perror("kill");
            return;
        }
        if(waitpid(pid,&wait_status,0)==-1)
        {
            perror("waitpid");
        }
        printf("Process %d terminated\n", pid);
    }
    else{
        puts("Usage: kill <pid>");
    }
}