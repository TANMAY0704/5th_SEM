#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int server_port = atoi(argv[1]);

    // Create socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Bind to the specified port
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Bind failed");
        close(server_socket);
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Listen failed");
        close(server_socket);
        exit(1);
    }

    printf("Server listening on port %d...\n", server_port);

    // Accept incoming connection
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);
    int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
    if (client_socket == -1) {
        perror("Accept failed");
        close(server_socket);
        exit(1);
    }

    printf("Connection established with client %s:%d\n",
           inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

    // Exchange messages
    char buffer[256];
    int bytes_received;

    do {
        bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received == -1) {
            perror("Receive error");
            break;
        }

        if (bytes_received == 0) {
            printf("Client disconnected.\n");
            break;
        }

        buffer[bytes_received] = '\0';
        printf("Received message from client: %s\n", buffer);

        // Respond to the client
        const char *response = "Received your message";
        send(client_socket, response, strlen(response), 0);

    } while (strcmp(buffer, "close") != 0);

    // Close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
