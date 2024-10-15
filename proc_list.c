#include <stdlib.h>
#include <stdio.h>
#include "proc_list.h"
#include "sys/types.h"
/*
Adds a process id to the process list, reallocating when necessary
@param proc_list process list to add to
@param new_pid pid for the new process
*/
void add(Proc_List *proc_list, pid_t new_pid){
    if(proc_list->num_procs==proc_list->proc_limit){
        pid_t *new_pids = realloc(proc_list->pids, (proc_list->proc_limit * 2) * sizeof(pid_t));
        if (new_pids == NULL) {
            perror("realloc");
            return;
        }
        proc_list->pids = new_pids;
    }
    proc_list->pids[proc_list->num_procs]=new_pid;
    proc_list->num_procs+=1;
}

/*
Searches for the target pid and return index if found or -1 if not found
@param proc_list pointer to the struct with the pids
@param target pid to look for
*/
int search(struct Process_List *proc_list, pid_t target){
    for(int i=0;i<proc_list->num_procs;++i){
        if(proc_list->pids[i]==target)
        {
            return i;
        }
    }
    return -1;
}

Proc_List create_proc_list(){
    Proc_List proc_list = {
        .pids=NULL,
        .num_procs=0,
        .proc_limit=10,
        .add=add
    };
    if((proc_list.pids=malloc(proc_list.proc_limit*sizeof(pid_t)))==NULL){
        perror("malloc");
        exit(1);
    }
    return proc_list;
}