#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_address;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);  // Port number
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP Address of the server

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed");
        exit(1);
    }

    // Send your name to the server
    char name[100] = "RAJBIR";
    send(client_socket, name, sizeof(name), 0);

    // Receive the prompt for two numbers
    char prompt[100];
    recv(client_socket, prompt, sizeof(prompt), 0);
    printf("%s", prompt);

    // Input two numbers
    int num1, num2;
    scanf("%d %d", &num1, &num2);

    // Send the numbers to the server
    char numbers[100];
    snprintf(numbers, sizeof(numbers), "%d %d", num1, num2);
    send(client_socket, numbers, sizeof(numbers), 0);

    // Receive and display the sum from the server
    char result[100];
    recv(client_socket, result, sizeof(result), 0);
    printf("Server: %s", result);

    // Close the socket
    close(client_socket);

    return 0;
}
