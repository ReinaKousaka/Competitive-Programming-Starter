// https://codeforces.com/problemset/gymProblem/102511/A
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    vector<vector<int>> b(n, vector<int>(3)), f(n, vector<int>(3));
    for (int i = 0; i < n; i++) { cin >> b[i][0]; }
    for (int i = 0; i < n; i++) { 
        cin >> b[i][1];
        b[i][2] = i + 1;
    }
    for (int i = 0; i < n; i++) { cin >> f[i][0]; }
    for (int i = 0; i < n; i++) { 
        cin >> f[i][1];
        f[i][2] = i + 1;
    }

    // sort based on value
    sort(f.begin(), f.end());
    sort(b.begin(), b.end());

    // height --> index
    std::multimap<int, int> bs, fs;
    vector<int> res_b, res_f;
    int i = 0, j = 0;
    while (i < n || j < n) {
        if (!bs.size()) {
            bs.insert({b[i][1], b[i][2]});
            int p = b[i][0];
            i++;
            while (i < n && b[i][0] == p) {
                bs.insert({b[i][1], b[i][2]});
                i++;
            }
        }
        if (!fs.size()) {
            fs.insert({f[j][1], f[j][2]});
            int p = f[j][0];
            j++;
            while (j < n && f[j][0] == p) {
                fs.insert({f[j][1], f[j][2]});
                j++;
            }
        }

        if (bs.size() <= fs.size()) {
            int m = bs.size();
            for (auto& [key, val]: bs) {
                auto it = fs.lower_bound(key);
                if (it == fs.begin()) {
                    cout << "impossible" << endl;
                    return 0;
                }
                it--;
                res_b.push_back(val);
                res_f.push_back(it->second);
                fs.erase(it);
            }
            bs.clear();
        } else {
            int m = fs.size();
            for (auto& [key, val]: fs) {
                auto it = bs.upper_bound(key);
                if (it == bs.end()) {
                    cout << "impossible" << endl;
                    return 0;
                }
                res_f.push_back(val);
                res_b.push_back(it->second);
                bs.erase(it);
            }
            fs.clear();
        }
    }

    for (int i = 0; i < n; i++) {
        cout << res_b[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << res_f[i] << " ";
    }
    cout << endl;
    return 0;
}
