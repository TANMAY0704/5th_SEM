

#include<stdio.h>
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
}
void hexadecimal(int n)
{
    int hexadecimal[32];
    int i = 0;
    while (n != 0)
    {
        int temp = 0;
        temp = n % 16;
        if (temp < 10)
        {
            hexadecimal[i] = temp + 48;
            i++;
        }
        else
        {
            hexadecimal[i] = temp + 55;
            i++;
        }
        n = n / 16;
    }
    for (int j = i - 1; j >= 0; j--)
        printf("%c", hexadecimal[j]);
}
int main()
{
    
    binary(140);
    printf("\n");
    hexadecimal(140);
    return 0;
}   