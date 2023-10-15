#include <stdio.h>
#include <stdlib.h>
void binary(int n)
{
    
    int binary[32];
    int i = 0;
    while (n > 0)
    {
        binary[i] = n % 2;
        n = n / 2;
        i++;
    }
    
    for (int j = i - 1; j >= 0; j--)
        printf("%d", binary[j]);
    printf("\nMSB : %d\n", binary[i-1]);
    printf("LSB : %d\n", binary[0]);


}
int main(int argc, char *argv[]) {
    

    unsigned int num = atoi(argv[1]);
    binary(num);

    return 0;
}
