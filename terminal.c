#include "network.h"
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
#include "command.h"
#include <signal.h>

int main(){
    setvbuf(stdout, NULL, _IONBF, 0);
    while(1){
        char s[100];
        bool no_cd=true;
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
            printf("logout\n");
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
            if(strcmp(commands[i],"exit")==0){
                free(commands);
                free(userinput);
                printf("logout\n");
                exit(0);
            }
            char checker[300];
            int count = 0;
            while(count < strlen(commands[i])){
                checker[0] = commands[i][count];
                checker[1] = commands[i][count+1];
                if(strcmp("cd", checker)==0){
                    cd_command(commands[i]);
                    count = strlen(commands[i])+1;
                    no_cd=false;
                }
                else{
                    count++;
                }
            }
            char ** args=calloc(64,sizeof(char*));
            char * args2[64];
            char userinputcpy[300];
            strcpy(userinputcpy, commands[i]);
            char bahaha[256];
            strcpy(bahaha, commands[i]);
            parse_args( bahaha, args, " " );
            int index=0;
            while(args[index]){
                index++;
            }
            int argslength=index;

            int in=STDIN_FILENO;
            int out=STDOUT_FILENO;
            int backup_stdout = dup( STDOUT_FILENO ); 
            int backup_stdin = dup( STDIN_FILENO ); 
            int orig=0;
            index=0;
            bool have_pipe=false;
            bool have_redir=false;
            char** command=calloc(100,sizeof(char*));
            int n_of_red=0;
            char* rein=strchr(commands[i], '<');
            char* reout=strchr(commands[i], '>');
            char* reoutout=strstr(commands[i], ">>");
            char* repipe=strchr(commands[i], '|');
            int ind=0;
            if(reout!=NULL&&reoutout==NULL){
                n_of_red++;
                while(strcmp(args[ind],">")!=0){
                    ind++;
                }
                out=open(args[ind+1], O_WRONLY | O_CREAT | O_TRUNC, 0700);
                ind=0;
                have_redir=true;
            }
            if(reoutout!=NULL){
                n_of_red++;
                while(strcmp(args[ind],">>")!=0){
                    ind++;
                }
                out=open(args[ind+1], O_WRONLY | O_CREAT | O_APPEND, 0700);
                ind=0;
                have_redir=true;
            }
            if(rein!=NULL){
                n_of_red++;
                while(strcmp(args[ind],"<")!=0){
                    ind++;
                }
                in=open(args[ind+1], O_RDONLY | O_CREAT, 0700);
                ind=0;
                have_redir=true;
            }
            if(repipe!=NULL){
                n_of_red++;
                while(strcmp(args[ind],"|")!=0){
                    ind++;
                }
                have_pipe=true;
            }

            int tem=0;
            while(args[tem]){
                tem++;
            }
            
            if(have_pipe){
                char* command1[100];
                char* command2[100];
                int end=0;
                for(int i=0;strcmp(args[i], "<")!=0&&strcmp(args[i], "|")!=0;i++){
                    command1[i]=args[i];
                    end=i;
                }
                command1[end+1]=NULL;
                end=0;
                int pipe_ind=0;
                while(args[pipe_ind]){
                    if(strcmp(args[pipe_ind], "|")==0){
                        break;
                    }
                    pipe_ind++;
                }
                if(reoutout!=NULL){
                    for(int i=pipe_ind+1;i<argslength&&strcmp(args[i], ">>")!=0;i++){
                    command2[i-pipe_ind-1]=args[i];
                    end=i-pipe_ind-1;
                }
                }else{
                    for(int i=pipe_ind+1;i<argslength&&strcmp(args[i], ">")!=0;i++){
                    command2[i-pipe_ind-1]=args[i];
                    end=i-pipe_ind-1;
                }
                }
                command2[end+1]=NULL;
                int smt=0;
                while(command1[smt]){
                    smt++;
                }
                smt=0;
                while(command2[smt]){
                    smt++;
                }
                mypipe(command1, command2, in, out);
            }else if(have_redir){
                char* command[100];
                int end=0;
                for(int i=0;strcmp(args[i], "<")!=0&&strcmp(args[i], ">")!=0&&strcmp(args[i], ">>")!=0;i++){
                    command[i]=args[i];
                    end=i;
                }
                command[end+1]=NULL;
                if(no_cd){
                    fork_command_new(command, &in, &out);
                }
            }else{
                if(no_cd){
                    fork_command_new(args, &in, &out);
                }
            }
            dup2(backup_stdin, STDIN_FILENO); 
            dup2(backup_stdout, STDOUT_FILENO); 
            free(args);
            remove("you_can_not_guess_this_name.txt");
        }
        free(userinput);
        free(commands);
    }
    printf("logout\n");
    exit(0);
}