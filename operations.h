int handle_builtins(char **shell_args, int num_args);
void execute_non_built_ins(char **shell_args, int num_args, pid_t *pids, unsigned int *num_procs, unsigned int *proc_limit);
int redirec_input(char *file);
int redirec_output(char *file,_Bool append);
void execute(char *input_file, char *output_file, char *exec_name, char **cmd, _Bool bckgrnd, _Bool append, pid_t *pids, unsigned int *num_procs, unsigned int *proc_limit);
void pipe_loop(char **args, int num_pipes, _Bool bckgrnd);
