#include "network.h"

int size(char* name, char recursive) {
    struct stat stats;
    if (recursive) {
        int sum;
        struct dirent *entry;
        DIR *dir = opendir(name);
        while (entry = readdir(dir)) {
            if (entry->d_type == DT_DIR)
                size(entry->d_name, 1);
            else
                size(entry->d_name, 0);
        }
    }

    stat(name, &stats);
    return stats.st_size;
}

int ls() {
    struct dirent * entry;
    DIR *dir = opendir(".");
    while (entry = readdir(dir)) {
        printf("%s %7d %12s\n",
               entry->d_type == DT_DIR ? "d" : "f",
               size(entry->d_name, 0),
               entry->d_name);
    }
}

int cd() {
    
}

int pwd() {
    char cwd[BUFFER_SIZE];
    if (getcwd(cwd, sizeof(cwd))) printf("%s\n", cwd);
    else {
        perror("getcwd error");
        return -1;
    }
    return 0;
}

int rm() {

}

int main(int argc, char *argv[]) {
    ls();
    pwd();
}