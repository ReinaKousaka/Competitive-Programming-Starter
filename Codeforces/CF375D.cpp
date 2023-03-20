#include <bits/stdc++.h>
using namespace std;


/**
 * Mo's Algorithm Template (0-indexed)
 * Time: O((N + Q) * F * sqrt(N)), where F: complexity of add(), sub()
 * */
namespace mo {

struct Query {
	int l, r, idx, k;
};

// counter[color]: number of nodes of the color
// suffix[k]: number of colors that there are >= k vertices of such color
std::vector<int> colors, counter, suffix;

void Add(int u) {
	counter[colors[u]]++;
	suffix[counter[colors[u]]]++;
}

void Sub(int u) {
	suffix[counter[colors[u]]]--;
	counter[colors[u]]--;
}

long long get_answer(int k) {
	return suffix[k];
}

vector<int> seq, id, end_idx;
int timer = 0;
void dfs(int u, int parent, vector<vector<int>>& adj) {
	seq[timer] = u;
	id[u] = timer;
	timer++;
	for (auto v: adj[u]) {
		if (v == parent) continue;
		dfs(v, u, adj);
	}
	end_idx[u] = timer - 1;
}

std::vector<int> mo_s_algorithm() {
	int n, q;
	std::cin >> n >> q;
	std::vector<int> pos(n);

	const int MAX_COLOR = 1e5;
	colors.resize(n + 1);
	counter.resize(MAX_COLOR + 1, 0);
	suffix.resize(MAX_COLOR + 1, 0);

	// sqrt decomposition, read n entries
	int siz = std::sqrt(n);
	for (int i = 0; i < n; i++) {
		std::cin >> colors[i + 1];
		pos[i] = i / siz;
	}

	// read tree edges
	vector<vector<int>> adj(n + 1);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	seq.resize(n);
	id.resize(n + 1);
	end_idx.resize(n + 1);
	dfs(1, -1, adj);
	
	// read q queries
	std::vector<Query> queries(q);
	for (int i = 0; i < q; i++) {
		int v, k;
		std::cin >> v >> k;
		queries[i].l = id[v];
		queries[i].r = end_idx[v];
		queries[i].k = k;
		queries[i].idx = i;
	}

	std::sort(queries.begin(), queries.end(),
		[&pos](Query& x, Query& y)->bool {
			return pos[x.l] == pos[y.l] ? x.r < y.r : pos[x.l] < pos[y.l];
	});

	int l = 0, r = -1;   // always reflect the range [l, r]
	std::vector<int> res(q);

	for (auto query: queries) {
		while (query.l < l) Add(seq[--l]);
		while (query.r > r) Add(seq[++r]);
		while (query.l > l) Sub(seq[l++]);
		while (query.r < r) Sub(seq[r--]);

		// mark down answers
		res[query.idx] = get_answer(query.k);
	}
	return res;
}
};



int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	auto res = mo::mo_s_algorithm();
	for (auto x: res) cout << x << "\n";
	return 0;
}
