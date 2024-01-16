# Final Project Proposal

## Group Members:

1. Tracey Lin
2. Ivan Chen
       
# Intentions:

We want to be able to access files on another machine. We do this by creating a client-server system such that the machine that stores the file always has an open server that can accept multiple concurrent clients. Once the client successfully connects to the server, it will gain access to a terminal which it uses to communicate with the subserver. There will be custom commands that allow the client to access the files it wants. All the changes between the client will be sync to prevent conflicts.
   
# Intended usage:

The client can connect to the server on any machine and it will open up a terminal. In the terminal there will be customized commands they can use to help them navigate and access the files they want. 
 
# Technical Details:

Technical Design
- Working with files (remote file system)
- Finding information about files (sync feature)
- Processes (use select to handle client interaction)
- Signals (tracking client sessions and handling interruptions when writing)
- Sockets (communication between servers and clients)


Work Distribution
Tracey: 
- Sockets to create a client-server communication pipeline
- Signals to handle interruptions during data transfers
- Custom terminal for client interface

Ivan: 
- Server file access
- Server file transfers (to/from)

Extra: 
- Data validation
- File synchronization
- Access control
    

Algorithms/Data Structures
- TCP-like handshake to establish client connection
   
# Intended pacing:

- (1/5) Sockets to create a client-server communication pipeline
- (1/9) Server file access
- (1/11) Server file transfers (to/from)
- (1/12) Custom terminal for client interface
- (1/13) Signals to handle interruptions during data transfers
