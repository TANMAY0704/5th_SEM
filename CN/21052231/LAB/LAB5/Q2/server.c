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

    int num1, num2;
    socklen_t client_address_len = sizeof(client_address);

    ssize_t bytes_received = recvfrom(server_socket, &num1, sizeof(num1), 0, (struct sockaddr *)&client_address, &client_address_len);
    if (bytes_received == -1) {
        perror("Receiving num1 failed");
        exit(EXIT_FAILURE);
    }

    bytes_received = recvfrom(server_socket, &num2, sizeof(num2), 0, (struct sockaddr *)&client_address, &client_address_len);
    if (bytes_received == -1) {
        perror("Receiving num2 failed");
        exit(EXIT_FAILURE);
    }

    int sum = num1 + num2;
    int difference = num1 - num2;
    int product = num1 * num2;
    float quotient = (float)num1 / num2;

    printf("Received numbers: %d and %d\n", num1, num2);
    printf("Sum: %d\n", sum);
    printf("Difference: %d\n", difference);
    printf("Product: %d\n", product);
    printf("Quotient: %.2f\n", quotient);

    close(server_socket);

    return 0;
}
