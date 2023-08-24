#include <stdio.h>
#include <stdlib.h>

int insert_sort(int arr[],int n){
    int i,j,temp;
    for(i=1;i<n;i++){
        temp=arr[i];
        j=i-1;
        while(j>=0 && arr[j] > temp){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=temp;
    }
}
int main() {
    int choice,n,i,comparisons=0;
    int *arr, *sorted_arr;
    FILE *input_file,*output_file;

    printf("MAIN MENU (INSERTION SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Data\n");
    printf("4. ERROR (EXIT)\n");

    do{
        printf("Enter option: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                input_file = fopen("inAsce.dat", "r");
                output_file = fopen("outInsAsce.dat", "w");
            break;
            case 2:
                input_file = fopen("inDesc.dat", "r");
                output_file = fopen("outInsDesc.dat", "w");
                break;
            case 3:
                input_file = fopen("inRand.dat", "r");
                output_file = fopen("outInsRand.dat", "w");
                break;
            case 4:
               exit(0);
            default:
                printf("Invalid choice!\n");
                continue;    
        }

        fscanf(input_file, "%d", &n);
        arr=(int*)malloc(n*sizeof(int));
        sorted_arr=(int*)malloc(n*sizeof(int));

        for (i = 0; i < n; i++) {
            fscanf(input_file, "%d", &arr[i]);
        }

        printf("BEFORE SORTING:\n");
        for (i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        insert_sort(arr, n);

        for (i = 0; i < n; i++) {
            sorted_arr[i] = arr[i];
        }

        fprintf(output_file, "%d\n", n);
        for (i = 0; i < n; i++) {
            fprintf(output_file, "%d ", sorted_arr[i]);
        }
        fprintf(output_file, "\n");

        comparisons = n - 1;
        printf("AFTER SORTING:\n");
        for (i = 0; i < n; i++) {
            printf("%d ", sorted_arr[i]);
        }
        printf("\n");
        printf("Number of Comparisons: %d\n", comparisons);
        if (comparisons == 0) {
            printf("Scenario: Best Case\n");
        } else if (comparisons == n * (n - 1) / 2) {
            printf("Scenario: Worst Case\n");
        } else {
            printf("Scenario: General Case\n");
        }

        free(arr);
        free(sorted_arr);
        fclose(input_file);
        fclose(output_file);
    } while (choice != 4);
    
    return 0;
}