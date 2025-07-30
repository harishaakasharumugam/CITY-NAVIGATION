#include <stdio.h>
#include <limits.h>
#include <string.h>
#define MAX 100
#define INF 9999
int n;
int graph[MAX][MAX];
char name[MAX][50];
void inputGraph() {
    printf("Enter the number of junctions: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter name for junction %d: ", i + 1);
        scanf("%s", name[i]);
    }
    printf("Enter the junction distances (in kilometers).\n");
    printf("Enter 0 if there is no direct road between two junctions:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if (i == j) {
                graph[i][j] = 0; // Ensure diagonal is zero
            } else if (graph[i][j] == 0) {
                graph[i][j] = INF;
            }
        }

    }
    // Display the distance table
    printf("\nJunction Distance Table (in kilometers):\n\n");
    printf("%-12s", "");
    for (int i = 0; i < n; i++) {
        printf("%-12s", name[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%-12s", name[i]);
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == INF)
                printf("%-12s", "*");
            else
                printf("%-12d", graph[i][j]);
        }
        printf("\n");
    }
}
// New function to display map-like adjacency list style
void displayMapLikeLayout() {
    printf("\nMap-like layout (adjacency list style):\n");
    for (int i = 0; i < n; i++) {
        printf("%s -> ", name[i]);
        int first = 1;
        for (int j = 0; j < n; j++) {
            if (graph[i][j] != INF && i != j) {
                if (!first) printf(", ");

                printf("%s(%d km)", name[j], graph[i][j]);
                first = 0;
            }
        }
        if (first) printf("No direct connections");
        printf("\n");
    }
}

int minDistance(int dist[], int visited[]) {
    int min = INF, min_index = -1;
    for (int v = 0; v < n; v++)
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

void dijkstra(int src, int dest) {
    int dist[MAX], visited[MAX], parent[MAX];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }


    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited);
        if (u == -1) break;
        visited[u] = 1;
        for (int v = 0; v < n; v++)
            if (!visited[v] && graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
    }
    int path[MAX], pathLen = 0, temp = dest;
    while (temp != -1) {
        path[pathLen++] = temp;
        temp = parent[temp];
    }
    if (dist[dest] == INF) {
        printf("\nNo path exists between %s and %s.\n", name[src], name[dest]);
        return;
    }
    printf("\nShortest path:\n");
    for (int i = pathLen - 1; i >= 0; i--) {
        printf("%s", name[path[i]]);
        if (i != 0)
            printf(" -> ");
    }

    printf("\nTotal distance: %d kilometers\n", dist[dest]);
}

int main() {
    char choice;
    inputGraph();
    displayMapLikeLayout();  // Display the map-like layout after input
    do {
        int src, dest;
        printf("\nEnter the source junction (0-%d): ", n - 1);
        scanf("%d", &src);
        printf("Enter the destination junction (0-%d): ", n - 1);
        scanf("%d", &dest);
        dijkstra(src, dest);
        printf("Do you want to find another route? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');
    return 0;
}
