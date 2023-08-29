#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

int main() {
    int server_socket;
    struct sockaddr_in server_address;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }


    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    
    if (listen(server_socket, 5) == -1) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening...\n");

    int client_socket;
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
    if (client_socket == -1) {
        perror("Acceptance failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected\n");

    int number;
    recv(client_socket, &number, sizeof(number), 0);

    if (number > 100) {
        printf("%d is an arbitrary number.\n", number);
    } else {
        printf("%d is not an arbitrary number.\n", number);
    }


    return 0;
}
