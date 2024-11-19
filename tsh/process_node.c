#include "process_node.h"

/*
Adds a node to be the new head of the linked list
@param node : the current head of the list
@param pid : process id of the new process to add
@param cmd : cmd of the new process to add
*/
ProcessNode* add_bg_proc(ProcessNode *node, pid_t pid, const char *cmd){
    ProcessNode *new_node;
    if((new_node=malloc(sizeof(ProcessNode)))==NULL){
        perror("malloc");
        return;
    }
    new_node->pid = pid;
    strcpy(new_node->cmd,cmd);
    new_node->next = node;
    return new_node;
}