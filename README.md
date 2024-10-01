# Project-2-S23

## Synopsis

For this project, I implemented a shell that could execute files given to it with arguments and it has some built in commands. Also, input and output can be redirected from and to files, and pipes can be used.

## Instructions for Compiling and Running on Linux server

1. Once the zip file is unzipped to a certain location, go to that directory and make sure all the files are present.
2. Type "make" into the terminal or commandline and press Enter.
3. Type "./shell" and then type "help" to see the help manual for the shell on how to use it.git a

## Initial Pseudocode

### Main Program
```
while(1)
{
    printf("%s", "<My_Shell> ");
    char *line;
    getline(&line);
    char **token_arr = parse(line);
    char built_ins[][] = {"help","exit","pwd","cd","wait"};
    if(token_arr[0] in built_ins)
    {
        execute(token_arr[0]);
    }
    else
    {
        if(token_arr[0] in "><|" or token_arr[num_args-1] in "><|")
        {
            puts("Invalid syntax");
        }
        else
        {
            int num_specials = 0;
            while(*token_arr!=NULL)
            {
                if(*token_arr in "><|")
                {
                    num_specials++;
                }
            }
            char **temp_start = token_arr;
            do
            {
                char *exec_name = *token_arr;
                char curr_special = NULL;
                while(*token_arr not in "><|NULL")
                {
                    token_arr++;
                }
                if(*token_arr is NULL)
                {
                    int ret = 0; int wait_status = 0;
                    if((ret=fork())==-1)
                    {
                        perror("fork");
                    }
                    else if(ret==0)
                    {
                        if(execv(exec_name,temp_start)==-1)
                        {
                            perror("execv");
                            exit(1);
                        }
                    }
                    else
                    {
                        waitpid(ret, &wait_status, NO_HANG);
                    }
                }
                else
                {
                    curr_special = **token_arr;
                    *token_arr = NULL;
                    int ret = 0, wait_status = 0;
                    if((ret=fork())==-1)
                    {
                        perror("fork");
                    }
                    else if(ret==0)
                    {
                        if(curr_special is "<" or curr_special is ">")
                        {
                            if(redirec(*curr_special,*(token_arr+1))!=-1 )
                            {
                                if(execv(exec_name,temp_start)==-1)
                                {
                                    perror("execv");
                                    exit(1);
                                }
                            }
                        }
                        else if(curr_special is "|")
                        {
                            int ret2 = 0, wait_status2 = 0;
                            int fd_arr[2];
                            pipe(fd_arr;)
                            if((ret2=fork())==-1)
                            {
                                perror("fork");
                            }
                            else if(ret2==0)
                            {
                                close(stdout);
                                if(dup2(fd[1],stdin)==-1)
                                {
                                    perror("dup2");
                                    exit(1;)
                                }
                                if(execv(*(token_arr+1),getargv(token_arr+1))==-1)
                                {
                                    perror("execv");
                                    exit(1);
                                }
                            }
                            else
                            {
                                close(stdin);
                                if(dup2(stdout,fd[0])==-1)
                                {
                                    perror("dup2");
                                    exit(1;)
                                }
                                if(execv(*(token_arr+1),getargv(token_arr+1))==-1)
                                {
                                    perror("execv");
                                    exit(1);
                                }
                            }
                        }
                    }

                }
            }while(num_specials>0);
                    
        }
    }
}
```

### built_ins.c

```
void exit()
{
    exit();
}

void help(char *arg)
{
    if(*arg=='\0')
    {
        print_help's_use(syntax)_and_description_of_built_ins;
    }
    else
    {
        print_info_about_arg;
    }
}

void cd(char *path)
{
    int ret = chdir(path);
    if(ret==-1)
    {
        perror("chdir");
    }
}

void pwd()
{
    char *path;
    if((path=malloc(MAX_PATH))==NULL)
    {
        perror("malloc");
        return;
    }
    if(getcwd(path,MAX_PATH)==NULL)
    {
        perror("getcwd");
    }
    printf("%s\n",path);
}
```

### non_built_in_operations.c

```
//op will only ever be '>' or '<'
//returns -1 on error
int redirec(char op, char* path)
{
    int ret = 0, fd;
    if((fd=open(path,O_RDONLY))==-1)
    {
        perror("open");
    }
    else
    {
        if(op=='<')
        {
            if(dup2(fd,stdin)==-1)
            {
                perror("dup2");
                ret = -1;
            }
        }
        else(op=='>')
        {
            if(dup2(stdout,fd)==-1)
            {
                perror("dup2");
                ret = -1;
            }
        }
    }
    return ret;
}
```

## Testing (command -> expected output)

1. dir -> write directory contents to stdout
2. pwd -> write current working directory to stdout
3. ls | wc -> wc output given ls's output
4. ls > file -> file has contents of current directory written to it
5. echo "file" -> "file" is written to stdout
6. wc < file -> wc is executed with file as input
7. ls | grep shell -> file names that have the string "shell" in them are written to stdout
8. ls | grep shell | wc -> same as last commandline but those file names are used as input for wc
9. ls | grep shell | sleep 5 & -> process runs in the background for about 5 seconds
10. sleep 5 & -> similar to above
11. sleep 2 -> shell does not execute commandline for 2 seconds
12. exit -> shell exits and regular terminal now takes user input

## Program Structure

### built_ins.c

#### shell_exit

Checks to make sure no arguments after exit have been entered and uses the system call exit.

#### help

If there are no arguments after help, then the manual for how to use the shell is printed. If help and then the name of a built-in command is entered, then the purpose of the command is printed. Otherwise an error message will appear.

#### pwd

This checks to make sure there are no arguments after pwd. Next, it allocates memory for the variable path, assigns it the current working directory, using the cwd() system call. Finally, it prints the cwd.

#### cd

This checks to make sure there is only one argument after cd and uses the chdir() system call if that is the case.

#### shell_wait

This checks to make sure there are no arguments after the call to wait and then begins a while loop checking if -1 is returned from the waitpid() call which waits for any child process.

### helpers.c

#### parse

First, this dynamically allocates array which will be returned at the end. Next, the tokenization of line begins, and if there is no character matching the delimeters, NULL is returned. If there are tokens found, a temporary array is assigned the pointer returned when reallocating memory for array. The array is allocated (*n+2)*sizeof(char*) because this allows for there to be space for the string before the delimeter and another space for the NULL terminator of the array which is assigned later in the while loop.

#### find_special

An int i is initialized to keep track of where in args the program is and where special will be. In the while loop, the program makes sure to check that it hasn't reached the NULL terminator of the array, and compares the current element to special. If it is equal to special, then i is returned, otherwise i is incremented.

### non_built_in_parsing.c

#### count_pipes

The variables count and i are initialized to keep track of number of pipes and current index respectively. The while loop keeps going as long as args at index i is not the null terminator. The variable count is incremented when args at index i is a pipe character.

#### get_first_special

The while loop checks to make sure that the NULL ending has not been reached and checks to make sure that the current memory location does not point to any of the special characters:  >, <, or |. If it does then, the pointer to the character will be returned. If there is no special character, NULL will be returned.

#### parse_env

First, env is assigned the PATH environment. Then a copy, env_cpy, is made via strdup so that future calls to getenv, still return the correct path since getenv returns a pointer to the PATH environment variable and strtok (used later) changes what is passed into it. Next, env_cpy is tokenized using ":" as the delimiter. During each iteration of the elements of env_paths as tokenized by the helper.c function parse, a string, path, is declared and has env_path at index i copied to it, and a "\" and then exec_name are concatenated to it. Finally, using access, the program checks if it is a valid absolute path and returns that path if it is the case.

### operations.c

#### redirec_input & redirec_output

A file descriptor, fd, is created when opening the file specified by the variable file. Then dup2 makes STDIN or STDOUT file descriptors point to the file instead and they close the pointer to where STDIN and STDOUT originally pointed.

#### execute

First a child process is forked from the parent. If the current executing process with this code is the child, and input_file and output_file are not NULL (meaning there was the appropriate redirection operator and a file name following the operator), then input and output are redirect accordingly. Then the executable specified by exec_name is executed. If the process in control is the parent and "&" is not the last argument, then it waits for the child to finish. If the parent process is in control and "&" is the last argument, then the parent calls waitpid() with the WNOHANG flag so that other processes may run.

#### pipe_loop

First, all the necessary pipes are created. Next, for each process (since # of processes == # of pipes+1), a child process is forked from the parent. If the process in control is the child, input and/or output is redirected according to certain cases. If the program is at the first process, then output is redirected to write end of the first pipe. If the program is at the last process, then input is redirected to the last pipe's read end. Otherwise, input is redirected to the previous pipe's read end, and output is redirected to the next pipe's write end. Then, all the pipes are closed for the child process and num_pipes_passed is initialized. Since the number of pipes passed will equal the number of processes, we will want to have passed, a while loop iterates on this premise. If the current argument pointed to in args is "|", then num_pipes_passed is incremented. To continue progressing through the loop, the args pointer is also incremented. The variables exec_name and cmdline are assigned to the string args points to and the current pointer assigned to args respectively. Then args is incremented until the next pipe char or NULL, and if the pointer points to the pipe char, it is assigned to point to NULL so that cmdline is null terminated after its last argument. After that, if exec_name's first character is not a symbolic link or a "/" then the environment path variable is parsed to find exec_name in it. To end the child process, the file named by exec_name is executed. In the parent, the process close the pipe ends that the child process wishes to use. If the process in control is the parent and "&" is not the last argument, then it waits for the child to finish. If the parent process is in control and "&" is the last argument, then the parent calls waitpid() with the WNOHANG flag so that other processes may run. Lastly, after the for loop ends, another for loop closes all the pipes.

### shell.c 

First, the string variable line is memory allocated, assigned to the line retrieved from STDIN, and parse into an array of strings delimited by " " and "\n". There are else statements following errors so that the program does not continue if there is an error critical to the execution of the program, and there are no exit() calls except the first, so that the shell can keep running. Next, the program compares the first argument of shell_args to see if it matches the name of any of the built_in commands. If it does, the functions that correspond to those built in commands are called. Otherwise, there is a lot more parsing done. If there is an operator character in the beginning or end of the shell_args string list, then an error message is printed and the shell will prompt the user again for another command. Otherwise, the program can begin parsing. If there is no symbolic link or "\" as the first character of exec_name, then the environment path variable is parsed to see if the command lies within those directories. Then, curr_special is assigned to the pointer to the first special character in shell_args. If curr_special is neither NULL nor the pipe character, then shell_args is incremented to the location of the first redirection character found and set to NULL and incremented again. Depending on what the redirection operator was, input or output are set accordingly and if the other redirection character is present in shell_args as indicated by find_special, then output file is assigned to the string after that operator. After that, execute() is called. On the other hand, if curr_special is not null, but the pipe character, then pipe_loop() is called with the appropriate arguments. Otherwise, the executable file is executed with no redirection. Finally, shell_args get reassigned to the starting pointer, and line and shell_args are deallocated.