#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int source, destination, weight;

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class Graph {
private:
    int vertices, edges;
    vector<Edge> edgeList;

public:
    Graph(int v, int e) : vertices(v), edges(e) {}

    void addEdge(int index, int src, int dest, int weight) {
        edgeList.push_back({ src, dest, weight });
    }

    int find(vector<int>& parent, int i) {
        if (parent[i] != i)
            parent[i] = find(parent, parent[i]);
        return parent[i];
    }

    void unionSet(vector<int>& parent, vector<int>& rank, int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);

        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

    void kruskalMST() {
        sort(edgeList.begin(), edgeList.end());

        vector<int> parent(vertices);
        vector<int> rank(vertices, 0);

        for (int v = 0; v < vertices; v++)
            parent[v] = v;

        vector<Edge> result;
        int edgeCount = 0, i = 0;

        while (edgeCount < vertices - 1 && i < edges) {
            Edge nextEdge = edgeList[i++];

            int x = find(parent, nextEdge.source);
            int y = find(parent, nextEdge.destination);

            if (x != y) {
                result.push_back(nextEdge);
                edgeCount++;
                unionSet(parent, rank, x, y);
            }
        }

        cout << "Edges in the Minimum Spanning Tree:\n";
        for (const auto& edge : result)
            cout << edge.source << " -- " << edge.destination << " == " << edge.weight << endl;
    }
};

int main() {
    int vertices = 4;
    int edges = 5;

    Graph graph(vertices, edges);

    graph.addEdge(0, 0, 1, 10);
    graph.addEdge(1, 0, 2, 6);
    graph.addEdge(2, 0, 3, 5);
    graph.addEdge(3, 1, 3, 15);
    graph.addEdge(4, 2, 3, 4);

    graph.kruskalMST();

    return 0;
}
