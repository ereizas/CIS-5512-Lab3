#include <stdlib.h>
typedef struct ProcessNode{
   pid_t pid;
   char cmd[CMD_MAX];
   struct ProcessNode *next;
} ProcessNode;

void add_bg_proc(pid_t pid, const char *cmd);
void rm_bg_proc(pid_t pid);