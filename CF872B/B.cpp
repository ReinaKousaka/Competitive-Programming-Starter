#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int max_n = 1e5;
// Sparse Table 
class ST {
public:
    int f[max_n][25];
    ST (vector<int>& arr) {
        // pre-computation
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            f[i][0] = arr[i];
        }
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; (i + (1 << j) - 1) < n; i++) {
                f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r) {
        const int j = (int)
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) { 
        cin >> arr[i];
    }
    if (k > 2) {
        cout << *max_element(arr.begin(), arr.end());
    } else if (k == 1) {
        cout << *min_element(arr.begin(), arr.end());
    } else {

    }
}