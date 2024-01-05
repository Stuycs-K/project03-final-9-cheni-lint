[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# !Better FTP

### The !Better FTP Incorporated

1. Tracey Lin
2. Ivan Chen
       
### Project Description:

This is an FTP-like program which consists of a server client connection to allow access to remote files. The client will interact with the server through a terminal using custom commands, to browse the file system, add or delete files, and also transfer files between the server and client. 

### Instructions:

How does the user install/compile/run the program.

The user will interact with this program through a terminal with the commands defined in the table below. 

|command|usage|function|
|-------|-----|--------|
|cd|`cd <dir>`|changes the current working directory to the `<dir>` directory. default is the current directory (`.`)|
|ls|`ls <dir>`|lists the files in the `<dir>` directory. default is the current directory (`.`)|

### Project Structure

|file      |description|
|----------|-----------|
|client.c  |handles client connection and communication with server + manages interface|
|fileman.c |contains functions to manage the server interaction with files|
|network.c |handles communication between server and client|
|server.c  |handles server actions like file management, file transfer, and responding to client commands|
|terminal.c|contains functions to manage the client terminal|
|transfer.c|contains functions to manage the transfer of files|
