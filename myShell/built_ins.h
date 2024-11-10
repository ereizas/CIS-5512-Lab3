_Bool shell_exit(int num_args);
void help(int num_args, char **args);
void pwd(int num_args);
void cd(int num_args, char **args);
void shell_wait(int num_args);
void shell_kill(int num_args, char **args, Proc_List *proc_list);
void killall(int num_args, Proc_List *proc_list);
void ps(int num_args, Proc_List *proc_list);