#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void merge(int a[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
    {
        L[i] = a[l + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = a[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }  
    while (i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }
}
void mergesort(int a[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergesort(a, l, m);
        mergesort(a, m + 1, r);
        merge(a, l, m, r);
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

    mergesort(arr, 0, n - 1);

    clock_t end_time = clock(); // End measuring execution time

    for (int i = 0; i < n; i++) {
        fprintf(out, "%d ", arr[i]);
    }

    comparisons = n * (n - 1) / 2; // Calculate the number of comparisons

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
        printf("\n\nMAIN MENU (MERGE SORT)\n1. Ascending Data\n2. Descending Data\n3. Random Data\n4. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        FILE *in;
        FILE *out;

        switch (choice) {
            case 1:
                in = fopen("inAsc.dat", "r");
                out = fopen("outMergeAsce.dat", "w");
                Sort(in, out);
                fclose(in);
                fclose(out);
                break;
            case 2:
                in = fopen("inDesc.dat", "r");
                out = fopen("outMergeDesc.dat", "w");
                Sort(in, out);
                fclose(in);
                fclose(out);
                break;
            case 3:
                in = fopen("inRand.dat", "r");
                out = fopen("outMergeRand.dat", "w");
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
