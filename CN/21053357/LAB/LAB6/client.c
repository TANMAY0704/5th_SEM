#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char number_str[1024];
    double number; // The number for which we want to calculate the square root
    printf("Enter number : ");
    scanf("%lf", &number);
    snprintf(number_str, sizeof(number_str), "%lf", number);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    send(sock, number_str, strlen(number_str), 0);


    double square_root;
    read(sock, &square_root, sizeof(square_root));
    printf("Square root received from server: %lf\n", square_root);

    return 0;
}
