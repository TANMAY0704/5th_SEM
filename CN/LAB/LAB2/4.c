#include <stdio.h>
#include <stdlib.h> // for atoi

struct packet {
    char a1;
    char a2[2];
    char a3;
};

int combineBytes(struct packet* pkt) {
    int data = 0;
    data |= pkt->a1;
    data |= (pkt->a2[0] << 8);
    data |= (pkt->a2[1] << 16);
    data |= (pkt->a3 << 24);
    return data;
}

void extractBytes(int data, struct packet* pkt) {
    pkt->a1 = (data);
    pkt->a2[0] = ((data >> 8));
    pkt->a2[1] = ((data >> 16));
    pkt->a3 = ((data >> 24));
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: %s <a1> <a2[0]> <a2[1]> <a3>\n", argv[0]);
        return 1;
    }

    struct packet pkt;
    pkt.a1 = argv[1][0];
    pkt.a2[0] = argv[2][0];
    pkt.a2[1] = argv[3][0];
    pkt.a3 = argv[4][0];

    int integer_data = combineBytes(&pkt);

    printf("Integer data: %d\n", integer_data);

    return 0;
}
