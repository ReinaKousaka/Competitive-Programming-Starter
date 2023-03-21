#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
using namespace std;

/**
 * Mo's Algorithm Template (0-indexed)
 * Time: O((N + Q) * F * sqrt(N)), where F: complexity of add(), sub()
 * */
namespace mo {

struct Query {
	int l, r, idx;
};

std::vector<int> prefix;
unordered_map<int, int> counter;

long long ans = 0;
int k;

void Add(int i) {
	auto target = k ^ prefix[i];
	ans += counter[target];
	counter[prefix[i]]++;
}

void Sub(int i) {
	counter[prefix[i]]--;
	auto target = k ^ prefix[i];
	ans -= counter[target];
}

long long get_answer() {
	return ans;
}

std::vector<long long> mo_s_algorithm() {
	int n, q;
	std::cin >> n >> q >> k;
	std::vector<int> pos(n);
	prefix.resize(n + 1);
	prefix[0] = 0;

	// sqrt decomposition, read n entries
	int siz = std::sqrt(n);
	for (int i = 0; i < n; i++) {
		int x;
		std::cin >> x;
		pos[i] = i / siz;
		prefix[i + 1] = prefix[i] ^ x;
	}


	// read q queries
	std::vector<Query> queries(q);
	for (int i = 0; i < q; i++) {
		std::cin >> queries[i].l >> queries[i].r;
		// count pairs (a, b) s.t. l-1 <= a < b <= r && prefix[a] XOR prefix[b] = k
		queries[i].l--;
		queries[i].idx = i;
	}

	std::sort(queries.begin(), queries.end(),
		[&pos](Query& x, Query& y)->bool {
			return pos[x.l] == pos[y.l] ? x.r < y.r : pos[x.l] < pos[y.l];
	});

	int l = 0, r = -1;   // always reflect the range [l, r]
	std::vector<long long> res(q);

	for (auto& query: queries) {
		while (query.l < l) Add(--l);
		while (query.r > r) Add(++r);
		while (query.l > l) Sub(l++);
		while (query.r < r) Sub(r--);

		// mark down answers
		res[query.idx] = get_answer();
	}
	return res;
}
};


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	auto res = mo::mo_s_algorithm();
	for (auto x: res) {
		cout << x << "\n";
	}
	return 0;
}
