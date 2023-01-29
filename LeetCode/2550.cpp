// base ^ exponent % mod
template <typename T>
T fastpow(T base, int exponent, int mod){
	T res = 1;
	while (exponent) {
		if (exponent & 1) {
			res = (res * base) % mod;
		}
		base = (base * base) % mod;
		exponent >>= 1;
	}
	return res;
}


class Solution {
public:
    int monkeyMove(int n) {
        const int mod = 7 + 1e9;
        int res = fastpow<long long>(2, n, mod) - 2;
        return res < 0 ? res + mod : res;
    }
};