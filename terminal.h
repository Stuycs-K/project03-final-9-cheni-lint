#ifndef TERMINAL_H
#define TERMINAL_H

char **  parse_args( char * line, char ** arg_ary, char* c);
char **  parse_argss( char * line, char ** arg_ary, char* c, int* a );
int error();
int server_terminal(char* userinput);

#endif