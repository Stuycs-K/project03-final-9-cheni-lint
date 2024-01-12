#include "network.h"
#include "fileman.h"
#include "terminal.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int main(int argc, char *argv[] ) {
  char str[BUFFER_SIZE];
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  printf("client connected with IP: [%s]\n", IP);

  while(1){
    printf("input str: \n");
    fgets(str, BUFFER_SIZE, stdin);

    if (strcmp(str, "exit\n") == 0) {
      printf("ending process...\n");
      exit(0);
    }

    int server_socket = client_tcp_handshake(IP);

    printf("server socket connection: [%d]\n", server_socket);

    send(server_socket, str, sizeof(str), 0);

    char response[BUFFER_SIZE];
    read(server_socket, response, sizeof(response));

    close(server_socket);
    sleep(0.2);
  }
}