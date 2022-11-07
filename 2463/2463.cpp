#include <vector>
#include <queue>
#include <limits>
using namespace std;

typedef long long ll;

// Hungarian algorithm template that MINIMIZES the cost
// take negative to get MAX
// cite from: http://e-maxx.ru/algo/assignment_hungary
template <typename T>
class Hungarian {
public:
    int n, m;
    vector<vector<T>> a;        // (n + 1) by (m + 1), 1-indexed, the cost matrix with fake-0
    vector<T> u, v, p, way;
    const T INF = std::numeric_limits<T>::max();
    vector<int> match;      // result match
    T result;       // result value

    Hungarian(vector<vector<T>>& cost) {
        n = cost.size(); m = cost[0].size();
        a = vector<vector<T>>(n + 1, vector<T>(m + 1, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                a[i][j] = cost[i - 1][j - 1];
            }
        }

        u = vector<T>(n + 1);
        v = vector<T>(m + 1);
        p = vector<T>(m + 1);
        way = vector<T>(m + 1);
        match = vector<int>(n + 1);
    }

    void solve() {
        for (int i = 1; i <= n; i++) {
            p[0] = i;
            int j0 = 0;
            vector<T> minv (m+1, INF);
            vector<char> used (m+1, false);
            do {
                used[j0] = true;
                T i0 = p[j0],  delta = INF,  j1;
                for (int j = 1; j <= m; j++)
                    if (!used[j]) {
                        int cur = a[i0][j]-u[i0]-v[j];
                        if (cur < minv[j])
                            minv[j] = cur,  way[j] = j0;
                        if (minv[j] < delta)
                            delta = minv[j],  j1 = j;
                    }
                for (int j = 0; j <= m; j++)
                    if (used[j])
                        u[p[j]] += delta,  v[j] -= delta;
                    else
                        minv[j] -= delta;
                j0 = j1;
            } while (p[j0] != 0);
            do {
                T j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }

        for (int j = 1; j <= m; j++)
            match[p[j]] = j;
        result = -v[0];
    }
};

class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        vector<int> factories;
        for (auto& vec: factory) {
            for (int i = 0; i < vec[1]; i++) {
                factories.push_back(vec[0]);
            } 
        }
        int n = robot.size(), m = factories.size();
        vector<vector<ll>> cost(n, vector<ll>(m, 0));
        for (int i = 0; i < robot.size(); i++) {
            for (int j = 0; j < factories.size(); j++) {
                cost[i][j] = abs(robot[i] - factories[j]);
            }
        }

        Hungarian km(cost);
        km.solve();
        return km.result;
    }
};