#include <stdio.h>

// Function to swap two elements
void swap(int *a_rs_69, int *b_rs_69) {
    int temp = *a_rs_69;
    *a_rs_69 = *b_rs_69;
    *b_rs_69 = temp;
}

// Function to rearrange array elements
void rearrangeArray(int arr_rs_69[], int n_rs_69) {
    int l_rs_69 = 0; 
    int r_rs_69 = n_rs_69 - 1; 

    while (l_rs_69 < r_rs_69) 
    {
        while (arr_rs_69[l_rs_69] % 2 == 0 && l_rs_69 < r_rs_69)
            l_rs_69++;


        while (arr_rs_69[r_rs_69] % 2 != 0 && l_rs_69 < r_rs_69)
            r_rs_69--;

    
        if (l_rs_69 < r_rs_69) 
        {
            swap(&arr_rs_69[l_rs_69], &arr_rs_69[r_rs_69]);
            l_rs_69++;
            r_rs_69--;
        }
    }
}

void main() 
{
    int arr_rs_69[20],n_rs_69;
    printf("ENTER ARRAY SIZE:");
    scanf("%d", &n_rs_69);
    printf("ENTER ARRAY ELEMENTS:\n_rs_69");
    for(int i_rs_69=0;i_rs_69<n_rs_69;i_rs_69++)
    {
        scanf("%d",&arr_rs_69[i_rs_69]);
    }

    printf("Original Array: ");
    for (int i_rs_69 = 0; i_rs_69 < n_rs_69; i_rs_69++) {
        printf("%d ", arr_rs_69[i_rs_69]);
    }

    rearrangeArray(arr_rs_69, n_rs_69);

    printf("\nRearranged Array: ");
    for (int i_rs_69 = 0; i_rs_69 < n_rs_69; i_rs_69++) {
        printf("%d ", arr_rs_69[i_rs_69]);
    }

}



