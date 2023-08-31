#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <ctype.h>

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
    struct sockaddr_in server_address;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
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

    // Listen for connections
    if (listen(server_socket, 5) == -1) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }


    // Accept connection
    int client_socket;
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
    if (client_socket == -1) {
        perror("Acceptance failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected\n");

    
    char name[100];
    recv(client_socket, name, sizeof(name), 0);


    int num_vowels = count_vowels(name);

    printf("Received name: %s\n", name);
    printf("Number of vowels: %d\n", num_vowels);


    return 0;
}
