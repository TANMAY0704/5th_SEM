#include <stdio.h>

void exchange(int *p, int *q)
{
    int c = *p;
    *p = *q;
    *q = c;
}

void rotate_right(int p, int q, int arr[])
{
    int temp = p;
    int rep = q;
    for (int i = q; i > p; i--)
    {
        exchange(&arr[i],&arr[i-1]);
    }
    p = temp;
    q = rep;
}

void printarr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
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

    int p, q;
    printf("Enter the range [p,q] to rotate : ");
    scanf("%d %d", &p, &q);

    if (p >= 0 && p < n && q >= 0 && q < n && p <= q)
    {
        rotate_right(p,q,arr);
        printarr(arr, n);
    }
    else
    {
        printf("Invalid range.\n");
    }

    return 0;
}