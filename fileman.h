#ifndef FILEMAN_H
#define FILEMAN_H

int size(char *name, char is_dir);
int ls(char *name);
int cd(char *name);
int pwd();
int rm(char *name, char is_dir);
int touch(char *name);

#endif