#include "network.h"
#include "fileman.h"
#include "terminal.h"

int main() {
    struct addrinfo * hints, * results;
    hints = calloc(1,sizeof(struct addrinfo));

    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM; //TCP socket
    hints->ai_flags = AI_PASSIVE; //only needed on server
    getaddrinfo(NULL, PORT, hints, &results);  //NULL is localhost or 127.0.0.1

    //create socket
    int listen_socket = socket(results->ai_family, results->ai_socktype, results->ai_protocol);\

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

    fd_set read_fds;
    fd_set backup_fd_set = read_fds;

    char* buff=calloc(1025, sizeof(char));

    while(1){

        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(listen_socket,&read_fds);
        int i = select(listen_socket+1, &read_fds, NULL, NULL, NULL);

        //if standard in, use fgets
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            fgets(buff, sizeof(buff), stdin);
            buff[strlen(buff)-1]=0;
            printf("Recieved from terminal: '%s'\n",buff);
        }

        // if socket
        if (FD_ISSET(listen_socket, &read_fds)) {
            //accept the connection
            int client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
            printf("Connected, waiting for data.\n");

            //read the whole buff
            read(client_socket,buff, sizeof(buff));
            //trim the string
            buff[strlen(buff)-1]=0; //clear newline
            if(buff[strlen(buff)-1]==13){
                //clear windows line ending
                buff[strlen(buff)-1]=0;
            }

            printf("\nRecieved from client [%d] '%s'\n", client_socket, buff);

            if(server_terminal(buff)<0) err;

            // // TODO: move to terminal.c
            // // process the command
            // if (strcmp(buff, "ls") == 0) {
            //     ls(".");
            // }
            // else if (strcmp(buff, "cd") == 0) {
            //     cd("..");
            // }
            // else if (strcmp(buff, "pwd") == 0) {
            //     pwd();
            // }
            // else if (strcmp(buff, "rm") == 0) {
            //     rm("test.txt", 0);
            // }
            // // else if (strcmp(buff, "mkdir" == 0)) {
            // //     mkdir("test", 0777);
            // // }
            // else if (strcmp(buff, "touch") == 0) {
            //     touch("test.txt");
            // }
            // else printf("%s not found\n", buff);

            // close(client_socket);
        }
    }

    free(buff);
    free(hints);
    freeaddrinfo(results);
    return 0;
}