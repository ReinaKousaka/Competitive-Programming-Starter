#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


// Heavy-light decomposition template
// reference: @jiangly https://codeforces.com/profile/jiangly
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


int main()  {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, x, y;
    cin >> n >> m >> s;

    HLD hld(n);

    for (int i = 0; i < n - 1; i++) {
        cin >> x >> y;
        x--; y--;
        hld.add_edge(x, y);
    }
    hld.init(s - 1);

    while (m--) {
        cin >> x >> y;
        x--; y--;
        cout << hld.lca(x, y) + 1 << "\n";
    }
    return 0;
}
