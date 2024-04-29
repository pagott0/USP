#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;


//Enzo Vasconcellos Pagotto - 13632844
//Guilherme Aureliano Xavier - 14575641

struct Arc {
    int start;
    int end;
    int weight;
    Arc(int src, int dest, int w) : start(src), end(dest), weight(w) {}
};

void insertArc(vector<vector<int>>& matrix, const Arc& arc) {
    matrix[arc.start][arc.end] = arc.weight;
}

void removeArc(vector<vector<int>>& matrix, const Arc& arc) {
    matrix[arc.start][arc.end] = 0;
    matrix[arc.end][arc.start] = 0;
}

void printArcs(const vector<vector<int>>& matrix, int vertex) {
    bool isFirstPrinted = true;
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[vertex][i] != numeric_limits<int>::max()) {
            if (!isFirstPrinted) {
                cout << ", ";
            } else {
                isFirstPrinted = false;
            }

            cout << i;
        }
    }
}

void printGraph(const vector<vector<int>>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        cout << "Vertex " << i << ", arcs: ";
        printArcs(matrix, i);
        cout << "\n";
    }
}

int getNumberOfArcs(const vector<vector<int>>& matrix, bool isBidirectional) {
    int count = 0;
    for (const auto& row : matrix) {
        count += std::count(row.begin(), row.end(), 1);
    }
    return isBidirectional ? count : count / 2;
}

void dfs(const vector<vector<int>>& matrix, int currentVertex, vector<bool>& visited) {
    visited[currentVertex] = true;
    cout << "visited " << currentVertex << "\n";

    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[currentVertex][i] && !visited[i]) {
            dfs(matrix, i, visited);
        }
    }
}

void bfs(const vector<vector<int>>& matrix, vector<bool>& visited) {
    queue<int> queue;
    queue.push(0);
    visited[0] = true;

    while (!queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();
        cout << "visited " << currentVertex << "\n";

        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[currentVertex][i] != numeric_limits<int>::max() && !visited[i]) {
                visited[i] = true;
                queue.push(i);
            }
        }
    }
}

vector<int> dijkstra(const vector<vector<int>>& matrix, int source, vector<int>& predecessor) {
    int size = matrix.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(size, numeric_limits<int>::max());
    predecessor.assign(size, -1);

    pq.push(make_pair(0, source));
    dist[source] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < size; ++v) {
            if (matrix[u][v] != numeric_limits<int>::max()) {
                int alt = dist[u] + matrix[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    predecessor[v] = u;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
    }

    return dist;
}

void printPath(int v, const vector<int>& predecessor) {
    if (predecessor[v] == -1) {
        cout << v;
        return;
    }

    printPath(predecessor[v], predecessor);
    cout << " -> " << v;
}

int main() {
    int verticesNum;
    cin >> verticesNum;

    vector<vector<int>> matrix(verticesNum, vector<int>(verticesNum, numeric_limits<int>::max()));
    for (int i = 0; i < verticesNum; ++i) {
        matrix[i][i] = 0;
    }

    int start, end, weight;
    while (cin >> start >> end >> weight) {
        Arc arc(start, end, weight);
        insertArc(matrix, arc);
    }

    for (int i = 0; i < verticesNum; ++i) {
        vector<int> predecessor;
        vector<int> distances = dijkstra(matrix, i, predecessor);

        cout << "Node " << i << ":\n";
        for (int j = 0; j < verticesNum; ++j) {
            cout << "Distance from " << i << " to " << j << " = ";
            if (distances[j] == numeric_limits<int>::max()) {
                cout << "infinity\n";
            } else {
                cout << distances[j] << "\n";

                if (distances[j] > 0) {
                    cout << "Path: ";
                    printPath(j, predecessor);
                    cout << "\n";
                }
            }
        }

        if (i < verticesNum - 1) {
            cout << "\n";
        }
    }

    return 0;
}
