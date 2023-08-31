#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

struct person *personArray;
int heapSize = 0;

void swap(struct person *a, struct person *b) {
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < heapSize && personArray[left].age < personArray[smallest].age)
        smallest = left;

    if (right < heapSize && personArray[right].age < personArray[smallest].age)
        smallest = right;

    if (smallest != index) {
        swap(&personArray[index], &personArray[smallest]);
        minHeapify(smallest);
    }
}

void maxHeapify(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;

    if (left < heapSize && personArray[left].weight > personArray[largest].weight)
        largest = left;

    if (right < heapSize && personArray[right].weight > personArray[largest].weight)
        largest = right;

    if (largest != index) {
        swap(&personArray[index], &personArray[largest]);
        maxHeapify(largest);
    }
}

void buildMinHeap() {
    for (int i = heapSize / 2 - 1; i >= 0; i--)
        minHeapify(i);
}

void buildMaxHeap() {
    for (int i = heapSize / 2 - 1; i >= 0; i--)
        maxHeapify(i);
}

int main() {
    int choice, n;

    while (1) {
        printf("MAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        if (choice == 7) {
            printf("Exiting program...\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter the number of students: ");
                scanf("%d", &n);

                personArray = (struct person *)malloc(n * sizeof(struct person));

                FILE *inputFile = fopen("input.txt", "r");
                if (inputFile == NULL) {
                    printf("Error opening input file.\n");
                    exit(1);
                }

                for (int i = 0; i < n; i++) {
                    fscanf(inputFile, "%d %d %d", &personArray[i].age, &personArray[i].height, &personArray[i].weight);
                    personArray[i].id = i;
                    personArray[i].name = (char *)malloc(100 * sizeof(char));
                    fscanf(inputFile, "%s", personArray[i].name);
                }

                fclose(inputFile);
                heapSize = n;
                break;

            case 2:
                buildMinHeap();
                printf("Min-heap based on age created.\n");
                break;

            case 3:
                buildMaxHeap();
                printf("Max-heap based on weight created.\n");
                break;

            case 4:
                printf("Weight of youngest student: %.2lf kg\n", personArray[0].weight * 0.453592);
                break;

            case 5:
                heapSize++;
                personArray = (struct person *)realloc(personArray, heapSize * sizeof(struct person));

                int newIndex = heapSize - 1;
                personArray[newIndex].id = newIndex;
                personArray[newIndex].name = (char *)malloc(100 * sizeof(char));
                scanf("%s %d %d %d", personArray[newIndex].name, &personArray[newIndex].age, &personArray[newIndex].height, &personArray[newIndex].weight);

                int parent = (newIndex - 1) / 2;
                while (newIndex > 0 && personArray[parent].age > personArray[newIndex].age) {
                    swap(&personArray[parent], &personArray[newIndex]);
                    newIndex = parent;
                    parent = (newIndex - 1) / 2;
                }

                printf("New student inserted into the Min-heap.\n");
                break;

            case 6:
                if (heapSize == 0) {
                    printf("Heap is empty.\n");
                } else {
                    swap(&personArray[0], &personArray[heapSize - 1]);
                    heapSize--;
                    minHeapify(0);
                    printf("Oldest person deleted.\n");
                }
                break;

            default:
                printf("Invalid option. Please choose a valid option.\n");
                break;
        }
    }

    for (int i = 0; i < heapSize; i++) {
        free(personArray[i].name);
    }
    free(personArray);

    return 0;
}
