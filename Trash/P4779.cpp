#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;


struct edge {
	int to;
	int w;
};


/**
 * Dijkstra's algorithm template
 * */
std::vector<int> Dijkstra(const std::vector<std::vector<edge>>& adj, int src) {
	typedef std::pair<int, int> pii;		// {dist, vertex}
	const int INFTY = 1 << 30;
	
	int n = adj.size();	// assume 0-indexed
	std::vector<bool> visited(n, 0);
	std::vector<int> prev(n, -1), dist(n, INFTY);
	std::priority_queue<pii, std::vector<pii>, std::greater<pii>> min_heap;
	min_heap.push({0, src});
	dist[src] = 0;
	
	while (min_heap.size()) {
		auto [d, u] = min_heap.top();
		min_heap.pop();
		if (visited[u]) continue;
		visited[u] = true;
		for (auto& e: adj[u]) {
			auto w = e.w, v = e.to;
			if (d + w < dist[v]) {
				dist[v] = d + w;
				prev[v] = u;
				min_heap.push({dist[v], v});
			}
		}
	}
	return dist;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m, s;
	cin >> n >> m >> s;
	vector<vector<edge>> adj(n);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u - 1].push_back(edge {v - 1, w});
	}
	auto res = Dijkstra(adj, s - 1);
	for (auto x: res) {
		cout << x << " ";
	}
	cout << "\n";
	return 0;
}
