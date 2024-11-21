#include "process_node.h"

/*
Adds a node to be the new head of the linked list
@param node : the current head of the list
@param pid : process id of the new process to add
@param cmd : cmd of the new process to add
@return new_node : the node added which is now the head of the list or NULL on error
*/
ProcessNode* add_bg_proc(ProcessNode *node, pid_t pid, const char *cmd){
    ProcessNode *new_node;
    if((new_node=malloc(sizeof(ProcessNode)))==NULL){
        perror("malloc");
        return NULL;
    }
    new_node->pid = pid;
    strcpy(new_node->cmd,cmd);
    new_node->next = node;
    return new_node;
}

/*
Removes a node from the linked list of processes
@param head : start of the linked list
@param pid : pid of the process node to remove
@return : the new head node if the previous head is removed, otherwise NULL
*/
ProcessNode* rm_bg_proc(ProcessNode *head, pid_t pid){
    ProcessNode *prev = NULL;
    ProcessNode *curr = head;
    while(curr!=NULL){
        if(curr->pid==pid){
            ProcessNode *next = curr->next;
            curr->next = NULL;
            prev->next=next;
            free(curr);
            if(curr==head){
                return next;
            }
            else{
                return NULL;
            }
        }
        prev = curr;
        curr=(curr->next);
    }
}