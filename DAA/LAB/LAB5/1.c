#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

typedef struct person Person;

void swap(Person *a, Person *b)
{
    Person temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(Person *arr, int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].age < arr[smallest].age)
        smallest = left;

    if (right < n && arr[right].age < arr[smallest].age)
        smallest = right;

    if (smallest != i)
    {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void buildMinHeap(Person *arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);
}

void maxHeapify(Person *arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].weight > arr[largest].weight)
        largest = left;

    if (right < n && arr[right].weight > arr[largest].weight)
        largest = right;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void buildMaxHeap(Person *arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

void displayYoungestWeight(Person *arr)
{
    printf("Weight of the youngest person: %d\n", arr[0].weight);
}

void insertIntoMinHeap(Person *arr, int *n)
{
    (*n)++;
    int i = (*n) - 1;
    while (i > 0 && arr[(i - 1) / 2].age > arr[i].age)
    {
        swap(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void deleteFromMaxHeap(Person *arr, int *n)
{
    if (*n == 0)
    {
        printf("Heap is empty!\n");
        return;
    }

    swap(&arr[0], &arr[*n - 1]);
    (*n)--;
    maxHeapify(arr, *n, 0);
}

int main()
{
    int choice, n = 0;
    Person *persons = NULL;

    FILE *file = fopen("input.txt", "r");

    do
    {
        printf("\nMenu:\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on age\n");
        printf("3. Create a Max-heap based on weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (file == NULL)
            {
                printf("Error opening the file.\n");
                return 1;
            }

            fscanf(file, "%d", &n);
            persons = (Person *)malloc(n * sizeof(Person));
            for (int i = 0; i < n; i++)
            {
                persons[i].name = (char *)malloc(50 * sizeof(char));
                fscanf(file, "%d %s %d %d %d", &persons[i].id, persons[i].name, &persons[i].age, &persons[i].height, &persons[i].weight);
            }

            fclose(file);
            printf("Data read successfully.\n");
            break;

        case 2:
            buildMinHeap(persons, n);
            printf("Min-heap based on age created.\n");
            break;

        case 3:
            buildMaxHeap(persons, n);
            printf("Max-heap based on weight created.\n");
            break;

        case 4:
            if (n > 0)
                displayYoungestWeight(persons);
            else
                printf("No data available.\n");
            break;

        case 5:
            if (n > 0)
            {
                Person newPerson;
                newPerson.name = (char *)malloc(50 * sizeof(char));
                printf("Enter person details (id name age height weight): ");
                scanf("%d %s %d %d %d", &newPerson.id, newPerson.name, &newPerson.age, &newPerson.height, &newPerson.weight);

                persons = (Person *)realloc(persons, (n + 1) * sizeof(Person));
                persons[n] = newPerson;

                insertIntoMinHeap(persons, &n);
                printf("Person inserted into the Min-heap.\n");
            }
            else
                printf("No data available.\n");
            break;

        case 6:
            if (n > 0)
            {
                deleteFromMaxHeap(persons, &n);
                printf("Oldest person deleted from the Max-heap.\n");
            }
            else
                printf("No data available.\n");
            break;

        case 7:
            printf("Exiting the program.\n");
            free(persons);
            break;

        default:
            printf("Invalid choice! Please select a valid option.\n");
        }

    } while (choice != 7);

    return 0;
}