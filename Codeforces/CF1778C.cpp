#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    std::string a, b;
    cin >> a >> b;

    std::vector<int> letters(26, -1);
    int num_letters = 0;
    for (auto ch: a) {
        if (letters[ch - 'a'] == -1) {
            letters[ch - 'a'] = num_letters;
            num_letters++;
        }
    }

    k = std::min(k, num_letters);
    long long res = 0;
    for (int mask = 0; mask < (1 << num_letters); mask++) {
        if (__builtin_popcount(mask) != k) continue;
        int prev = -1;
        long long s = 0;
        for (int i = 0; i <= n; i++) {
            if (i == n || 
            (a[i] != b[i] && (mask & (1 << letters[a[i] - 'a'])) == 0)) {
                s += 1LL * (i - prev) * (i - prev - 1) / 2;
                prev = i;
            }
        }
        res = max(res, s);
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    };
    return 0;
}
