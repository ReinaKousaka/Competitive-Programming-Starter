#include <vector>
#include <iostream>
using namespace std;


/**
 * reference: @jiangly: https://codeforces.com/profile/jiangly
 * primes: list of prime numbers starting from 2
 * minp[i]: the min prime factor of i, where i >= 2
 */
std::vector<int> minp, primes;

void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        
        for (int p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    
    sieve(n);

    while (q--) {
        int x;
        cin >> x;
        cout << primes[x - 1] << "\n";
    }
    return 0;
}
