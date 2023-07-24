/*To take three variable (a, b, c) as separate parameters and swap the
values stored so that value a goes to b, b to c and c to a by using a SWAP(x,y) function that
swaps/exchanges the numbers x & y.*/

#include <stdio.h>

void SWAP(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void swap_variables(int *a, int *b, int *c) {
    SWAP(a, b);
    SWAP(b, c);
}

void main()
{
    int a, b, c;

    printf("Enter the value of a: ");
    scanf("%d", &a);

    printf("Enter the value of b: ");
    scanf("%d", &b);

    printf("Enter the value of c: ");
    scanf("%d", &c);

    printf("Before swapping:\n");
    printf("a = %d, b = %d, c = %d\n", a, b, c);

    swap_variables(&a, &b, &c);

    printf("After swapping:\n");
    printf("a = %d, b = %d, c = %d\n", a, b, c);
}
