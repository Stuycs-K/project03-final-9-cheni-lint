#ifndef NETWORK_H
#define NETWORK_H
#define PORT "6940"
#define BUFFER_SIZE 1025
void err(int i, char*message);
int server_setup();
int client_tcp_handshake(char*server_address);
int server_tcp_handshake(int listen_socket);
#endif
