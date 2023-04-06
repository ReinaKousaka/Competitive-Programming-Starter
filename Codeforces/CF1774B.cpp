#include <bits/stdc++.h>
using namespace std;


void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    int siz = (n + k - 1) / k;
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }

    std::sort(a.begin(), a.end(), greater<int>());

    int sum = 0;
    for (int i = 1; i <= m; i++) {
        sum += a[i - 1];
        // the RHS is the max number cells that i colors can accommodate
        if (sum > 1LL * (n / k) * i + std::min(n % k, i)) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}