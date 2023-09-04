#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int client_socket;
    struct sockaddr_in server_address;

    // Create socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    int num1, num2;
    printf("Enter the first number: ");
    scanf("%d", &num1);
    printf("Enter the second number: ");
    scanf("%d", &num2);


    ssize_t bytes_sent = sendto(client_socket, &num1, sizeof(num1), 0, (struct sockaddr *)&server_address, sizeof(server_address));
    if (bytes_sent == -1) {
        perror("Sendto failed");
        exit(EXIT_FAILURE);
    }

    bytes_sent = sendto(client_socket, &num2, sizeof(num2), 0, (struct sockaddr *)&server_address, sizeof(server_address));
    if (bytes_sent == -1) {
        perror("Sendto failed");
        exit(EXIT_FAILURE);
    }


    close(client_socket);

    return 0;
}
