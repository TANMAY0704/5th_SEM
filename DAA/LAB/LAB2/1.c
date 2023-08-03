#include <stdio.h>
#include <stdlib.h>
int binary(int n)
{

    if (n == 0)
    {
        return 0;
    }
    else
    {
        return (n % 2 + 10 * binary(n / 2));
    }
}
void decimalToBinary(int n, FILE *inFile, FILE *outFile)
{
    if (n == 0)
    {
        return;
    }

    int decimalNum;
    fscanf(inFile, "%d", &decimalNum);

    fprintf(outFile, "%d : %d\n", decimalNum, binary(decimalNum));

    decimalToBinary(n - 1, inFile, outFile);
}

int main(int argc, char *argv[])
{

    int n = atoi(argv[1]);
    FILE *inFile = fopen(argv[2], "r");
    FILE *outFile = fopen(argv[3], "w");

    if (inFile == NULL || outFile == NULL)
    {
        printf("Error opening files.\n");
        return 1;
    }

    decimalToBinary(n, inFile, outFile);

    printf("Decimals converted !!\n", n);

    rewind(outFile);
    char line[100];
    while (fgets(line, sizeof(line), outFile) != NULL)
    {
        printf("%s", line);
    }

    fclose(inFile);
    fclose(outFile);

    return 0;
}
