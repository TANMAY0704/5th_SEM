#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

int main() {
    int client_socket;
    struct sockaddr_in server_address;


    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }


    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }


    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    // Send data
    send(client_socket, &number, sizeof(number), 0);




    return 0;
}
