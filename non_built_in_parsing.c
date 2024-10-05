/*
Author: Eric Reizas
This is meant to provide functions to parse commands given to shell that do not involve built-in commands.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "helpers.h"
/*This function counts the number of pipe characters within the args array.
@param args : Array of strings
@return count : Number of special pipes*/
int count_pipes(char **args)
{
    int count = 0, i = 0;
    while(args[i]!=NULL)
    {
        if(!strcmp(args[i],"|"))
        {
            count++;
        }
        i++;
    }
    return count;
}

/*Returns a pointer to the next special character (> < or |)
@param args : Array of strings
@return : the pointer to the next special character or NULL if there are no more special characters*/
char* get_first_special(char *args[])
{
    while(*args!=NULL && strcmp(*args,"|") && strcmp(*args,"<") && strcmp(*args,">>") && strcmp(*args,">"))
    {
        args++;
    }
    return *args;
}
/*This function is meant to parse the enviroment paths returned by getenv to find exec_name within those paths and return the absolute path of that file
@param exec_name name of the executable file to search for in the env paths
@return path : full path or NULL if not found in path env*/
char* parse_env(char *exec_name)
{
    char *env;
    if((env=getenv("PATH"))==NULL)
    { 
        perror("getenv");
        return NULL;
    }
    char *env_cpy = strdup(env);
    int num_env_paths = 0;
    char **env_paths = parse(env_cpy,":",&num_env_paths);
    for(int i = 0; i<num_env_paths; ++i)
    {
        char *path;
        if((path=malloc(LINE_MAX))==NULL)
        {
            perror("malloc");
            return NULL;
        }
        strcpy(path,env_paths[i]);
        strcat(path,"/");
        strcat(path,exec_name);
        if(access(path,F_OK)==0)
        {
            return path;
        }
    }
    return NULL;    
}

