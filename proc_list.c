#include "sys/types.h"
typedef struct{
    pid_t *pids;
    unsigned int num_procs;
    unsigned int proc_limit;
} Proc_List;