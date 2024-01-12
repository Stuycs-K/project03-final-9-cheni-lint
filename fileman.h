#ifndef FILEMAN_H
#define FILEMAN_H

int size(char *name, char is_dir);
int ls(char *name, int client_socket, char* buffer);
int cd(char *name);
int pwd(int client_socket, char* buffer);
int rm(char *name, char is_dir);
int touch(char *name);

#endif