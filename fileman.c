#include "network.h"

int size(char* name, char is_dir) {
    struct stat stats;
    if (is_dir) {
        int sum;
        struct dirent *entry;
        DIR *dir = opendir(name);
        while (entry = readdir(dir)) {
            if (entry->d_type == DT_DIR) size(entry->d_name, 1);
            else size(entry->d_name, 0);
        }
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

int main(int argc, char *argv[]) {
    // rm("test", 1);
    pwd();
    cd("tessdst");
    pwd();
}