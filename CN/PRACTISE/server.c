#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int s_fd,c-fd;
    struct sockaddr_in s_addr,c_addr;
    int addrlen = sizeof(c_addr);

    if ((s_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = INADDR_ANY;
    s_addr.sin_port = htons(8080);

    if ((bind(s_fd, (struct sockaddr *)&s_addr, sizeof(s_addr))) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if ((listen(s_fd, 3)) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", 8080);

    if ((c_fd = accept(s_fd, (struct sockaddr *)&c_addr, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    int num1;
    revc(c_fd, &num1, sizeof(int), 0);
    printf("Received number from client: %d\n", num1);

    
    return 0;
}
