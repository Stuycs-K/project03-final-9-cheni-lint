#include "network.h"
#include "fileman.h"
#include "terminal.h"
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int sig_handler(int signo) {
    if (signo == SIGPIPE) {
        printf("SIGPIPE caught: server not found\n");
    }
    if ( signo == SIGINT ){
        printf("SIGINT caught: killing client\n");
        exit(0);
    }
    if ( signo == SIGQUIT ){
        printf("SIGQUIT caught: killing client\n");
        exit(0);
    }
}

int main(int argc, char *argv[] ) {
  signal(SIGPIPE, sig_handler);
  signal(SIGINT, sig_handler);
  signal(SIGQUIT, sig_handler);


  char str[BUFFER_SIZE];
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  printf("client connected with IP: [%s]\n", IP);

  while(1){

      printf("> ");
      fgets(str, BUFFER_SIZE, stdin);

      if (strcmp(str, "exit\n") == 0)
      {
          printf("ending process...\n");
          exit(0);
    }

    int server_socket = client_tcp_handshake(IP);
    char* response=calloc(BUFFER_SIZE, sizeof(char));

    send(server_socket, str, sizeof(str), 0);

    read(server_socket, response, BUFFER_SIZE);
    printf("%s\n", response);

    close(server_socket);
    sleep(0.2);
    free(response);
  }
}