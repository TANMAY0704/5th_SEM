#include <stdio.h>

struct packet {
    char a1;
    char a2[2];
    char a3;
};

void extractBytes(int data, struct packet* pkt) {
    pkt->a1 = (data);
    pkt->a2[0] = ((data >> 8));
    pkt->a2[1] = ((data >> 16));
    pkt->a3 = ((data >> 24));
}

int main() {
    int integer_data = 1234;

    struct packet pkt;

    printf("Extracting bytes from integer data...\n");
    extractBytes(integer_data, &pkt);

    printf("a1: %c\n", pkt.a1);
    printf("a2[0]: %c\n", pkt.a2[0]);
    printf("a2[1]: %c\n", pkt.a2[1]);
    printf("a3: %c\n", pkt.a3);

    return 0;
}
