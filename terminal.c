#include "network.h"
#include "terminal.h"
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
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <signal.h>

int error(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

char **  parse_argss( char * line, char ** arg_ary, char* c, int* a ){
    int i=0;
    char* command;
    while (command = strsep(&line, c)){
        if(arg_ary[i]==NULL){
        }
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

int main(){
    setvbuf(stdout, NULL, _IONBF, 0);
    while(1){
        char** words=calloc(100,sizeof(char*));
        char ** commands=calloc(100,sizeof(char*));
        char * userinput=calloc(256, sizeof(char));
        printf("%s$ ", getcwd(s, 100));
        if(fgets(userinput, 256, stdin)==NULL){
            ferror(stdin);
            // printf("NULLL\n");
        }
        // printf("userinput : %s\n", userinput);
        if(userinput[0]=='e'&&userinput[1]=='x'&&userinput[2]=='i'&&userinput[3]=='t'&&userinput[4]!='\n'){
            printf("exit\n");
            exit(0);
        }
        bool need_to_add_null=true;
        bool not_terminal_input=false;
        int random_ind=0;
        while(userinput[random_ind]){
            if(userinput[random_ind]=='\r'){
                need_to_add_null=false;
                not_terminal_input=true;
                // printf("equal r\n");
            }
            if(userinput[random_ind]=='\n'){
                need_to_add_null=false;
                not_terminal_input=true;
                // printf("equal n\n");
            }
            if(userinput[random_ind]=='\0'){
                // printf("equal 0\n");
            }
            random_ind++;
        }
        // printf("userinput need to be nulled %d  equal 0: %d\n", need_to_add_null,*userinput!='\0');
        if(need_to_add_null&&*userinput!='\0'){
            strcat(userinput, "\n");
            strcat(userinput, "\r");
            not_terminal_input=true;
        }
        if(*userinput=='\0'||*userinput=='\r'){
            printf("End of File\nlogout\n");
            exit(0);
        }
        // printf("not terminal input: %d\n", not_terminal_input);
        if(not_terminal_input){
            printf("%s", userinput);
        }
        fflush(stdout);
        int last_ind=0;
        parse_argss(userinput, commands, ";", &last_ind);


        for(int i=0;i<last_ind;i++){
            int command_length=0;
            char** words=calloc(100,sizeof(char*));
            parse_argss(commands[i], words, " ", &command_length);
            if(strcmp(words[0],"exit")==0){
                free(words);
                free(commands);
                free(userinput);
                printf("exit\n");
                exit(0);
            }
            if(strcmp(words[0],"touch")==0){
                if(touch(words[1])<0) error(); 
            }
            if(strcmp(words[0],"rm")==0){
                struct stat * stat_b=malloc(sizeof(struct stat)*1);
                if(stat(words[1], stat_b)<0) error();
                if(rm(words[1], S_ISDIR(statbuf.st_mode))<0) error();
            }
            if(strcmp(words[0],"pwd")==0){
                if(pwd()<0) error();
            }
            if(strcmp(words[0],"cd")==0){
                if(cd(words[1])<0) error();
            }
            if(strcmp(words[0],"ls")==0){
                if(ls(words[1])<0) error();
            }
            if(strcmp(words[0],"size")==0){
                struct stat * stat_b=malloc(sizeof(struct stat)*1);
                if(stat(words[1], stat_b)<0) error();
                if(size(words[1], S_ISDIR(statbuf.st_mode))<0) error();
            }
            if(strcmp(words[0],"rpath")==0){
                // char * rpath(words[1], struct dirent * entry);
            }
        }
        free(words);
        free(userinput);
        free(commands);
    }


    printf("logout\n");
    exit(0);
}