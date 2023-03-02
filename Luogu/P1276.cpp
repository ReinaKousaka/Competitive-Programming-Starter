#include <iostream>
#include <bitset>
using namespace std;

int main() {
    int l, n;
    cin >> l >> n;

    int res1 = 0, res2 = 0;
    std::bitset<10001> is_tree, is_planted;
    is_tree.set();
    is_planted.reset();
    while (n--) {
        int x, y, z;
        cin >> x >> y >> z;
        for (int i = y; i <= z; i++) {
            if (x) {
                if (!is_tree[i]) {
                    is_tree.set(i);
                    is_planted.set(i);
                }
            } else {
                is_tree.reset(i);
                if (is_planted[i]) {
                    res2++;
                }
                is_planted.reset(i);
            }
        }
    }

    for (int i = 0; i <= l; i++) {
        res1 += is_planted[i];
    }
    cout << res1 << "\n" << res2 << "\n";
    return 0;
}
