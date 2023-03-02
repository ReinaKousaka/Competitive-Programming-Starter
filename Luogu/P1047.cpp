#include <bits/stdc++.h>
using namespace std;


/**
 * cite from: https://codeforces.com/blog/entry/20528
 * Lazy Segment Tree template which supports operations:
 * 1. Add amount V to the values in range [L, R]
 * 2. Reset the values in range [L, R] to value V.
 * 3. Query for the sum of the values in range [L, R].
 * 
 * T: for vertex values, looks like struct node 
 *    should have an operator + specifying how to combine vertices
 * U: for update operations, looks like struct update
 *    should have an operator () specifying how to apply updates to vertices
 *    and an operator + for combining two updates.
 * 
 * T zero is the zero node, U noop is the zero update
 * default constructor is: LazySegmentTree<node, update> st(N, {0, 0}, {false, 0});
 */
struct node {
    int sum, width;
    
    node operator+(const node &n) {
        return { sum + n.sum, width + n.width };
    }    
};

struct update {
    bool type; // 0 for add, 1 for reset
    int value;

    node operator()(const node &n) {
        if (type) return { n.width * value, n.width };
        else return { n.sum + n.width * value, n.width };
    }

    update operator+(const update &u) {
        if (u.type) return u;
        return { type, value + u.value };
    }
};

template<typename T, typename U> 
struct LazySegmentTree {
    int S, H;
 
    T zero;
    vector<T> value;
 
    U noop;
    vector<bool> dirty;
    vector<U> prop;
 
    LazySegmentTree<T, U>(int _S, T _zero = T(), U _noop = U()) {
        zero = _zero, noop = _noop;
        for (S = 1, H = 1; S < _S; ) S *= 2, H++;
 
        value.resize(2*S, zero);
        dirty.resize(2*S, false);
        prop.resize(2*S, noop);
    }
 
    void set_leaves(vector<T> &leaves) {
        copy(leaves.begin(), leaves.end(), value.begin() + S);
 
        for (int i = S - 1; i > 0; i--)
            value[i] = value[2 * i] + value[2 * i + 1];
    }
 
    void apply(int i, U &update) {
        value[i] = update(value[i]);
        if(i < S) {
            prop[i] = prop[i] + update;
            dirty[i] = true;
        }
    }
 
    void rebuild(int i) {
        for (int l = i/2; l; l /= 2) {
            T combined = value[2*l] + value[2*l+1];
            value[l] = prop[l](combined);
        }
    }
 
    void propagate(int i) {
        for (int h = H; h > 0; h--) {
            int l = i >> h;
 
            if (dirty[l]) {
                apply(2*l, prop[l]);
                apply(2*l+1, prop[l]);
 
                prop[l] = noop;
                dirty[l] = false;
            }
        }
    }
 
    void upd(int i, int j, U update) {
        i += S, j += S;
        propagate(i), propagate(j);
 
        for (int l = i, r = j; l <= r; l /= 2, r /= 2) {
            if((l&1) == 1) apply(l++, update);
            if((r&1) == 0) apply(r--, update);
        }
 
        rebuild(i), rebuild(j);
    }
 
    T query(int i, int j){
        i += S, j += S;
        propagate(i), propagate(j);
 
        T res_left = zero, res_right = zero;
        for(; i <= j; i /= 2, j /= 2){
            if((i&1) == 1) res_left = res_left + value[i++];
            if((j&1) == 0) res_right = value[j--] + res_right;
        }
        return res_left + res_right;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int l, m;
    cin >> l >> m;

    LazySegmentTree<node, update> seg(l);
    vector<node> leaves(l + 1, node {1, 0});
    seg.set_leaves(leaves);

    while (m--) {
        int x, y;
        cin >> x >> y;
        seg.upd(x, y, update {1, 0});
    }
    cout << seg.query(0, l).sum << "\n";
    return 0;
}
