#include <stdlib.h>
#include <stdio.h>
#include "proc_list.h"
/*
Adds a process id to the process list, reallocating when necessary
@param proc_list process list to add to
@param new_pid pid for the new process
*/
void add(Proc_List *proc_list, pid_t new_pid){
    if(proc_list->num_procs==proc_list->proc_limit){
        if((realloc(proc_list->pids,(proc_list->proc_limit)*2*sizeof(pid_t)))==NULL){
            perror("realloc");
            return;
        }
        proc_list->proc_limit*=2;
    }
    proc_list->pids[proc_list->num_procs]=new_pid;
    proc_list->num_procs+=1;
}

Proc_List create_proc_list(){
    Proc_List proc_list = {
        .pids=NULL,
        .num_procs=0,
        .proc_limit=10,
        .add=add
    };
    if((proc_list.pids=malloc(proc_list.proc_limit*sizeof(typeof(proc_list.pids))))==-1){
        perror("malloc");
        exit(1);
    }
    return proc_list;
}