#include "network.h"
#include "fileman.h"
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
#include <sys/types.h>
#include <unistd.h>

char * rpath(char * name, struct dirent * entry) {
    char rpath[BUFFER_SIZE];
    strcat(rpath, name);
    strcat(rpath, "/");
    strcat(rpath, entry->d_name);
    return rpath;
}

// TODO: fix recursive size
int size(char* name, char is_dir) {
    struct stat stats;
    if (is_dir) {
        int sum = 0;
        struct dirent *entry;
        DIR *dir = opendir(name);
        while (entry = readdir(dir)) {
            char rpath[BUFFER_SIZE];
            strcat(rpath, name);
            strcat(rpath, "/");
            strcat(rpath, entry->d_name);
            if (entry->d_type == DT_DIR) sum += size(entry->d_name, 1);
            else sum += size(entry->d_name, 0);
        }
        return sum;
    }

    stat(name, &stats);
    return stats.st_size;
}

int ls(char * name, int client_socket, char* buffer) {
    struct dirent * entry;
    DIR *dir = opendir(name);
    int i=0;
    while (entry = readdir(dir)) {
        char* this_line[256];
        // printf("%s %7d %12s\n",
        //        entry->d_type == DT_DIR ? "d" : "f",
        //        size(entry->d_name, 0),
        //        entry->d_name);
        sprintf(this_line, "%s %7d %12s\n", entry->d_type == DT_DIR ? "d" : "f", size(entry->d_name, 0), entry->d_name);
        strcat(buffer, this_line);
        i++;
    }
    write(client_socket, buffer, BUFFER_SIZE*i); 
}

int cd(char * name) {
    if (chdir(name) != 0) perror("chdir failed");
    return 0;
}

int pwd(int client_socket, char* cwd) {
    char* buff[1025];
    if (getcwd(buff, 1024)){
        strcat(cwd, buff);
        // printf("cwd: %s %d\n", cwd, strlen(cwd));
        write(client_socket, cwd, BUFFER_SIZE); 
    }
    else perror("getcwd failed");
    return 0;
}

int rm(char * name, char is_dir) {
    if (is_dir) {
        struct dirent *entry;
        DIR *dir = opendir(name);
        while (entry = readdir(dir)) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
            char rpath[BUFFER_SIZE];
            strcat(rpath, name);
            strcat(rpath, "/");
            strcat(rpath, entry->d_name);
            if (entry->d_type == DT_DIR) {
                int x = rm(rpath, 1);
                printf("%d\n", x);
            } else {
                int x = rm(rpath, 0);
                printf("%d\n", x);
            }
            rmdir(name);
        }
    }
    return remove(name);
}

int touch(char * name) {
    if (open(name, O_RDWR | O_CREAT, 0644) < 0) perror("touch failed");
    return 0;
}