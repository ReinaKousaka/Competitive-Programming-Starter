#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>


/**
 * Mo's Algorithm Template (0-indexed)
 * Time: O((N + Q) * F * sqrt(N)), where F: complexity of add(), sub()
 * */
namespace mo {

struct Query {
	int l, r, idx;
};

std::vector<int> a;
int ans = 0;

void Add(int i) {

}

void Sub(int i) {

}

int get_answer() {
	return ans;
}

std::vector<int> mo_s_algorithm() {
	int n, q;
	std::cin >> n >> q;
	std::vector<int> pos(n);
	a.resize(n);

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
		queries[i].idx = i;
	}

	std::sort(queries.begin(), queries.end(),
		[&pos](Query& x, Query& y)->bool {
			return pos[x.l] == pos[y.l] ? x.r < y.r : pos[x.l] < pos[y.l];
	});

	int l = 0, r = -1;   // always reflect the range [l, r]
	std::vector<int> res(q);

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
