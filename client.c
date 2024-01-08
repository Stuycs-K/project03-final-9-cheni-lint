#include "network.h"

void clientLogic(int server_socket){
  char str[BUFFER_SIZE];
  printf("input str: \n");
  fgets(str, BUFFER_SIZE, stdin);
  send(server_socket,str,sizeof(str),0);
  read(server_socket,str,BUFFER_SIZE);
  printf("returned str: %s\n", str);
  close(server_socket);
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  printf("client connected with IP: [%s]\n", IP);
  while(1){
    // printf("stuck here\n");
    int server_socket = client_tcp_handshake(IP);
    // printf("or here\n");
    clientLogic(server_socket);
    sleep(1);
  }
}
