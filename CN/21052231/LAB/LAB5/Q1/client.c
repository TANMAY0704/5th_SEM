#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int client_socket;
    struct sockaddr_in server_address;

    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    if (sendto(client_socket, &number, sizeof(number), 0, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Sendto failed");
        exit(EXIT_FAILURE);
    }

    close(client_socket);

    return 0;
}
