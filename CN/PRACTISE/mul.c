#include <stdio.h>
#include <stdlib.h>
void array(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
}
void mul_array(int a[], int b[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int mul = 1;
        int x = a[i];
        for (int j = 0; j < n; j++)
        {
            b[i] *= mul * a[i];
        }
        b[i] /= x;
    }
}

int main()
{
    int n;
    printf("Enter the number of elements :");
    scanf("%d", &n);
    int a[n], b[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    mul_array(a, b, n);
    array(b, n);
    return 0;
}