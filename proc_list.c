#include <stdlib.h>
#include "proc_list.h"
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