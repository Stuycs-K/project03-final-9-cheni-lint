# Dev Log:

## Tracey

### 2024-01-02 - pair up with partner
i asked ivan, he said yes, took about 5 seconds

### 2024-01-03 - discuss what project we want to make and make proposal
heavily debated what we want to do and after multiple tries we settled with client server network that uses
a terminal to communicate and allows for the access and transfer of data, took about 2 hours

### 2024-01-04 - start working on server client network
i started doing the client server, basically just copy and pasting lab16 and k code

### 2024-01-05 - research how to connect with multiple client using select
figure out that you need multiple thread, fork, or select in order to do multiple client connection and just reading
up on code to understand select more

### 2024-01-06 - did testing
try to see why it wouldn't connect to client on the school laptop and turns out I forgot to do args and that wasted
a stupid amount of time (1.5 hrs)

### 2024-01-07 - did testing + research how to use select to decide which client to listen to
look at codes online and read documentations on it (.5 hrs)

### 2024-01-08 - more testing
in class: figure out why it connects back and forth (1hr)
outisde of class: figure out how to do multiple concurrent client, started on the skeleton of terminal making (1 hr)

### 2024-01-09 - work on terminal.c
in class/at home: worked on a skeleton of terminal.c, not very sure if this is how it works or if where to read from so I
defaulted to stdin for now (1.5hr)

### 2024-01-10 - made terminal and server more compatible
in class: moved terminal logic into the server main() and started testing (1 hr)
at home: debugging (.5 hr)

### 2024-01-11 - debugging
in class: fixed makefile linking, check the errors and added all the import back (1hr)
at home: strsep is giving me a segfault and I cant figure out why (3hr)

### 2024-01-12 - terminal
in class: fix all the import stuffs now its not throwing me a thousand errors anymore (1hr)
at home: made terminal look better and fix the comunication sen message logic (3hr)

### 2024-01-13 - laptop broke

### 2024-01-14 - laptop broke

### 2024-01-15 - touch up
add signals and check up with ivan on progress and tested mkdir and other commands and tested that it can connect across different machines (.5 hrs)

## Ivan

### 2024-01-02 - Brief description
partner matching with tracey

### 2024-01-03 - discuss what project we want to make and make proposal
discussed with tracey project ideas and wrote proposal

### 2024-01-04 - Brief description
fixed up the imports so that the client server connection works - ivan
resolve bug from redefining PORT constant - ivan

### 2024-01-05 - Worked on fileman funcs
i worked on the file management functions, starting with `ls()` and `size()`
i want the `size()` to work recursively also with directories and started, but didn't finish implementing that

### 2024-01-08 - Almost done with fileman funcs
i completed all of the fileman funcs other than recursive `size()`
started to think about server side of handling terminal input

### 2024-01-09 - Fileman + Server
added ability to test input from user (client) in server.c
waiting for terminal part to be complete so args are actually properly handled
started thinking about how to transfer the files between server and client

### 2024-01-10 - Fileman + Server
added redirect from server stdout to client socket
tried to debug error with this causing the server to hang after sending a particularly large message

### 2024-01-11 - Fileman + Server
resolved bugs with sending msgs from client (limited to 8 bytes since accidentally used sizeof(char *))
resolved import errors