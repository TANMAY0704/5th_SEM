#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

void calculateProduct(int num1, int num2) {
    int product = num1 * num2;
    printf("Product of %d and %d is: %d\n", num1, num2, product);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // Client
    int num1;
    if (read(new_socket, &num1, sizeof(int)) < 0) {
        perror("Read failed");
        close(new_socket);
        exit(EXIT_FAILURE);
    }
    printf("Received number from client: %d\n", num1);

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // Client 2
    int num2;
    if (read(new_socket, &num2, sizeof(int)) < 0) {
        perror("Read failed");
        close(new_socket);
        exit(EXIT_FAILURE);
    }
    printf("Received number from client: %d\n", num2);

    calculateProduct(num1, num2);

    close(new_socket);

    return 0;
}
