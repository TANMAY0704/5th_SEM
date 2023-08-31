#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform Merge Sort
void merge(int arr[], int left, int mid, int right, long long *comparisons) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        (*comparisons)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right, long long *comparisons) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comparisons);
        mergeSort(arr, mid + 1, right, comparisons);
        merge(arr, left, mid, right, comparisons);
    }
}

<<<<<<< Updated upstream
    while (fscanf(in, "%d", &num) == 1) {
        arr[n] = num;
        n++;
    }


    mergesort(arr, 0, n - 1);

    

    for (int i = 0; i < n; i++) {
        fprintf(out, "%d ", arr[i]);
    }

    

    printf("AFTER SORTING:\n");
    for (int i = 0; i < n; i++) {
=======
// Function to print array elements
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
>>>>>>> Stashed changes
        printf("%d ", arr[i]);
    printf("\n");
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
}

int main() {
    FILE *inputFile;
    FILE *outputFile;
    int choice;

    while (1) {
        printf("MAIN MENU (MERGE SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. EXIT\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        if (choice == 4) {
            printf("Exiting program...\n");
            break;
        }

        char *inputFilename, *outputFilename;

        if (choice == 1) {
            inputFilename = "inAsc.dat";
            outputFilename = "outMergeAsce.dat";
        } else if (choice == 2) {
            inputFilename = "inDesc.dat";
            outputFilename = "outMergeDesc.dat";
        } else if (choice == 3) {
            inputFilename = "inRand.dat";
            outputFilename = "outMergeRand.dat";
        } else {
            printf("Invalid option. Please choose a valid option.\n");
            continue;
        }

        inputFile = fopen(inputFilename, "r");
        if (inputFile == NULL) {
            printf("Error opening input file.\n");
            exit(1);
        }

        int numElements;
        fscanf(inputFile, "%d", &numElements);

        int arr[numElements];
        for (int i = 0; i < numElements; i++) {
            fscanf(inputFile, "%d", &arr[i]);
        }

        fclose(inputFile);

        long long comparisons = 0;

        clock_t start = clock();
        mergeSort(arr, 0, numElements - 1, &comparisons);
        clock_t end = clock();

        outputFile = fopen(outputFilename, "w");
        if (outputFile == NULL) {
            printf("Error opening output file.\n");
            exit(1);
        }

        for (int i = 0; i < numElements; i++) {
            fprintf(outputFile, "%d\n", arr[i]);
        }

        fclose(outputFile);

        printf("Before Sorting: ");
        printArray(arr, numElements);
        printf("After Sorting: ");
        printArray(arr, numElements);
        printf("Number of Comparisons: %lld\n", comparisons);

        // Calculate and print execution time
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Execution Time: %lf seconds\n", time_taken);
    }

    return 0;
}
