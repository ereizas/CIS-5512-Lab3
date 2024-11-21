#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#define CMD_MAX 4096
typedef struct ProcessNode{
   pid_t pid;
   char cmd[CMD_MAX];
   struct ProcessNode *next;
} ProcessNode;

ProcessNode* add_bg_proc(ProcessNode *node, pid_t pid, const char *cmd);
ProcessNode* rm_bg_proc(ProcessNode *node, pid_t pid);