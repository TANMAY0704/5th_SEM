#include <stdio.h>

int min(int arr[], int n)
{
    int min, max, min2, max2;
    if (arr[0] > arr[1])
    {
        max = arr[0];
        min = arr[1];
        min2 = max;
        max2 = min;
    }
    else
    {
        max = arr[1];
        min = arr[0];
        min2 = min;
        max2 = max;
    }
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min)
        {
            min2 = min;
            min = arr[i];
        }
        else if (arr[i] < min2 && arr[i] > min)
        {
            min2 = arr[i];
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max)
        {
            max2 = max;
            max = arr[i];
        }
        else if (arr[i] > max2 && arr[i] < max)
        {
            max2 = arr[i];
        }
    }
    return (min2);
}
int max(int arr[], int n)
{
    int max, max2;
    if (arr[0] > arr[1])
    {
        max = arr[0];
        max2 = arr[1];
    }
    else
    {
        max = arr[1];
        max2 = arr[0];
    }
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max)
        {
            max2 = max;
            max = arr[i];
        }
        else if (arr[i] > max2 && arr[i] < max)
        {
            max2 = arr[i];
        }
    }
    return (max2);
}
void readarr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
}
int main()
{
    int n;
    printf("Enter the number of elements :");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements : ");
    readarr(arr, n);
    printf("%d,%d", min(arr, (sizeof(arr) / sizeof(arr[0]))), max(arr, (sizeof(arr) / sizeof(arr[0]))));
}