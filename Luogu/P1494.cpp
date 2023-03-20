#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <utility>
#include <numeric>
using namespace std;


/**
 * Mo's Algorithm Template (0-indexed)
 * Time: O((N + Q) * F * sqrt(N)), where F: complexity of add(), sub()
 * */
namespace mo {

struct Query {
	int l, r, idx;
};

std::vector<int> a;
std::vector<int> cnt;
long long numerator = 0;

void Add(int i) {
	numerator += cnt[a[i]];
	cnt[a[i]]++;
}

void Sub(int i) {
	cnt[a[i]]--;		
	numerator -= cnt[a[i]];
}

pair<int, int> get_answer(long long denominator) {
	long long g = gcd(numerator, denominator);
	return {numerator / g, denominator / g};
}

vector<pair<int, int>> mo_s_algorithm() {
	int n, q;
	std::cin >> n >> q;
	std::vector<int> pos(n);
	a.resize(n);
	cnt.resize(n, 0);

	// sqrt decomposition, read n entries
	int siz = std::sqrt(n);
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
		pos[i] = i / siz;
	}

	// read q queries
	std::vector<Query> queries(q);
	for (int i = 0; i < q; i++) {
		std::cin >> queries[i].l >> queries[i].r;	// need to -1 if 1-indexed
		queries[i].l--;
		queries[i].r--;
		queries[i].idx = i;
	}

	std::sort(queries.begin(), queries.end(),
		[&pos](Query& x, Query& y)->bool {
			return pos[x.l] == pos[y.l] ? x.r < y.r : pos[x.l] < pos[y.l];
	});

	int l = 0, r = -1;   // always reflect the range [l, r]
	std::vector<pair<int, int>> res(q);

	for (int i = 0; i < q; i++) {
		while (queries[i].l < l) Add(--l);
		while (queries[i].r > r) Add(++r);
		while (queries[i].l > l) Sub(l++);
		while (queries[i].r < r) Sub(r--);

		// get answers
		if (l == r || !numerator)
			res[queries[i].idx] = {0, 1};
		else {
			auto [a, b] = get_answer((long long)(r - l + 1) * (long long)(r - l) / 2) ;
			res[queries[i].idx] = {a, b};
		}
	}
	return res;
}
};


int main(int argc, char const *argv[])
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	auto res = mo::mo_s_algorithm();
	for (auto [a, b]: res)
		cout << a << "/" << b << "\n";
	return 0;
}
