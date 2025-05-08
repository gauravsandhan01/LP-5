#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

// Parallel BFS
void parallel_bfs(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << "BFS visiting: " << node << endl;

        #pragma omp parallel for
        for (int i = 0; i < graph[node].size(); i++) {
            int adj = graph[node][i];
            if (!visited[adj]) {
                #pragma omp critical
                {
                    if (!visited[adj]) {
                        visited[adj] = true;
                        q.push(adj);
                    }
                }
            }
        }
    }
}

void dfs_helper(const vector<vector<int>>& graph, vector<bool>& visited, int node) {
    visited[node] = true;
    cout << "DFS visiting: " << node << endl;

    for (int adj : graph[node]) {
        if (!visited[adj]) {
            dfs_helper(graph, visited, adj);
        }
    }
}

void parallel_dfs(const vector<vector<int>>& graph, int start) {
    vector<bool> visited(graph.size(), false);
    dfs_helper(graph, visited, start);
}

int main() {
    int nodes, edges;
    cout << "Enter number of nodes and edges: ";
    cin >> nodes >> edges;

    vector<vector<int>> graph(nodes);

    cout << "Enter " << edges << " edges (u v):\n";
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // For undirected graph
    }

    int start;
    cout << "Enter starting node: ";
    cin >> start;

    cout << "\nParallel BFS:\n";
    parallel_bfs(graph, start);

    cout << "\nParallel DFS:\n";
    parallel_dfs(graph, start);

    return 0;
}
