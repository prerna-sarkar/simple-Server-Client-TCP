// socket()-> connect() -> recv()
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
    // Create a Socket
    int client_socket; 
    client_socket = socket(AF_INET, SOCK_STREAM,0); //domain (Address family), type(SOCK_STREAM => sequenced bidirectional byte streams), protocol 0 => default

    // Specify an Address for the Socket
    struct sockaddr_in server_addr; //store address of server in Internet connections
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Connect
    int connection_status = connect(client_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)); // socket, to server_addr, server_addr length

    // check for error with connection
    if(connection_status == -1)
    {
        printf("There was an error making a connection to the remote socket\n");
    }

    // Receive data from the Server
    char server_response[256];
    recv(client_socket, &server_response, sizeof(server_response),0); //socket, buffer, length of buffer, flag

    // print out the server's response
    printf("The server sent the data:  %s\n", server_response);

    // Close the socket
    close(client_socket);

    return 0;
}

