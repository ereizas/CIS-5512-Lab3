int handle_builtins(char **shell_args, int num_args);
void execute_non_built_ins(char **shell_args, int num_args);
int redirec_input(char *file);
int redirec_output(char *file,_Bool append);
void execute(char *input_file, char *output_file, char *exec_name, char **cmd, _Bool bckgrnd, _Bool append);
void pipe_loop(char **args, int num_pipes, _Bool bckgrnd);
