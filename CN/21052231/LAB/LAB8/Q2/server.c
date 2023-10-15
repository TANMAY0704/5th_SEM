#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024
#define MAX_CLIENTS 2

int client_sockets[MAX_CLIENTS];
pthread_t threads[MAX_CLIENTS];

typedef struct {
    int index;
} ThreadArgs;

void *client_handler(void *arg) {
    ThreadArgs *threadArgs = (ThreadArgs *)arg;
    int client_index = threadArgs->index;
    int receiver = (client_index + 1) % MAX_CLIENTS;

    char buffer[MAX_BUFFER_SIZE];

    while (1) {
        int valread = read(client_sockets[client_index], buffer, MAX_BUFFER_SIZE);
        if (valread == 0) {
            printf("Client %d disconnected.\n", client_index + 1);
            close(client_sockets[client_index]);
            pthread_exit(NULL);
        }

        printf("Client %d: %s", client_index + 1, buffer);

        // Relay the message to the other client
        send(client_sockets[receiver], buffer, strlen(buffer), 0);
    }

    return NULL;
}

int main() {
    int server_fd;
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
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    int client_count = 0;

    while (client_count < MAX_CLIENTS) {
        if ((client_sockets[client_count] = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        printf("Client %d connected.\n", client_count + 1);

        // Create a thread to handle this client
        ThreadArgs *threadArgs = (ThreadArgs *)malloc(sizeof(ThreadArgs));
        threadArgs->index = client_count;

        if (pthread_create(&threads[client_count], NULL, client_handler, (void *)threadArgs) != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }

        client_count++;
    }

    // Wait for all threads to finish
    for (int i = 0; i < MAX_CLIENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
