#include <stdio.h>
void readArray(int a[], int n)
{
    printf("Enter the element of the array : ");
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
void multiplyExceptSelf(int arr[], int n, int output[]) {
    int product = 1;

    for (int i = 0; i < n; i++)
        product *= arr[i];

    for (int i = 0; i < n; i++) {
        output[i] = product / arr[i];
    }
}

int main() {
    int n;
    int output[n],arr[n];

    printf("Enter the size of the array : ");
    scanf("%d", &n);
    
    readArray(arr, n);

    printf("Original array: ");
    printArray(arr,n);

    multiplyExceptSelf(arr, n, output);

    printf("\nArray after multiplication: ");
    printArray(output, n);

    return 0;
}
