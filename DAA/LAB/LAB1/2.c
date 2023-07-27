#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n, i, j, temp;
    printf("Enter the size of array: ");
    scanf("%d", &n);
    int a[n];
    printf("Enter the elements of array: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    int prefixSum[n];
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            prefixSum[i] = a[i];
        }
        else
        {
            prefixSum[i] = prefixSum[i - 1] + a[i];
        }
        
    }
    
    for (int i = 0; i < n; i++)
    {
        printf("%d ", prefixSum[i]);
    }
    
}