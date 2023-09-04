#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <ctype.h>
#include <unistd.h>

int count_vowels(const char *name) {
    int vowels = 0;
    for (int i = 0; name[i] != '\0'; ++i) {
        char c = tolower(name[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            vowels++;
        }
    }
    return vowels;
}

int main() {
    int server_socket;
    struct sockaddr_in server_address, client_address;

    // Create socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind to address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening...\n");

    char name[100];
    socklen_t client_address_len = sizeof(client_address);

    ssize_t bytes_received = recvfrom(server_socket, name, sizeof(name), 0, (struct sockaddr *)&client_address, &client_address_len);
    if (bytes_received == -1) {
        perror("Receiving name failed");
        exit(EXIT_FAILURE);
    }

    int num_vowels = count_vowels(name);

    printf("Received name: %s\n", name);
    printf("Number of vowels: %d\n", num_vowels);

    // Close the server socket
    close(server_socket);

    return 0;
}
