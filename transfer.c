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

// returns number of bytes sent. -1 if error
int transfer(char* filename, int to_other) {
    // open file
    FILE *file = fopen(filename, "r");
    char *buffer = malloc(BUFFER_SIZE);
    // for each chunk of 1024 bytes
    while (read(file, buffer, BUFFER_SIZE) != NULL) {
        // send each chunk to other side
        send(to_other, buffer, BUFFER_SIZE, 0);
        // wait for other side to send ok
        // repeat until file is transferred
    }
}

int recieve() {
    // recieve file from other side
    // write file to the file system
    // send ok to server
    // repeat until file is transferred
}