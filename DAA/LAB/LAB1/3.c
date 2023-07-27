#include <stdio.h>
#include <stdlib.h>

void readFromFile(char filename[], int arr[], int n)
{
    FILE *myFile;
    myFile = fopen(filename, "r");

    if (myFile == NULL)
    {
        printf("Error Reading File\n");
        exit(0);
    }

    for (int i = 0; i < n; i++)
    {
        fscanf(myFile, "%d,", &arr[i]);
    }

    fclose(myFile);
}

int countDuplicates(int arr[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                count++;
                break;
            }
        }
    }
    return count;
}

int findMostRepeatingElement(int arr[], int n)
{
    int max = 0;
    int maxElement = 0;
    for (int i = 0; i < n; i++)
    {
        int count = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                count++;
            }
        }
        if (count > max)
        {
            max = count;
            maxElement = arr[i];
        }
    }
    return maxElement;
}

int main()
{
    int n;
    printf("Number of elements to read: ");
    scanf("%d", &n);
    int arr[n];

    readFromFile("num.txt", arr, n);

    printf("Data read from the file: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int numDuplicates = countDuplicates(arr, n);
    printf("Number of duplicates: %d\n", numDuplicates);

    int mostRepeatingElement = findMostRepeatingElement(arr, n);
    printf("The most repeating element: %d\n", mostRepeatingElement);

    return 0;
}
