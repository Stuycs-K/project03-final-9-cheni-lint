#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h>
#include <string.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/wait.h>

#ifndef COMMAND_H
#define COMMAND_H

char **  parse_args( char * line, char ** arg_ary, char* c);
char **  parse_argss( char * line, char ** arg_ary, char* c, int* a );
int error();
int server_terminal(char* userinput);

#endif