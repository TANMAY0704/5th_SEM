#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


int main()
{
    int s_fd,c_fd;
    struct sockaddr_in S_add,c_add;

    if(s_fd=socket(AF_INET,SOCK_STREAM,0)== -1)
    return 0;
}