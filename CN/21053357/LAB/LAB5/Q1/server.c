#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_socket;
    struct sockaddr_in server_address, client_address;

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
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

    printf("Server listening...\n");

    int number;
    socklen_t client_address_len = sizeof(client_address);

    ssize_t bytes_received = recvfrom(server_socket, &number, sizeof(number), 0, (struct sockaddr *)&client_address, &client_address_len);

    if (bytes_received == -1) {
        perror("Receiving data failed");
        exit(EXIT_FAILURE);
    }

    printf("Received a number: %d\n", number);

    if (number > 100) {
        printf("%d is an arbitrary number.\n", number);
    } else {
        printf("%d is not an arbitrary number.\n", number);
    }

    close(server_socket);

    return 0;
}
