#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
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


    char name[100];
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';  

    // Send data to the server using UDP
    ssize_t bytes_sent = sendto(client_socket, name, strlen(name), 0, (struct sockaddr *)&server_address, sizeof(server_address));
    if (bytes_sent == -1) {
        perror("Sendto failed");
        exit(EXIT_FAILURE);
    }

    // Close the client socket
    close(client_socket);

    return 0;
}
