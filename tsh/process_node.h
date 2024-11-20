#include <stdlib.h>
#include "synergy.h"
typedef struct ProcessNode{
   pid_t pid;
   char cmd[CMD_MAX];
   struct ProcessNode *next;
} ProcessNode;

ProcessNode* add_bg_proc(ProcessNode *node, pid_t pid, const char *cmd);
ProcessNode* rm_bg_proc(ProcessNode *node, pid_t pid);