#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// Union Find template w/ path compression and union by rank
class UF {
 public:
    vector<int> parent;
    vector<int> rank;
    vector<int> size;
    int n;
    UF (int n):n(n) {
        for (int i = 0; i < n; i++) {
            parent.push_back(i);
            rank.push_back(1);
            size.push_back(1);
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

    int getSize(int x) {
        return size[find(x)];
    }
};

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        const vector<int> DIRECTION = {0, 1, 0, -1, 0};
        int n = grid.size();
        UF dsu(n * n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j]) {
                    for (int k = 0; k < 2; k++) {       // actually only 2 directions are enough
                        int x = i + DIRECTION[k];
                        int y = j + DIRECTION[k + 1];
                        if (x < 0 || y < 0 || x >= n || y >= n) continue;
                        if (grid[x][y]) {
                            dsu.connect(trans(x, y, n), trans(i, j, n));
                        }
                    }
                }
            }
        }

        int res = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!grid[i][j]) {
                    set<int> s;
                    int size = 1;
                    for (int k = 0; k < 4; k++) {
                        int x = i + DIRECTION[k];
                        int y = j + DIRECTION[k + 1];
                        if (x < 0 || y < 0 || x >= n || y >= n) continue;
                        if (grid[x][y]) {
                            s.insert(dsu.find(trans(x, y, n)));
                        }
                    }
                    for (auto& x: s) {
                        size += dsu.getSize(x);
                    }
                    res = max(res, size);
                }
            }
        }
        return (res == -1) ? n * n : res;
    }

    inline int trans(int x, int y, int n) {
        return x * n + y;
    }
};
