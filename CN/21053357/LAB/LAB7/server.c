/*WAP using TCP where the client will send your name to server and
server will display.
then enter two numbers in client and the server will show their sum*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length = sizeof(client_address);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);  // Port number
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified address
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Binding failed");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Listening failed");
        exit(1);
    }

    printf("Server is listening...\n");

    // Accept a client connection
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_length);
    if (client_socket == -1) {
        perror("Accepting failed");
        exit(1);
    }

    // Receive and display client's name
    char name[100];
    recv(client_socket, name, sizeof(name), 0);
    printf("Received name from client: %s\n", name);

    // Prompt the client for two numbers
    send(client_socket, "Enter two numbers separated by space: ", sizeof("Enter two numbers separated by space: "), 0);

    // Receive and calculate the sum of two numbers
    char numbers[100];
    recv(client_socket, numbers, sizeof(numbers), 0);

    int num1, num2, sum;
    sscanf(numbers, "%d %d", &num1, &num2);
    sum = num1 + num2;

    // Send the sum back to the client
    char result[100];
    snprintf(result, sizeof(result), "Sum: %d\n", sum);
    send(client_socket, result, sizeof(result), 0);

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}



