[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# !Better FTP

### The !Better FTP Incorporated

Team Lychee

1. Tracey Lin
2. Ivan Chen
       
### Project Description:

This is an FTP-like program which consists of a server client connection to allow access to remote files. The client will interact with the server through a terminal using custom commands, to browse the file system, add or delete files, and also transfer files between the server and client. 

### Instructions:

How does the user install/compile/run the program.

The user will type "make compile" to make sure everything is up to date then type "make client" plus use ARGS= to connect with their desires machine and interact with this program through a terminal with the commands defined in the table below. 

|command|usage|function|
|-------|-----|--------|
|cd     |`cd <dir>`|changes the current working directory to the `<dir>` directory. default is `.`|
|ls     |`ls <dir>`|lists the files in the `<dir>` directory. default is `.`|
|up     |`up <filename>`|uploads file from client to server|
|down   |`down <filename>`|downloads file from server to client|
|pwd    |`pwd`|prints working directory|
|touch  |`touch <filename>`|creates new file|
|rm     |`rm <filename>`|removes a file. use `-r` flag to remove recursively|
|mkdir  |`mkdir <dirname>`|creates a directory|
|size   |`size <filename>`|print out the size of a directory. use `-r` flag to get size recursively|
|end    |`end`|ends client session with server|

### Project Structure

|file      |description|
|----------|-----------|
|client.c  |handles client connection and communication with server + manages interface|
|fileman.c |contains functions to manage the server interaction with files|
|network.c |handles communication between server and client|
|server.c  |handles server actions like file management, file transfer, and responding to client commands|
|terminal.c|contains functions to manage the client terminal|
|transfer.c|contains functions to manage the transfer of files|
