#include "sys/types.h"

typedef struct{
    pid_t *pids;
    unsigned int num_procs;
    unsigned int proc_limit;
    void (*add)(struct Proc_List, pid_t new_pid);
} Proc_List;