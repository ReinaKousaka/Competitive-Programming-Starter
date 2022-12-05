#include <iostream>
#include <vector>
using namespace std;

// check if the graph is bipartite by coloring with dfs
bool dfs(int vertex, 
    const vector<vector<int>>& adjacent, 
    vector<int>& colors,
    int color=1
) {
    colors[vertex] = color;
    for (auto& w: adjacent[vertex]) {
        if (!colors[w]) {
            // if first time encounter w
            if (!dfs(w, adjacent, colors, -color)) {
                return false;
            }
        } else {
            if (colors[vertex] == colors[w]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adjacent(n, vector<int>());
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adjacent[a - 1].push_back(b - 1);
        adjacent[b - 1].push_back(a - 1);
        edges.push_back({a - 1, b - 1});
    }

    vector<int> colors(n, 0);
    if (dfs(0, adjacent, colors)) {
        cout << "YES" << endl;
        for (auto& [a, b]: edges) {
            cout << (colors[a] == 1);
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
