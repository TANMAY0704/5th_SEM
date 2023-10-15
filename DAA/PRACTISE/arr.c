#include <stdio.h>
#include <stdlib.h>
void readArray(int a[], int n)
{
    for (int i = 0; i < n ; i++)
    {
        scanf("%d", &a[i]);
    }

}
void printArray(int a[] , int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    
}
void mul(int a[], int b[],int n)
{
    for (int i = 0; i < n; i++)
    {
        if (i==0)
        {

            for ( int j = 1; i <= n; j++)
            {
                b[0] *= a[j];
            }
            
        }
        
    }
    
}
int main()
{
    int n;
    printf("Enter the size of the array : ");
    scanf("%d", &n);
    int a[n],b[n];;
    printf("Enter elements : ");
    readArray(a, n);
    mul(a, b, n);
    printArray(b,n);

    return 0;
}