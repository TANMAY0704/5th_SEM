/* To store random numbers into an array of N integers, where the array
must contains some duplicates and then do the following:
a) Find out the total_rs_69 number of duplicate elements.
b) Find out the most repeating element in the array.*/ 


#include<stdio.h>
#include<stdlib.h>
int duplicates_count(int arr_rs_69[], int size_rs_69) 
{
    int total_rs_69 = 0;

    for (int i = 0; i < size_rs_69 - 1; i++) {
        for (int j = i + 1; j < size_rs_69; j++) {
            if (arr_rs_69[i] == arr_rs_69[j]) {
                total_rs_69++;
                break; // Only count one duplicate per element
            }
        }
    }

    return total_rs_69; 
}

int most_repeating_element(int arr_rs_69[], int size_rs_69) 
{
    int max_rs_69 = 0;
    int max_repeats_rs_69 = 0;

    for (int i = 0; i < size_rs_69; i++) {
        int curr_element_rs_69 = arr_rs_69[i];
        int curr_repeats_rs_69 = 0;

        for (int j = i; j < size_rs_69; j++) {
            if (arr_rs_69[j] == curr_element_rs_69) {
                curr_repeats_rs_69++;
            }
        }

        if (curr_repeats_rs_69 > max_repeats_rs_69) {
            max_rs_69 = curr_element_rs_69;
            max_repeats_rs_69 = curr_repeats_rs_69;
        }
    }

    return max_rs_69;
}

void main()
{
    int n, arr_rs_69[100];
    printf("ENTER SIZE OF THE ARRAY:");
    scanf("%d", &n); 
    printf("ENTER THE ARRAY ELEMENTS:");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr_rs_69[i]);
    }
    printf("\n");

    int duplicates= duplicates_count(arr_rs_69, n);
    printf("Total number of duplicate elements: %d\n", duplicates);

    int max_repeating_element = most_repeating_element(arr_rs_69, n);
    printf("Most repeating element: %d\n", max_repeating_element);

}