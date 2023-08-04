#include<stdio.h>
int countNonZero(int mat_rs_69[][100], int n_rs_69) 
{
    int count_rs_69 = 0;
    for (int i_rs_69 = 0; i_rs_69 < n_rs_69; i_rs_69++) {
        for (int j_rs_69 = 0; j_rs_69 < n_rs_69; j_rs_69++) {
            if (mat_rs_69[i_rs_69][j_rs_69] != 0) {
                count_rs_69++;
            }
        }
    }
    return count_rs_69;
}

int sumAboveDiagonal(int mat_rs_69[][100], int n_rs_69) {
    int sum_rs_69 = 0;
    for (int i_rs_69 = 0; i_rs_69 < n_rs_69; i_rs_69++) {
        for (int j_rs_69 = i_rs_69 + 1; j_rs_69 < n_rs_69; j_rs_69++) {
            sum_rs_69 += mat_rs_69[i_rs_69][j_rs_69];
        }
    }
    return sum_rs_69;
}

void BelowMD(int mat_rs_69[][100], int n_rs_69) 
{
    printf("Elements below the minor diagonal:\n_rs_69");
    for (int i_rs_69 = 1; i_rs_69 < n_rs_69; i_rs_69++) 
    {
        for (int j_rs_69 = 0; j_rs_69 < i_rs_69; j_rs_69++) 
        {
            printf("%d ", mat_rs_69[i_rs_69][j_rs_69]);
        }
        printf("\n_rs_69");
    }
}

int productOfDiagonal(int mat_rs_69[][100], int n_rs_69) {
    int p_rs_69 = 1;
    for (int i_rs_69 = 0; i_rs_69 < n_rs_69; i_rs_69++) {
        p_rs_69 *= mat_rs_69[i_rs_69][i_rs_69];
    }
    return p_rs_69;
}

void main() 
{
    int n_rs_69;
    printf("Enter Matrix Size: ");
    scanf("%d", &n_rs_69);

    int mat_rs_69[100][100];

    printf("Enter the elements of the %d x %d matrix:\n_rs_69", n_rs_69, n_rs_69);
    for (int i_rs_69 = 0; i_rs_69 < n_rs_69; i_rs_69++) 
    {
        for (int j_rs_69 = 0; j_rs_69 < n_rs_69; j_rs_69++) 
        {
            scanf("%d", &mat_rs_69[i_rs_69][j_rs_69]);
        }
    }

    int nonzero_rs_69 = countNonZero(mat_rs_69, n_rs_69);
    printf("Number of non-zero elements: %d\n_rs_69", nonzero_rs_69);

    int sumabovediag_rs_69 = sumAboveDiagonal(mat_rs_69, n_rs_69);
    printf("Sum of elements above the leading diagonal: %d\n_rs_69", sumabovediag_rs_69);

    BelowMD(mat_rs_69, n_rs_69);

    int diagonal_rs_69 = productOfDiagonal(mat_rs_69, n_rs_69);
    printf("Product of diagonal elements: %d\n_rs_69", diagonal_rs_69);
}



