#include <stdio.h>
struct pkt 
{
    char ch1;
    char ch2[2];
    char ch3;
};

int main() 
{
    struct pkt packet;
    int num;

    printf("Enter an integer: ");
    scanf("%d", &num);

    packet.ch1 = num & 0xFF;
    packet.ch2[0] = (num >> 8) & 0xFF;
    packet.ch2[1] = (num >> 16) & 0xFF;
    packet.ch3 = (num >> 24) & 0xFF;


    printf("Content of structure:\n");
    printf("ch1: %d\n", packet.ch1);
    printf("ch2[0]: %d\n", packet.ch2[0]);
    printf("ch2[1]: %d\n", packet.ch2[1]);
    printf("ch3: %d\n", packet.ch3);

    int originalNumber = 0;
    originalNumber |= (packet.ch3 << 24);
    originalNumber |= (packet.ch2[0] << 8);  
    originalNumber |= (packet.ch2[1] << 16);
    originalNumber |= packet.ch1; 

    printf("Aggregated original number: %d\n", originalNumber);

    return 0;
}
