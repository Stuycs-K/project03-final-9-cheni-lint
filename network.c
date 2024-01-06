#include "network.h"

/*Connect to the server
 *return the to_server socket descriptor
 *blocks until connection is made.*/
int client_tcp_handshake(char * server_address) {

  //getaddrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  // getaddrinfo(NULL, “80”, hints, &results);  //Server sets node to NULL
  getaddrinfo(server_address, PORT, hints, &results);
  //marge is “149.89.150.100”

  printf("stuck 0\n");
  int serverd;
  //create the socket
  serverd = socket(results->ai_family, results->ai_socktype, 0);
  // printf("the ai protocol is [%d]\n", results->ai_protocol);

  printf("stuck 1\n");
  //connect to the server
  connect(serverd, results->ai_addr, results->ai_addrlen);

  printf("stuck 2\n");
  free(hints);
  freeaddrinfo(results);

  printf("stuck 3\n");
  return serverd;
}

/*Accept a connection from a client
 *return the to_client socket descriptor
 *blocks until connection is made.
 */
int server_tcp_handshake(int listen_socket){
    int client_socket;

    //accept the client connection
    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);
    client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
  
    return client_socket;
}

/*Create and bind a socket.
* Place the socket in a listening state.
*/
int server_setup() {
  //setup structs for getaddrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  results = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  hints->ai_flags = AI_PASSIVE; //only needed on server
  getaddrinfo(NULL, PORT, hints, &results);  //Server sets node to NULL
  //client: getaddrinfo(“149.89.150.100”, “9845”, hints, &results);
  
  //create the socket
  int sd = socket(results->ai_family, results->ai_socktype, 0);
  // printf("ai protocol: [%d]\n", results->ai_protocol);
  
  //this code should get around the address in use error
  //client d is client file descriptor and the return value of your socket command
  //client d should be whatever ur to client socket returns
  int yes = 1;
  int sockOpt =  setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  err(sockOpt,"sockopt  error");
  
  //bind the socket to address and port
  bind(sd, results->ai_addr, results->ai_addrlen);
  
  //set socket to listen state
  listen (sd, 10);
  
  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);
  
  return sd;
}

void err(int i, char*message){
  if(i < 0){
	  printf("Error: %s - %s\n",message, strerror(errno));
  	exit(1);
  }
}