#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

bool is_prime(int num) {
    if (num < 2)
        return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    int num;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error in socket creation");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error in socket binding");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 2) == -1) {
        perror("Error in listening");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080\n");

    socklen_t addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
    if (client_socket < 0) {
        perror("Error in accepting connection for client 1");
        exit(EXIT_FAILURE);
    }

    recv(client_socket, &num, sizeof(num), 0);
    printf("Received number from Client 1: %d\n", num);

    bool is_prime_number = is_prime(num);

    close(client_socket);

    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
    if (client_socket < 0) {
        perror("Error in accepting connection for client 2");
        exit(EXIT_FAILURE);
    }

    memset(buffer, 0, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "%d is %sprime.\n", num, is_prime_number ? "" : "not ");
    send(client_socket, buffer, strlen(buffer), 0);

    close(client_socket);
    close(server_socket);
    return 0;
}
