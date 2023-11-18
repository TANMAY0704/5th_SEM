#include<stdio.h>
#include<stdlib.h>

void insertionSort(FILE *in, FILE *out) {
    int numArray[1000];
    int num, i, j, n = 0;

    while (fscanf(in, "%d", &num) == 1) {
        numArray[n] = num;
        n++;
    }

    for (i = 1; i < n; i++) 
    {
        int key = numArray[i];
        j = i - 1;
        while (j >= 0 && numArray[j] > key) 
        {
            numArray[j + 1] = numArray[j];
            j = j - 1;
        }
        numArray[j + 1] = key;
    }

    for (i = 0; i < n; i++) {
        fprintf(out, "%d ", numArray[i]);
    }
}

int main() {
    int choice;


    while (1) {
    printf("\n\nMAIN MENU (INSERTION SORT)\n1. Ascending Data\n2. Descending Data\n3. Random Data\n4. ERROR (EXIT)\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        FILE *in ;
        FILE *out;
        switch (choice) {
            case 1:
                {
                    in = fopen("inAsc.dat", "r");
                    out = fopen("outAsc.dat", "w");
                    insertionSort(in, out);
                    fclose(in);
                    fclose(out);
                }
                break;
            case 2:
                {

                    in = fopen("inDesc.dat", "r");
                    out = fopen("outDesc.dat", "w");
                    insertionSort(in, out);
                    fclose(in);
                    fclose(out);
                }
                break;
            case 3:
                {
                    in = fopen("inRand.dat", "r");
                    out = fopen("outRand.dat", "w");
                    insertionSort(in, out);
                    fclose(in);
                    fclose(out);
                }
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
