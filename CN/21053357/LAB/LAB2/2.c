#include <stdio.h>

int main() {
    unsigned int num;
    printf("Enter a number: ");
    scanf("%u", &num);

    unsigned char byte1, byte2, byte3, byte4;

    byte1 = num & 0xFF; 
    byte2 = (num >> 8) & 0xFF; 
    byte3 = (num >> 16) & 0xFF; 
    byte4 = (num >> 24) & 0xFF; 

    printf("Byte 1: %02X\n", byte1);
    printf("Byte 2: %02X\n", byte2);
    printf("Byte 3: %02X\n", byte3);
    printf("Byte 4: %02X\n", byte4);

    return 0;
}
