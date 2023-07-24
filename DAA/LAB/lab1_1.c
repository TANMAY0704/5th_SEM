/*To store random numbers into an array of N integers and then find out
the smallest and largest number stored in it. N is the user input.*/


#include<stdio.h>
#include<stdlib.h>
int smallest_element(int arr[], int size) 
{
    int smallest = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] < smallest) 
        {
            smallest = arr[i];
        }
    }
    return smallest;
}
 int largest_element(int arr[], int size) 
 {
    int largest = arr[0];
    for (int i = 1; i < size; i++) 
    {
        if (arr[i] > largest) 
        {
            largest = arr[i];
        }
    }
    return largest;
}
void main()
{
    int n, arr[100];
    printf("ENTER ARRAY SIZE:");
    scanf("%d", &n);
    printf("ENTER ARRAY ELEMENTS:");
    for(int i=0;i<n;i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("\n");
    int smallest = smallest_element(arr,n);
    int largest = largest_element(arr,n);

    printf("Smallest number is: %d\n", smallest);
    printf("Largest number is: %d\n", largest);
}