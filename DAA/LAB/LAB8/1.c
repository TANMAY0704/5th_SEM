#include <stdio.h>

void bfs(int n, int g[n][n], int f1[], int f2[], int s, int d[]) {
    for (int i = 0; i < n; i++) {
        if (g[s][i] > 0 && f1[i] == 0) {
            printf("%d ", i + 1);
            f1[i] = 1;
            d[i] = d[s] + g[s][i];
        }
    }

    for (int i = 0; i < n; i++) {
        if (g[s][i] > 0 && f2[i] == 0) {
            f2[i] = 1;
            bfs(n, g, f1, f2, i, d);
        }
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int g[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u - 1][v - 1] = 2;
        g[v - 1][u - 1] = 2;
    }

    int s;
    scanf("%d", &s);
    int f1[n], f2[n];
    int d[n];
    for (int i = 0; i < n; i++) {
        d[i] = -1;
        f1[i] = 0;
        f2[i] = 0;
    }
    f1[s - 1] = 1;
    d[s - 1] = 0; 
    printf("%d ", s);
    bfs(n, g, f1, f2, s - 1, d);
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", d[i]);
    }
    printf("\n");

    return 0;
}