#define LINE_MAX 4096 

char** parse(char*line, char*delim, int* n);
int find_special (char*args[], char * special);
void parse_opts(int argc, char *const argv[],_Bool *interactive);