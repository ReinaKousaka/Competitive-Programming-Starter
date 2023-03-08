#include <bits/stdc++.h>
using namespace std;

long long MOD;

// 0-indexed LazySegmentTree supporting +
template <typename T>
struct LazySegmentTree {
    struct Node {
        int start, end;
        T lazy, val;
    };

    std::vector<Node> tree;
    int size;

    LazySegmentTree(int size): size(size) {
        tree.resize(size * 4 + 1);
        build(0, 0, size - 1);
    }

    LazySegmentTree(const std::vector<int>& data): size(data.size()) {
        tree.resize(size * 4 + 1);
        build(0, 0, size - 1, data);
    }

    void build(int i, int start, int end, const std::vector<int>& data = std::vector<int>()) {
        tree[i].start = start;
        tree[i].end = end;
        if (start == end) {
            if (data.size()) tree[i].val = data[start];
        } else {
            int mid = (start + end) >> 1;
            build(i * 2 + 1, start, mid, data);
            build(i * 2 + 2, mid + 1, end, data);
            if (data.size())
                tree[i].val = (tree[i * 2 + 1].val + tree[i * 2 + 2].val) % MOD;
        }
    }

    void _push_down(int i) {
        if (tree[i].lazy) {
            // can adjust operator
            tree[i * 2 + 1].val = (tree[i * 2 + 1].val + tree[i].lazy * (tree[i * 2 + 1].end - tree[i * 2 + 1].start + 1)) % MOD;
            tree[i * 2 + 2].val = (tree[i * 2 + 2].val + tree[i].lazy * (tree[i * 2 + 2].end - tree[i * 2 + 2].start + 1)) % MOD;
            tree[i * 2 + 1].lazy = (tree[i * 2 + 1].lazy + tree[i].lazy) % MOD;
            tree[i * 2 + 2].lazy = (tree[i * 2 + 2].lazy + tree[i].lazy) % MOD;
            tree[i].lazy = 0;
        }
    }

    // add delta to range [l, r]
    void update(int l, int r, T delta, int i = 0) {
        // if current node is covered
        if (l <= tree[i].start && r >= tree[i].end) {
            tree[i].val = (tree[i].val + delta * (tree[i].end - tree[i].start + 1)) % MOD;
            tree[i].lazy = (tree[i].lazy + delta) % MOD;
            return;
        }
        _push_down(i);
        int mid = (tree[i].start + tree[i].end) >> 1;
        if (l <= mid) update(l, r, delta, i * 2 + 1);
        if (r > mid) update(l, r, delta, i * 2 + 2);
        tree[i].val = (tree[i * 2 + 1].val + tree[i * 2 + 2].val) % MOD;
    }

    T query(int l, int r, int i = 0) {
        if (l <= tree[i].start && r >= tree[i].end)
            return tree[i].val;
        _push_down(i);
        int mid = (tree[i].start + tree[i].end) >> 1;
        T res = 0;
        if (l <= mid) res = (res + query(l, r, i * 2 + 1)) % MOD;
        if (r > mid) res = (res + query(l, r, i * 2 + 2)) % MOD;
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


// HLD helper functions

// return the sum on the path between x, y
template <typename T>
long long path_sum(const HLD& hld, LazySegmentTree<T>& seg, int x, int y) {
    long long res = 0;
    while (hld.top[x] != hld.top[y]) {
        if (hld.dep[hld.top[x]] < hld.dep[hld.top[y]]) std::swap(x, y);
        res = (res + seg.query(hld.in[hld.top[x]], hld.in[x])) % MOD;
        x = hld.parent[hld.top[x]];
    }
    if (hld.dep[x] > hld.dep[y]) std::swap(x, y);
    res = (res + seg.query(hld.in[x], hld.in[y])) % MOD;
    return res;
}

// add delta on the path between x, y
template <typename T>
void path_add(const HLD& hld, LazySegmentTree<T>& seg, int x, int y, int delta) {
    while (hld.top[x] != hld.top[y]) {
        if (hld.dep[hld.top[x]] < hld.dep[hld.top[y]]) std::swap(x, y);
        seg.update(hld.in[hld.top[x]], hld.in[x], delta);
        x = hld.parent[hld.top[x]];
    }
    if (hld.dep[x] > hld.dep[y]) std::swap(x, y);
    seg.update(hld.in[x], hld.in[y], delta);
}

// return the sum of the subtree rooted at x
template <typename T>
long long subtree_sum(const HLD& hld, LazySegmentTree<T>& seg, int x) {
    return seg.query(hld.in[x], hld.in[x] + hld.siz[x] - 1);
}

// add delta to the subtree rooted at x
template <typename T>
void subtree_add(const HLD& hld, LazySegmentTree<T>& seg, int x, int delta) {
    seg.update(hld.in[x], hld.in[x] + hld.siz[x] - 1, delta);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, r;
    cin >> n >> m >> r >> MOD;
    vector<int> arr(n), mapped_arr(n);  
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    HLD hld(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        hld.add_edge(u - 1, v - 1);
    }
    hld.init(r - 1);

    for (int i = 0; i < n; i++) {
        // mapped_arr[i] = arr[hld.seq[i]];   also works
        mapped_arr[hld.in[i]] = arr[i];
    }
    
    LazySegmentTree<long long> seg(mapped_arr);

    while (m--) {
        int op, x, y, z;
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> z;
            x--; y--;
            path_add(hld, seg, x, y, z);
        } else if (op == 2) {
            cin >> x >> y;
            x--; y--;
            cout << path_sum(hld, seg, x, y) << "\n";
        } else if (op == 3) {
            cin >> x >> z;
            subtree_add(hld, seg, x - 1, z);
        } else {
            cin >> x;
            cout << subtree_sum(hld, seg, x - 1) << "\n";
        }
    }
    return 0;
}
