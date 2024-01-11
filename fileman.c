#include "network.h"
#include "fileman.h"
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <stdio.h>

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

int ls(char * name) {
    struct dirent * entry;
    DIR *dir = opendir(name);
    while (entry = readdir(dir)) {
        printf("%s %7d %12s\n",
               entry->d_type == DT_DIR ? "d" : "f",
               size(entry->d_name, 0),
               entry->d_name);
    }
}

int cd(char * name) {
    if (chdir(name) != 0) perror("chdir failed");
    return 0;
}

int pwd() {
    char cwd[BUFFER_SIZE];
    if (getcwd(cwd, sizeof(cwd))) printf("%s\n", cwd);
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