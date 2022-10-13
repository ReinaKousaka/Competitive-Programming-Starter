#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        int m = rooms.size(), n = rooms[0].size();
        const int inf = 2147483647;
        queue<pair<int, int>> q;
        // BFS, starting from all gates
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!rooms[i][j]) {
                    q.push({i, j});
                }
            }
        }

        int dist = 0;
        while (!q.empty()) {
            int num_elements = q.size();
            for (int t = 0; t < num_elements; t++) {
                auto [i, j] = q.front();
                q.pop();
                if (rooms[i][j] == inf) {
                    // first arrival
                    rooms[i][j] = dist;
                }
                if (i > 0 && rooms[i - 1][j] == inf) {
                    q.push({i - 1, j});
                }
                if (j > 0 && rooms[i][j - 1] == inf) {
                    q.push({i, j - 1});
                }
                if (i < m - 1 && rooms[i + 1][j] == inf) {
                    q.push({i + 1, j});
                }
                if (j < n - 1 && rooms[i][j + 1] == inf) {
                    q.push({i, j + 1});
                }
            }
            dist++;
        }
    }
};