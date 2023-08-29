#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main() {
    int client_socket;
    struct sockaddr_in server_address;


    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }


    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Take user input for the name
    char name[100];
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';  // Remove the newline character

    // Send data
    send(client_socket, name, sizeof(name), 0);
    //close server
    
    return 0;
}
