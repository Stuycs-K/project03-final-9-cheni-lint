#include "network.h"
#include "fileman.h"
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
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

void clientLogic(int server_socket, char* str) {
  send(server_socket,str,sizeof(str),0);
  read(server_socket,str,BUFFER_SIZE);
  printf("returned str: %s\n", str);
  close(server_socket);
}

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
    clientLogic(server_socket, str);
    sleep(1);
  }
}
