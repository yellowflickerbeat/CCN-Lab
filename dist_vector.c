#include <stdio.h>

struct node {
    int dist[20];   // Distance to all nodes
    int via[20];    // Next-hop for each destination
} rt[10];

int main() {

    int cost[20][20];
    int n, i, j, k, updated;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("\nEnter cost matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);

            // Distance to itself is always 0
            if (i == j) cost[i][j] = 0;

            // Initialize routing table:
            rt[i].dist[j] = cost[i][j];  // direct cost
            rt[i].via[j]  = j;           // initially via destination
        }
    }

    // ------------------------------------------------------------
    // Distance Vector Algorithm (Bellman–Ford):
    // Keep updating until no router changes its table
    // ------------------------------------------------------------
    do {
        updated = 0;

        for (i = 0; i < n; i++) {         // for each router
            for (j = 0; j < n; j++) {     // for each destination
                for (k = 0; k < n; k++) { // check via each neighbor

                    // If going i → k → j is cheaper, update
                    if (rt[i].dist[j] > cost[i][k] + rt[k].dist[j]) {

                        rt[i].dist[j] = cost[i][k] + rt[k].dist[j];
                        rt[i].via[j] = k;
                        updated = 1;      // at least one change occurred
                    }
                }
            }
        }

    } while (updated);   // Repeat until stable (no changes)

    // ------------------------------------------------------------
    // Print final routing tables
    // ------------------------------------------------------------
    for (i = 0; i < n; i++) {
        printf("\nRouting table for Router %d:", i + 1);
        for (j = 0; j < n; j++) {
            printf("\n  To Node %d via %d, Distance = %d",
                   j + 1, rt[i].via[j] + 1, rt[i].dist[j]);
        }
    }

    printf("\n");
    return 0;
}
