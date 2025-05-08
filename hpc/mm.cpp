//new bfs dfs

#include <omp.h>
#include <iostream>
#include <queue>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Node {
public:
    int value;
    Node *left = nullptr, *right = nullptr;
    Node(int val) : value(val) {}
    Node() {}
};

Node* generateTree(int values[], int n) {
    if (n == 0) return nullptr;
    Node* nodes[n];
    for (int i = 0; i < n; ++i)
        nodes[i] = (values[i] != -1) ? new Node(values[i]) : nullptr;
    for (int i = 0, j = 1; j < n; ++i) {
        if (nodes[i]) {
            if (j < n) nodes[i]->left = nodes[j++];
            if (j < n) nodes[i]->right = nodes[j++];
        }
    }
    return nodes[0];
}

void bfs(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front(); q.pop();
        cout << node->value << " -> ";
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}

void dfs(Node* root) {
    if (!root) return;
    #pragma omp critical
    cout << root->value << " -> ";
    #pragma omp parallel sections num_threads(2)
    {
        #pragma omp section
        dfs(root->left);
        #pragma omp section
        dfs(root->right);
    }
}

int main() {
    int values[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}, n = sizeof(values)/sizeof(int);
    Node* root = generateTree(values, n);

    auto start_bfs = high_resolution_clock::now();
    cout << "BFS: "; bfs(root);
    auto duration_bfs = duration_cast<microseconds>(high_resolution_clock::now() - start_bfs);
    cout << "\nExecution time for BFS: " << duration_bfs.count() << " microseconds" << endl;

    auto start_dfs = high_resolution_clock::now();
    cout << "DFS: "; dfs(root);
    auto duration_dfs = duration_cast<microseconds>(high_resolution_clock::now() - start_dfs);
    cout << "\nExecution time for DFS: " << duration_dfs.count() << " microseconds" << endl;

    return 0;
}

