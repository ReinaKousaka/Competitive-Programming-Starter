// https://codeforces.com/problemset/gymProblem/102759/J
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <utility>
#include <functional>
using namespace std;

// overload +, - for pair<>
template <typename T, typename U>                                                   
std::pair<T, U> operator+(const std::pair<T, U>& l, const std::pair<T, U>& r) {   
    return {l.first + r.first, l.second + r.second};                                    
}
template <typename T, typename U>                                                   
std::pair<T, U> operator-(const std::pair<T, U>& l, const std::pair<T, U>& r) {   
    return {l.first - r.first, l.second - r.second};                                    
}

// define hash func to use pair as a key
// see https://youngforest.github.io/2020/05/27/best-implement-to-use-pair-as-key-to-std-unordered-map-in-C/
template <typename T>
inline void hash_combine(std::size_t &seed, const T &val) {
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
// auxiliary generic functions to create a hash value using a seed
template <typename T> inline void hash_val(std::size_t &seed, const T &val) {
    hash_combine(seed, val);
}
template <typename T, typename... Types>
inline void hash_val(std::size_t &seed, const T &val, const Types &... args) {
    hash_combine(seed, val);
    hash_val(seed, args...);
}

template <typename... Types>
inline std::size_t hash_val(const Types &... args) {
    std::size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const {
        return hash_val(p.first, p.second);
    }
};
    
// main
int main() {
    // input
    int n, q;
    cin >> n;
    string command;
    cin >> command;
    cin >> q;
    vector<pair<int, int>> coordinate;
    unordered_map<pair<int, int>, list<int>, pair_hash> m;    // cars' coordinate (x, y) --> indices
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        coordinate.push_back({x, y});
        m[make_pair(x, y)].emplace_back(i);
    }
    
    // move location of cars whenever encounters the wall
    unordered_map<char, pair<int, int>> action = {
        {'R', {1, 0}}, {'L', {-1, 0}}, {'U', {0, 1}}, {'D', {0, -1}}
    };
    pair<int, int> wall = {0, 0};
    pair<int, int> abs_val = {0, 0};
    for (auto& ch: command) {
        wall = wall - action[ch];       // wall moves in reverse direction
        if (m.find(wall) != m.end()) {
            m[wall - action[ch]].splice(m[wall - action[ch]].end(), m[wall]);       // O(1) due to list
            m.erase(wall);
        }
        abs_val = abs_val + action[ch];
    }
    
    // output
    for (const auto& [key, val]: m) {
        for (auto& i: val) {
            coordinate[i] = key;
        }
    }
    for (int i = 0; i < q; i++) {
        cout << coordinate[i].first + abs_val.first << " " << coordinate[i].second + abs_val.second << endl;
    }
    return 0;
}