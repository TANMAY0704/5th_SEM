/* To store random numbers into an array of N integers, where the array
must contains some duplicates and then do the following:
a) Find out the total number of duplicate elements.
b) Find out the most repeating element in the array.*/ 


#include<stdio.h>
#include<stdlib.h>
int duplicates_count(int arr[], int size) 
{
    int total = 0;

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                total++;
                break; // Only count one duplicate per element
            }
        }
    }

    return total; 
}

int most_repeating_element(int arr[], int size) 
{
    int max_element = 0;
    int max_repeats = 0;

    for (int i = 0; i < size; i++) {
        int current_element = arr[i];
        int current_repeats = 0;

        for (int j = i; j < size; j++) {
            if (arr[j] == current_element) {
                current_repeats++;
            }
        }

        if (current_repeats > max_repeats) {
            max_element = current_element;
            max_repeats = current_repeats;
        }
    }

    return max_element;
}

void main()
{
    int n, arr[100];
    printf("ENTER SIZE OF THE ARRAY:");
    scanf("%d", &n); 
    printf("ENTER THE ARRAY ELEMENTS:");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("\n");

    int duplicates= duplicates_count(arr, n);
    printf("Total number of duplicate elements: %d\n", duplicates);

    int max_repeating_element = most_repeating_element(arr, n);
    printf("Most repeating element: %d\n", max_repeating_element);

}