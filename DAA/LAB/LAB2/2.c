#include <stdio.h>
#include <stdlib.h>

int GCD(int a, int b)
{
    if (b != 0)
        return GCD(b, a % b);
    else
        return a;
}

int main(int argc, char *argv[])
{
    int num1, num2;

    FILE *inFile = fopen(argv[1], "r");
    FILE *outFile = fopen(argv[2], "w");

    if (inFile == NULL)
    {
        printf("Error opening the file %s.\n", inFile);
        return 1;
    }


    
    if (outFile == NULL)
    {
        printf("Error creating/writing to the file %s.\n", outFile);
        fclose(inFile);
        return 1;
    }

    while (fscanf(inFile, "%d %d", &num1, &num2) == 2)
    {
        int gcd = GCD(num1, num2);
        fprintf(outFile, "GCD of %d and %d : %d\n",num1,num2, gcd);
    }


    printf("GCD printed to file");
    fclose(inFile);
    fclose(outFile);
    return 0;
}