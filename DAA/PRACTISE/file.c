#include <stdio.h>
#include <stdlib.h>

void writeToFile(const char filename[])
{
    FILE *myFile;
    myFile = fopen(filename, "w");

    if (myFile == NULL)
    {
        printf("Error opening the file. Please check the file path.\n");
        exit(1);
    }

    int n;
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid input. Please enter a positive integer.\n");
        fclose(myFile);
        exit(1);
    }

    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Invalid input. Please enter a valid integer.\n");
            fclose(myFile);
            exit(1);
        }
        fprintf(myFile, "%d ", arr[i]);
    }

    fclose(myFile);
    printf("Data has been written to the file successfully.\n");
}

void readFileToArray(const char filename[],int n)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening the file. Please check the file path.\n");
        exit(1);
    }



    int arr[n];
    printf("Contents of the file:\n");
    for (int i = 0; i < n; i++)
    {
        fscanf(file, "%d", &arr[i]);
        printf("%d ", arr[i]);
    }

    fclose(file);
    printf("\n");
}

int main()
{
    const char *filename = "file.txt";
    writeToFile(filename);
    readFileToArray(filename,5);

    return 0;
}