#include <stdio.h>
#include <stdlib.h>

int n;

void readGraph(const char *filename) {
    int graph[n][n];
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found.\n");
        exit(1);
    }

    for  (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }
    //print graph
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    fclose(file);
}
int main()
{
    n=5;
    scanf("%d",&n);
    readGraph("1.dat");
    
    return 0;
}
