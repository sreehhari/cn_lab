#include <stdio.h>
#include <stdlib.h>

#define INF 999

int main() {
    int nodes, i, j, k, dist[10][10], next_hop[10][10];
    printf("Enter number of nodes: ");
    scanf("%d", &nodes);

    printf("Enter distance matrix (use 999 for infinity):\n");
    for(i = 0; i < nodes; i++)
        for(j = 0; j < nodes; j++)
            scanf("%d", &dist[i][j]);

    // Initialize next hop
    for(i = 0; i < nodes; i++)
        for(j = 0; j < nodes; j++)
            next_hop[i][j] = j;

    // Bellman-Ford algorithm
    for(k = 0; k < nodes; k++)
        for(i = 0; i < nodes; i++)
            for(j = 0; j < nodes; j++)
                if(dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next_hop[i][j] = next_hop[i][k];
                }

    printf("\nDistance Vector Table:\n");
    for(i = 0; i < nodes; i++) {
        for(j = 0; j < nodes; j++)
            printf("%d ", dist[i][j]);
        printf("\n");
    }

    printf("\nNext Hop Table:\n");
    for(i = 0; i < nodes; i++) {
        for(j = 0; j < nodes; j++)
            printf("%d ", next_hop[i][j]);
        printf("\n");
    }
    return 0;
}