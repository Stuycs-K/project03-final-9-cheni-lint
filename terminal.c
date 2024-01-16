#include "network.h"
#include "terminal.h"
#include "fileman.h"
#include "transfer.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

int error(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

char **  parse_argss( char * line, char ** arg_ary, char* c, int* a ){
    // printf("line: %s   c: %c\n", line, *c);
    int i=0;
    char* command;
    while (command = strsep(&line, c)){
        // if(command==NULL){
        //     printf("command: NULL\n");
        // }else{
        //     printf("command: %s\n", command);
        // }
        arg_ary[i] = command;
        // printf("arr[%d]: %s \n", i, arg_ary[i]);
        i++;
    }
    arg_ary[i]=NULL;
    int k=0;
    // printf("arg_ary[i-1]: %s\n", arg_ary[i-1]);
    while(arg_ary[i-1][k]){
        if(arg_ary[i-1][k]=='\n'||arg_ary[i-1][k]=='\r'){
            arg_ary[i-1][k]='\0';
            break;
        }
        k++;
    }
    *a=i;
}

char **  parse_args( char * line, char ** arg_ary, char* c){
    int i=0;
    char* command;
    while (command = strsep(&line, c)){
        arg_ary[i] = command;
        i++;
    }
    arg_ary[i]=NULL;
    int k=0;
    while(arg_ary[i-1][k]){
        if(arg_ary[i-1][k]=='\n'||arg_ary[i-1][k]=='\r'){
            arg_ary[i-1][k]='\0';
            break;
        }
        k++;
    }
}

int server_terminal(char* userinput, int client_socket){
    // setvbuf(stdout, NULL, _IONBF, 0);
    // while(1){

        char* message=calloc(1025, sizeof(char));
        char s[100];
        char** words=calloc(100,sizeof(char*));
        char ** commands=calloc(100,sizeof(char*));
        // snprintf(message, sizeof(message), getcwd(s, 100), "# ", userinput);
        strcat(message, getcwd(s, 100));
        strcat(message, "# ");
        strcat(message, userinput);
        strcat(message, "\n");
        // printf("message: %s\n", message);
        // write(client_socket, message, BUFFER_SIZE); 
        int random_ind=0;
        while(userinput[random_ind]){
            // if(userinput[random_ind]=='\r'){
            //     printf("r: %d\n", random_ind);
            //     userinput[random_ind]='\n';
            //     userinput[random_ind+1]='\0';
            //     break;
            // }
            // if(userinput[random_ind]=='\n'){
            //     printf("n: %d\n", random_ind);
            //     userinput[random_ind+1]='\0';
            //     break;
            // }
            random_ind++;
        }
        // printf("random_int: %d\n", random_ind);
        // userinput[random_ind]='\n';
        // userinput[random_ind+1]='\0';
        // printf("not terminal input: %d\n", not_terminal_input);
        // printf("command: %s\n", userinput);
        // fflush(stdout);
        int last_ind=0;
        // userinput[0]='a';
        // printf("userinput: %s\n", userinput);
        // printf("testing %s\n", strsep(&userinput, ";"));
        parse_argss(userinput, commands, ";", &last_ind);
        // printf("after parss: %s  %d\n", commands[0], last_ind);
        // printf("ahhhhh\n");

        for(int i=0;i<last_ind;i++){
            bool p=true;
            int command_length=0;
            parse_argss(commands[i], words, " ", &command_length);
            if(strcmp(words[0],"ls")==0 || strcmp(words[0],"pwd")==0){
                p=false;
            }
            if(p){
                write(client_socket, message, BUFFER_SIZE); 
            }
            // printf("commands[%d]: %s\n", i, commands[i]);
            if(strcmp(words[0],"exit")==0){
                free(words);
                free(commands);
                // free(userinput);
                printf("exit\n");
                exit(0);
            }
            else if(strcmp(words[0],"touch")==0){
                if(touch(words[1])<0) error(); 
            }
            else if(strcmp(words[0],"rm")==0){
                struct stat * stat_b=malloc(sizeof(struct stat)*1);
                if(stat(words[1], stat_b)<0) error();
                if(rm(words[1], S_ISDIR(stat_b->st_mode))<0) error();
            }
            else if(strcmp(words[0],"pwd")==0){
                if(pwd(client_socket, message)<0) error();
            }
            else if(strcmp(words[0],"cd")==0){
                if(cd(words[1])<0) error();
            }
            else if(strcmp(words[0],"ls")==0){
                if(last_ind==1){
                    if(ls(".", client_socket, message)<0) error();
                }else{
                    if(ls(words[1], client_socket, message)<0) error();
                }
            }
            else if(strcmp(words[0],"size")==0){
                struct stat * stat_b=malloc(sizeof(struct stat)*1);
                if(stat(words[1], stat_b)<0) error();
                if(size(words[1], S_ISDIR(stat_b->st_mode))<0) error();
            }
            else if (strcmp(words[0],"mkdir")==0) {
                mkdir(words[1], 0777);
            }
            else if (strcmp(words[0],"touch")==0) {
                touch(words[1]);
            }
            // else if (strcmp(words[0], "down") == 0) {
            //     transfer(words[1], client_socket);
            // }
            else printf("%s not found\n", commands[i]);
        }
        // free(userinput);
        message[0]='\0';
        free(commands);
        free(words);
        free(message);
    // }

    // printf("logout\n");
    // exit(0);
}