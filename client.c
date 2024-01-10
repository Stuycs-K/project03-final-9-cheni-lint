#include "network.h"

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

    if (strcmp(str, "end\n") == 0) {
      printf("ending process...\n");
      exit(0);
    }

    int server_socket = client_tcp_handshake(IP);
    printf("server socket connection: [%d]\n", server_socket);
    clientLogic(server_socket, str);
    sleep(1);
  }
}
