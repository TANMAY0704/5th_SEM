#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 12345
#define CLIENT_PORT 54321
#define SERVER_IP "0.0.0.0"

int main() {
    // Create a server socket 
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Server socket creation failed");
        return EXIT_FAILURE;
    }
    //this is working for some reason idek what i have done in this code soemone save me from this 

    
    // Create a client socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Client socket creation failed");
        close(server_socket);
        return EXIT_FAILURE;
    }
    
    // Bind server socket
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Server socket binding failed");
        close(server_socket);
        close(client_socket);
        return EXIT_FAILURE;
    }
    
    // Bind client socket
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(CLIENT_PORT);
    client_addr.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(client_socket, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
        perror("Client socket binding failed");
        close(server_socket);
        close(client_socket);
        return EXIT_FAILURE;
    }
    
    printf("Sockets created and bound successfully.\n");
    
    // Clean up and close sockets
    close(server_socket);
    close(client_socket);
    
    return EXIT_SUCCESS;
}