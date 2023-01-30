#include <iostream>
#include <vector>
using namespace std;

typedef long long int ll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tt;
    cin >> tt;

    const int N = 20;

    while (tt--) {
        int n;
        cin >> n;
        
        vector<int> nums(n);
        vector<int> a(1 << N, 0);
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
            a[nums[i]]++;
        }

        // cite from: https://codeforces.com/blog/entry/45223
        for (int i = 0; i < N; i++) {
            for (int mask = 0; mask < (1 << N); mask++) {
                if (mask & (1 << i)) {
                    a[mask] += a[mask ^ (1 << i)];
                }
            }
        }

        ll res = 0;
        for (auto& x: nums) {
            res += a[x];
        }
        cout << res << endl;
    }
    return 0;
}