#include <vector>
#include <algorithm>


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
