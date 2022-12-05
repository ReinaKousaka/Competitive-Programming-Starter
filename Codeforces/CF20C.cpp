// https://codeforces.com/problemset/problem/20/C
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <utility>
using namespace std;

typedef long long ll;
int main() {
    // input
    int n, m;
    cin >> n >> m;
    vector<list<pair<int, int>>> graph(n + 1);      // pairs: {weight, neighbor}
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a].push_back({w, b});
        graph[b].push_back({w, a});
    }
    // Dijkstra setup
    vector<int> prev(n + 1, -1);        // previous node, 1-indexed
    vector<ll> dist(n + 1, 1e18);
    vector<bool> visited(n + 1, false);     // otherwise will get MLE
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> min_heap;
    dist[1] = 0;
    min_heap.push({0, 1});      // {dist, vertex index}
    // Dijkstra without decrease-key, C++ priority_queue does not support it

    while (!min_heap.empty()) {
        auto [d, u] = min_heap.top();
        min_heap.pop();
        // if (d > dist[u]) { continue; }
        if (visited[u]) { continue; }
        visited[u] = true;
        for (auto& [w, v]: graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                min_heap.push({dist[v], v});
            }
        }
    }

    // output
    if (dist[n] == 1e18) {
        cout << -1 << endl;
    } else {
        vector<int> reverse_path;
        int i = n;
        while (i != -1) {
            reverse_path.push_back(i);
            i = prev[i];
        }
        for (int i = reverse_path.size() - 1; i >= 0; i--) {
            cout << reverse_path[i] << " ";
        }
        cout << endl;
    }
    return 0;
}