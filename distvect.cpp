#include <iostream>
using namespace std;

const int INF = 1000;

int BellmanFord(int G[100][100], int V, int E, int edge[100][2]) {
    int distance[100], S, flag = 1;

    for (int i = 0; i < V; i++)
        distance[i] = INF;

    cout << "\nEnter source: ";
    cin >> S;
    distance[S - 1] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (int k = 0; k < E; k++) {
            int u = edge[k][0];
            int v = edge[k][1];
            if (distance[u] + G[u][v] < distance[v])
                distance[v] = distance[u] + G[u][v];
        }
    }

    for (int k = 0; k < E; k++) {
        int u = edge[k][0];
        int v = edge[k][1];
        if (distance[u] + G[u][v] < distance[v])
            flag = 0;
    }

    if (flag) {
        cout << "\nShortest distances from source " << S << ":\n";
        for (int i = 0; i < V; i++)
            cout << "To vertex " << i + 1 << ": " << distance[i] << "\n";
        cout << "\nNo negative weight cycle exists\n";
    } else {
        cout << "\nGraph contains a negative weight cycle\n";
    }

    return flag;
}

int main() {
    int V, edge[100][2], G[100][100];

    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter graph in matrix form:\n";
    int k = 0;  
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) {
            cin >> G[i][j];
            if (G[i][j] != 0)
                edge[k][0] = i, edge[k++][1] = j;
        }

    (BellmanFord(G, V, k, edge));

    return 0;
}

//example
/*
no neg wt cycle
3
1 2 2 
2 3 1
1 3 5
1

with neg wt cycle
3
1 3 2
-1 -2 3
3 2 1
1
*/
