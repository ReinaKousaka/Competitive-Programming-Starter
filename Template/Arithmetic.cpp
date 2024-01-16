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
