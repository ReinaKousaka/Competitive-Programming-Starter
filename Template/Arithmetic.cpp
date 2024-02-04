// (n ^ x) % m
long long fastpow(long long n, long long x, long long m) {
    long long ret = 1;
    while (x) {
        if (x & 1)
            (ret *= n) %= m;
        x >>= 1;
        (n *= n) %= m;
    }
    return ret;
}

// ceil(a / b), where a, b > 0
inline long long ceil_div(long long a, long long b) {
    return (a + b - 1) / b;
}

// floor(sqrt(a)), where a >= 0
long long int_sqrt(long long x) {
    long long res = 0;
    for (long long k = 1LL << 30; k != 0; k = k >> 1) {
        if ((res + k) * (res + k) <= x) {
            res += k;
        }
    }
    return res;
}

