#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>
using namespace std;

void parallel_bfs(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node;
        #pragma omp critical
        {
            node = q.front();
            q.pop();
        }
        cout << "BFS visiting: " << node << endl;

        #pragma omp parallel for
        for (int i = 0; i < graph[node].size(); i++) {
            int neighbor = graph[node][i];
            if (!visited[neighbor]) {
                #pragma omp critical
                {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
        }
    }
}

void parallel_dfs(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    stack<int> stk;
    stk.push(start);

    while (!stk.empty()) {
        int node;
        #pragma omp critical
        {
            node = stk.top();
            stk.pop();
        }

        if (!visited[node]) {
            visited[node] = true;
            cout << "DFS visiting: " << node << endl;

            #pragma omp parallel for
            for (int i = 0; i < graph[node].size(); i++) {
                int neighbor = graph[node][i];
                if (!visited[neighbor]) {
                    #pragma omp critical
                    stk.push(neighbor);
                }
            }
        }
    }
}

int main() {
    int nodes, edges;
    cout << "Enter number of nodes and edges: ";
    cin >> nodes >> edges;

    vector<vector<int>> graph(nodes);
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // undirected
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
