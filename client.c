#include "networking.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <sys/socket.h> 
#include <netdb.h>

void clientLogic(int server_socket){
  char str[BUFFER_SIZE];
  printf("input str: \n");
  fgets(str, BUFFER_SIZE, stdin);
  send(server_socket,str,sizeof(str),0);
  read(server_socket,str,BUFFER_SIZE);
  printf("modified str: %s\n", str);
  close(server_socket);
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  printf("client connected with IP: [%s]\n", IP);
  while(1){
    int server_socket = client_tcp_handshake(IP);
    clientLogic(server_socket);
    sleep(1);
  }
}
