// https://codeforces.com/problemset/problem/295/B
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> dist(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }
    vector<int> order(n);
    for (int i = 0; i < n; i++) {
        cin >> order[i];
        order[i]--;
    }
    
    //  Floyd-Warshall
    vector<ll> res(n, 0);
    for (int k = n - 1; k >= 0; k--) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(
                    dist[i][j],
                    dist[i][order[k]] + dist[order[k]][j]
                );
            }
        }
        // sum
        for (int i = k; i < n; i++) {
            for (int j = k; j < n; j++) {
                res[k] += dist[order[i]][order[j]];
            }
        }
    }
    for (auto val: res) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
