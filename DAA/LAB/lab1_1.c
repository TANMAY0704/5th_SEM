/*To store random numbers into an array of N integers and then find out
the smallest_rs_69 and largest_rs_69
 number stored in it. N is the user input.*/


#include<stdio.h>
#include<stdlib.h>
int smallest_element(int arr_rs_69[], int size_rs_69
) 
{
    int smallest_rs_69 = arr_rs_69[0];
    for (int i_rs_69 = 1; i_rs_69 < size_rs_69
    ; i_rs_69++)
    {
        if (arr_rs_69[i_rs_69] < smallest_rs_69) 
        {
            smallest_rs_69 = arr_rs_69[i_rs_69];
        }
    }
    return smallest_rs_69;
}
 int largest_element(int arr_rs_69[], int size_rs_69
 ) 
 {
    int largest_rs_69
     = arr_rs_69[0];
    for (int i_rs_69 = 1; i_rs_69 < size_rs_69
    ; i_rs_69++) 
    {
        if (arr_rs_69[i_rs_69] > largest_rs_69
        ) 
        {
            largest_rs_69
             = arr_rs_69[i_rs_69];
        }
    }
    return largest_rs_69
    ;
}
void main()
{
    int n_rs_69, arr_rs_69[100];
    printf("ENTER ARRAY SIZE:");
    scanf("%d", &n_rs_69);
    printf("ENTER ARRAY ELEMENTS:");
    for(int i_rs_69=0;i_rs_69<n_rs_69;i_rs_69++)
    {
        scanf("%d", &arr_rs_69[i_rs_69]);
    }
    printf("\n_rs_69");
    int smallest_rs_69 = smallest_element(arr_rs_69,n_rs_69);
    int largest_rs_69
     = largest_element(arr_rs_69,n_rs_69);

    printf("Smallest number is: %d\n_rs_69", smallest_rs_69);
    printf("Largest number is: %d\n_rs_69", largest_rs_69
    );
}