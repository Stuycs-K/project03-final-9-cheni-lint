#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h> 
#include <math.h>
#include <netdb.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/socket.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>


#ifndef NETWORKING_H
#define NETWORKING_H
#define PORT "6940"
#define BUFFER_SIZE 1025
void err(int i, char*message);
int server_setup();
int client_tcp_handshake(char*server_address);
int server_tcp_handshake(int listen_socket);
#endif
