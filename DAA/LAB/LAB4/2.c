#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high, int *comparisonCount) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        (*comparisonCount)++; // Increment comparison count
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort(int arr[], int low, int high, int *comparisonCount) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisonCount);
        quicksort(arr, low, pi - 1, comparisonCount);
        quicksort(arr, pi + 1, high, comparisonCount);
    }
}

void Sort(FILE *in, FILE *out) {
    int arr[1000];
    int num, n = 0;

    while (fscanf(in, "%d", &num) == 1) {
        arr[n] = num;
        n++;
    }

    int comparisons = 0; // Initialize comparison count

    clock_t start_time = clock(); // Start measuring execution time

    quicksort(arr, 0, n - 1, &comparisons);

    clock_t end_time = clock(); // End measuring execution time

    for (int i = 0; i < n; i++) {
        fprintf(out, "%d ", arr[i]);
    }

    printf("AFTER SORTING:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Number of Comparisons: %d\n", comparisons);
    
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Execution Time: %lf seconds\n", execution_time);

    if (comparisons == 0) {
        printf("Scenario: Best Case\n");
    } else if (comparisons == n * (n - 1) / 2) {
        printf("Scenario: Worst Case\n");
    } else {
        printf("Scenario: General Case\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n\nMAIN MENU (QUICK SORT)\n1. Ascending Data\n2. Descending Data\n3. Random Data\n4. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        FILE *in;
        FILE *out;

        switch (choice) {
            case 1:
                in = fopen("inAsc.dat", "r");
                out = fopen("outQuickAsce.dat", "w");
                Sort(in, out);
                fclose(in);
                fclose(out);
                break;
            case 2:
                in = fopen("inDesc.dat", "r");
                out = fopen("outQuickDesc.dat", "w");
                Sort(in, out);
                fclose(in);
                fclose(out);
                break;
            case 3:
                in = fopen("inRand.dat", "r");
                out = fopen("outQuickRand.dat", "w");
                Sort(in, out);
                fclose(in);
                fclose(out);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}
