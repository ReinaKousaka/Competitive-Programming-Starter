#include <bits/stdc++.h>
using namespace std;


// fill the distance array, return one of the farest vertice reachable from u
int bfs(int u, vector<int>& dist, const vector<vector<int>>& adj) {
	std::queue<int> q;
	q.push(u);
	std::fill(dist.begin(), dist.end(), -1);
	dist[u] = 0;
	int max_node = -1;
	
	while (q.size()) {
		int u = q.front();
		q.pop();
		for (int v: adj[u]) {
			if (dist[v] < 0) {
				q.push(v);
				dist[v] = dist[u] + 1;
			}
		}
		max_node = u;
	}
	return max_node;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	vector<vector<int>> adj(n);
	for (int i = 0; i < n - 1; i++) {
		int x, y;
		cin >> x >> y;
		x--, y--;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	vector<int> dx(n), dy(n);
	// get x
	int x = bfs(0, dx, adj);
	// mark down dx, get y
	int y = bfs(x, dx, adj);
	// mark down dy
	bfs(y, dy, adj);

	vector<int> diff(n + 1, 0);		// difference array
	for (int i = 0; i < n; i++) {
		// property of tree diameter
		int d = std::max(dx[i], dy[i]);

		// max(dist[u, x], dist[u, y]) < k --> u is an isolated point
		diff[d + 1]++;	
	}
	int res = diff[0] = 1;		// 1 connected componenet + some ioslated points
	diff[dx[y] + 1]--;	// k > diameter, deduct the initial connected component

	for (int k = 1; k <= n; k++) {
		res += diff[k];
		cout << res << " ";
	}
	cout << "\n";
	return 0;
}
