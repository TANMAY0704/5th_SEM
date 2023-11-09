#include <stdio.h>
#include <limits.h>

#define INF INT_MAX

void dijkstra(int source, int n, int graph[n][n]) {
    int dist[n];
    int parent[n];
    int visited[n];

    for (int i = 0; i < n; ++i) {
        dist[i] = INF;
        parent[i] = -1;
        visited[i] = 0;
    }

    dist[source - 1] = 0;

    for (int count = 0; count < n - 1; ++count) {
        int u = -1;

        for (int i = 0; i < n; ++i) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        visited[u] = 1;

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && graph[u][v] > 0 && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("Source\tDestination\tCost\tPath\n");
    for (int i = 0; i < n; ++i) {
        if (i != source - 1) {
            printf("%d\t%d\t%d\t", source, i + 1, dist[i]);

            // Display the path
            int current = i;
            while (current != -1) {
                printf("%d", current + 1);
                current = parent[current];
                if (current != -1) {
                    printf("->");
                }
            }

            printf("\n");
        }
    }
}

int main() {
    FILE *inputFile = fopen("1.dat", "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening input file.\n");
        return 1;
    }

    int n;
    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);

    int graph[n][n];

    // Read the graph from the input file
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fscanf(inputFile, "%d", &graph[i][j]);
        }
    }

    int source;
    printf("Enter the Source Vertex: ");
    scanf("%d", &source);

    dijkstra(source, n, graph);

    fclose(inputFile);
    return 0;
}
