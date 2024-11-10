#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "helpers.h"

/*
  Function to break up a line (or any arbitrary string) into a memory allocated
  tokenized array of strings separated by the given delimiter or set of 
  delimiters (see strtok_r for more information about delim parameter). 
  
  Note: The array as well as the individual strings will be memory allocated,
  therefore they must be freed later. 
  
  Warning: LINE MUST BE MEMORY ALLOCATED!

  @param line : An arbitrary string
  @param delim : The delimiter or set of delimiters for separating 
    the line (see strtok_r for more information)
  @param n : Pointer to number of arguments
  @return argn : The length of the array
*/
char** parse(char*line, char*delim, int *n){
  char**array=malloc(sizeof(char*));
  *array=NULL;

  char*buf = strtok(line,delim);

  if (buf == NULL){
          free(array);
          array=NULL;
          return array;
  }

  while(buf!=NULL ){

          char**temp = realloc(array,(*n+2)*sizeof(char*));

          if(temp==NULL){
                  free(array);
                  array=NULL;
                  return array;
          }

          array=temp;
          temp[(*n)++]=buf;
          temp[*n]=NULL;

          buf = strtok(NULL,delim);

  }

  return array;
}

/*Returns index of first instance of char * special
@param args : array of string arguments from the shell input
@param special : pointer to char to look for
@return i : offset from given position in args which corresponds to special's location*/
int find_special (char*args[], char * special){

	int i = 0;
	while(args[i]!=NULL){
		if(strcmp(args[i],special)==0){
			return i;
		}
		i++;
	}
	return -1;
}

