#include <vector>


/**
 * Fenwick Tree template, reference: @jiangly: https://codeforces.com/profile/jiangly
 * .add(x, delta): 0-indexed
 * .sum(x): sum from x-th element to the end, with a dummy 0 at the beginning
 * .rangeSum(l, r): sum of interval [l, r]
 * */
template <class T>
class Fenwick {
public:
    int n;
    std::vector<T> a;
    
    Fenwick(int n = 0) {
        init(n);
    }
    
    void add(int x, const T& delta) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += delta;
        }
    }

    T sum(int x) {
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        return sum(r + 1) - sum(l);
    }
    
    int kth(T k) {
        int x = 0;
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
private:
    void init(int n) {
        this->n = n;
        a.assign(n, T());
    }
};


// For different operations:
// Fenwick<Max>
struct Max {
    int x = -1E9;
    Max &operator+=(Max a) {
        x = std::max(x, a.x);
        return *this;
    }
};
 