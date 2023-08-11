#include <stdio.h>

int count = 0;

int binarysearch(int arr[], int num, int s, int e) {
    count++;
    if (s <= e) {
        int mid = (s + e) / 2;
        if (arr[mid] == num) {
            
            if (mid == 0 || arr[mid - 1] != num)
                return mid;
            else
                return binarysearch(arr, num, s, mid - 1);
        } else if (arr[mid] > num) {
            return binarysearch(arr, num, s, mid - 1);
        } else {
            return binarysearch(arr, num, mid + 1, e);
        }
    }
    return -1;
}

int main() {
    int n;
    printf("Enter the length of the array: ");
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int num;
    printf("Enter the element to be searched: ");
    scanf("%d", &num);
    int result = binarysearch(arr, num, 0, n - 1);
    if (result != -1)
        printf("Leftmost occurrence of element at index %d, number of searches = %d\n", result, count);
    else
        printf("Element not found in the array, number of searches = %d\n", count);
    return 0;
}
