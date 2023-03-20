#include <vector>
#include <cmath>


/**
 * LCA - Binary Lifting template
 * up[i][j] := the (2^j)-th ancestor above node i. Where 0 <= j <= ceil(lg(N))
 * in, out := Euler tour order
 * .is_ancestor(u, v): true if u is ancestor of v
 * .lca(u, v)
 * */
struct LCA {
	int n, MAX_LOG;
	std::vector<std::vector<int>> adj, up;
	std::vector<int> in, out;

	LCA(int n): n(n), MAX_LOG(ceil(log2(n))), adj(n), in(n), out(n), up(n, vector<int>(MAX_LOG + 1)) {}

	void add_edge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void init(int root = 0) {
		dfs(root, root);
	}

	int timer = 0;
	void dfs(int u, int parent) {
		in[u] = timer++;
		up[u][0] = parent;
		for (int i = 1; i <= MAX_LOG; i++) {
			up[u][i] = up[up[u][i - 1]][i - 1];
		}

		for (int v: adj[u]) {
			if (v == parent) continue;
			dfs(v, u);
		}
		out[u] = timer++;
	}

	bool is_ancestor(int u, int v) {
		return in[u] <= in[v] && out[u] >= out[v];
	}

	int lca(int u, int v) {
		if (is_ancestor(u, v)) return u;
		if (is_ancestor(v, u)) return v;
		for (int i = MAX_LOG; i >= 0; i--) {
			if (!is_ancestor(up[u][i], v))
				u = up[u][i];
		}
		return up[u][0];
	}
};
