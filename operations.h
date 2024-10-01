int redirec_input(char *file);
int redirec_output(char *file);
void execute(char *input_file, char *output_file, char *exec_name, char **cmd, _Bool bckgrnd);
void pipe_loop(char **args, int num_pipes, _Bool bckgrnd);
