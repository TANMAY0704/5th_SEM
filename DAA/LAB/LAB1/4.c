#include <stdio.h>

void swap(int *p, int *q) {
    int temp = *p;
    *p = *q;
    *q = temp;
}

void rotateRight(int p, int q, int arr[], int n) {
    for (int i = q; i > p; i--) {
        swap(&arr[i], &arr[i - 1]);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void readArray(int arr[], int n) {
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of elements.\n");
        return 1;
    }

    int arr[n];
    readArray(arr, n);

    int p, q;
    printf("Enter the range [p, q] to rotate (0-indexed): ");
    scanf("%d %d", &p, &q);

    if (p < 0 || p >= n || q < 0 || q >= n || p > q) {
        printf("Invalid range.\n");
        return 1;
    }

    rotateRight(p, q, arr, n);

    printf("Array after rotation: ");
    printArray(arr, n);

    return 0;
}
