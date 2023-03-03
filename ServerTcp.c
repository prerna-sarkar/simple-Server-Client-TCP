// socket()-> bind()-> listen()-> accept()-> send()
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
    char server_message[256] = "You have reached the server";

    // Create Server Socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM,0); 
    
    // Specify Server Address
    struct sockaddr_in server_addr; //store address of server in Internet connections
    server_addr.sin_family = AF_INET; // address family
    server_addr.sin_port = htons(9002); // host byte order to network byte order (port below 1024 reserved)
    server_addr.sin_addr.s_addr = INADDR_ANY; // internet address in network byte order

    // Bind the socket to an IP and port 
    bind(server_socket, (struct sockaddr*) &server_addr,sizeof(server_addr));
    
    /*
    LISTEN
    makes it a passive socket
    i.e. not connected but awaiting connection which will spawn an active socket
    backlog (5 here) is the max length to which queue of pending connections may grow
    */
    listen(server_socket, 5); 
    
    //ACCEPT
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // SEND the message to client_socket
    send(client_socket, server_message, sizeof(server_message), 0);

    // CLOSE socket
    close(server_socket);

    return 0;

}