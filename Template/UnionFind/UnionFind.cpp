#include <vector>


// Union Find template w/ path compression and union by rank
struct UnionFind {
    std::vector<int> parent;
    std::vector<int> rank;
    std::vector<int> size;
    int n;
    
    UnionFind (int n): n(n), rank(n, 1), size(n, 1) {
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        while (x != parent[x]) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void connect(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (rank[x] <= rank[y]) {
            parent[x] = y;
            size[y] += size[x];
        } else {
            parent[y] = x;
            size[x] += size[y];
        }
        if (rank[x] == rank[y]) {
            rank[y]++;
        }
    }

    int get_size(int x) {
        return size[find(x)];
    }
};
