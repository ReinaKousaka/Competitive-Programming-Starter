#include <bits/stdc++.h>
using namespace std;


/**
 * LazySegmentTree supporting set/reset bit
 */
template <typename T>
struct LazySegmentTree {
	struct Node {
		int start, end;
		T lazy, val;
	};

	std::vector<Node> t;
	int size;

	LazySegmentTree(int size): size(size) {
		t.resize(size * 4);
		_build(1, 0, size - 1);
	}

	LazySegmentTree(const std::vector<T>& data): size(data.size()) {
		t.resize(size * 4);
		_build(1, 0, size - 1, data);
	}

	void _build(int i, int start, int end, const std::vector<T>& data = std::vector<int>()) {
		t[i].start = start;
		t[i].end = end;
		if (start == end) {
			if (data.size()) t[i].val = data[start];
		} else {
			int mid = (start + end) >> 1;
			_build(i << 1, start, mid, data);
			_build(i << 1 | 1, mid + 1, end, data);
			if (data.size())
				_push_up(i);
		}
	}

	void _push_up(int i) {
		t[i].val = t[i << 1].val | t[i << 1 | 1].val;
	}

	void _push_down(int i) {
		if (t[i].lazy) {
			t[i << 1].val = t[i].lazy;
			t[i << 1 | 1].val = t[i].lazy;
			t[i << 1].lazy = t[i].lazy;
			t[i << 1 | 1].lazy = t[i].lazy;
			t[i].lazy = 0;
		}
	}

	// change color with bitwise operations to range [l, r]
	void set_color(int l, int r, T new_color, int i = 1) {
		if (l <= t[i].start && r >= t[i].end) {
			t[i].val = 1LL << new_color;
			t[i].lazy = 1LL << new_color;
			return;
		}
		_push_down(i);
		int mid = (t[i].start + t[i].end) >> 1;
		if (l <= mid) set_color(l, r, new_color, i << 1);
		if (r > mid) set_color(l, r, new_color, i << 1 | 1);
		_push_up(i);
	}

	T query(int l, int r, int i = 1) {
		if (l <= t[i].start && r >= t[i].end)
			return t[i].val;
		_push_down(i);
		int mid = (t[i].start + t[i].end) >> 1;
		T res = 0;
		if (l <= mid) res |= query(l, r, i << 1);
		if (r > mid) res |= query(l, r, i << 1 | 1);
		return res;
	}
};


/**
 * Heavy-light decomposition template
 * reference: @jiangly https://codeforces.com/profile/jiangly
 * top[x] := the top node of the heavy chain where x is in
 * adj[x][0] := the heavy son of x
 * in[x] := the index of x in the dfs sequence
 * seq: the dfs sequence
 */
class HLD {
public:
    int n;
    std::vector<int> siz, top, dep, parent, in, out, seq;
    std::vector<std::vector<int>> adj;
    HLD(int n): n(n), siz(n), top(n), dep(n), parent(n, -1), in(n), out(n), seq(n), adj(n) {}
    
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init(int root = 0) {
        top[root] = root;
        dfs1(root);
        dfs2(root);
    }

    void dfs1(int u) {
        if (parent[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
        }
        siz[u] = 1;
        for (int& v: adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }

    int cur = 0;
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (int v: adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;   
    }

    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
};



/**
 * HLD helper functions
 * Assume use a segmentree with the help of a mapping
 * for (int i = 0; i < n; i++) 
        mapped_arr[hld.in[i]] = arr[i];
    LazySegmentTree<T> seg(mapped_arr);
 */
// return the sum of the subtree rooted at x
template <typename T>
long long subtree_sum(const HLD& hld, LazySegmentTree<T>& seg, int x) {
    return seg.query(hld.in[x], hld.in[x] + hld.siz[x] - 1);
}

// set color to the subtree rooted at x
template <typename T>
void subtree_set(const HLD& hld, LazySegmentTree<T>& seg, int x, int color) {
    seg.set_color(hld.in[x], hld.in[x] + hld.siz[x] - 1, color);
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	
	// colors in [1, 60] --> represented as long long type bitmask
	vector<long long> colors(n), mapped_colors(n);
	for (int i = 0; i < n; i++) {
		int c;
		cin >> c;
		colors[i] = (1LL << (c - 1));	// important to avoid shift too long error
	}

	HLD hld(n);
	for (int i = 0; i < n - 1; i++) {
		int x, y;
		cin >> x >> y;
		x--; y--;
		hld.add_edge(x, y);
	}
	hld.init(0);
	for (int i = 0; i < n; i++)
		mapped_colors[hld.in[i]] = colors[i];
	LazySegmentTree<long long> seg(mapped_colors);

	while (m--) {
		int op, v;
		cin >> op >> v;
		v--;
		if (op == 1) {
			long long c;
			cin >> c;
			subtree_set(hld, seg, v, c - 1);
		} else {
			long long xor_sum = subtree_sum(hld, seg, v);
			// https://codeforces.com/blog/entry/13134
			cout << __builtin_popcountll(xor_sum) << "\n";
		}
	}
	return 0;
}
