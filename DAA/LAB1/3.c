#include <stdio.h>
#include <stdlib.h>

int main()
{

    FILE *myFile;
    myFile = fopen("num.txt", "r");

    int i,n;
    printf("Number of elements to read : ");
    scanf("%d",&n);
    int a[n];

    if (myFile == NULL)
    {
        printf("Error Reading File\n");
        exit(0);
    }

    for (i = 0; i < n; i++)
    {
        fscanf(myFile, "%d,", &a[i]);
    }

    fclose(myFile);
    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    int  count = 0 ;
    for (i = 0; i < n; i++)
    {
        
        for (int j = i + 1; j < n; j++)
        {
            if (a[i] == a[j])
            {
                count++;
                break;
            }    
        }        
    }
    printf("Number of duplicate : %d", count);
    
    
    int max = 0;
    int maxElement = 0;
    for (i = 0; i < n; i++)
    {
        int count = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (a[i] == a[j])
            {
                count++;
            }    
        }
        if (count > max)
        {
            max = count;
            maxElement = a[i];
        }
    }
    printf("\nThe most repeating element : %d", maxElement);

    return 0;
}