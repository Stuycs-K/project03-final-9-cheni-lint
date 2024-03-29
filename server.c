#include "network.h"
#include "fileman.h"
#include "terminal.h"
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdbool.h>

int sig_handler(int signo) {
    if (signo == SIGPIPE) {
        printf("SIGPIPE caught\n");
    }
    if ( signo == SIGINT ){
        printf("SIGINT caught: killing server\n");
        exit(0);
    }
    if ( signo == SIGQUIT ){
        printf("SIGQUIT caught: killing server\n");
        exit(0);
    }
}

int main() {

    signal(SIGPIPE, sig_handler);
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);

    struct addrinfo *hints, *results;
    hints = calloc(1,sizeof(struct addrinfo));

    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM; //TCP socket
    hints->ai_flags = AI_PASSIVE; //only needed on server
    getaddrinfo(NULL, PORT, hints, &results);  //NULL is localhost or 127.0.0.1

    //create socket
    int listen_socket = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

    //this code allows the port to be freed after program exit.  (otherwise wait a few minutes)
    int yes = 1;
    if ( setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1 ) {
        printf("sockopt  error\n");
        printf("%s\n",strerror(errno));
        exit(-1);
    }

    int err = bind(listen_socket, results->ai_addr, results->ai_addrlen);
    if(err == -1){
        printf("Error binding: %s",strerror(errno));
        exit(1);
    }
    listen(listen_socket, 3);//3 clients can wait to be processed
    printf("Listening on port %s\n",PORT);

    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);

    int client_sockets[100];
    for (int i = 0; i < 100; i++) {
        client_sockets[i] = 0;
    }
    client_sockets[0]=STDIN_FILENO;
    client_sockets[1]=listen_socket;

    fd_set read_fds;
    fd_set backup_fd_set = read_fds;

    char* buff = calloc(1025, sizeof(char));

    while(1){

        FD_ZERO(&read_fds);
         for (int i = 0; i < 100; i++) {
            if (client_sockets[i] > 0) {
                FD_SET(client_sockets[i], &read_fds);
            }
        }
        int i = select(listen_socket+1, &read_fds, NULL, NULL, NULL);

        //if standard in, use fgets
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            fgets(buff, BUFFER_SIZE, stdin);
            buff[strlen(buff)-1]=0;
            printf("Recieved from terminal: '%s'\n",buff);
        }

        // if socket
        if (FD_ISSET(listen_socket, &read_fds)) {
            //accept the connection
            int client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
            printf("Connected, waiting for data.\n");

            if (read(client_socket, buff, BUFFER_SIZE) == 0) {
                // Client disconnected
                printf("Client disconnected, socket fd is %d\n", client_socket);
                close(client_socket);
                client_sockets[i] = 0;
            }

            //trim the string
            buff[strlen(buff)-1]=0; //clear newline
            if(buff[strlen(buff)-1]==13){
                //clear windows line ending
                buff[strlen(buff)-1]=0;
            }

            printf("\nRecieved from client '%s'\n", buff);
            if(client_socket<0) printf("client negative");

            // redirect stdout to client_socket
            int fd1 = open("foo.txt", O_WRONLY);
            int cpy = dup(STDOUT_FILENO);
            if(cpy<0) printf("cpy negative");
            // dup2(fd1, STDOUT_FILENO);
            
            if (server_terminal(buff, client_socket) < 0) error();

            // restore stdout
            // dup2(cpy, STDOUT_FILENO);

            close(client_socket);
        }
    }

    free(buff);
    free(hints);
    freeaddrinfo(results);
    return 0;
}