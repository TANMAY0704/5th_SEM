#include <stdio.h>

void SWAP(int *x_rs_69, int *y_rs_69) 
{
    int temp_rs_69 = *x_rs_69;
    *x_rs_69 = *y_rs_69;
    *y_rs_69 = temp_rs_69;
}

void swap_variables(int *a_rs_69, int *b_rs_69, int *c_rs_69) {
    SWAP(a_rs_69, b_rs_69);
    SWAP(b_rs_69, c_rs_69);
}

int main() {
    int a_rs_69, b_rs_69, c_rs_69;

    printf("Enter the value of a: ");
    scanf("%d", &a_rs_69);

    printf("Enter the value of b: ");
    scanf("%d", &b_rs_69);

    printf("Enter the value of c: ");
    scanf("%d", &c_rs_69);

    printf("Before swapping:\n");
    printf("a_rs_69 = %d, b_rs_69 = %d, c_rs_69 = %d\n", a_rs_69, b_rs_69, c_rs_69);

    swap_variables(&a_rs_69, &b_rs_69, &c_rs_69);

    printf("After swapping:\n");
    printf("a_rs_69 = %d, b_rs_69 = %d, c_rs_69 = %d\n", a_rs_69, b_rs_69, c_rs_69);

    return 0;
}

