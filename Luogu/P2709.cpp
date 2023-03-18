#include <bits/stdc++.h>
using namespace std;


#include <bits/stdc++.h>
using namespace std;


/**
 * Mo's Algorithm Template (0-indexed)
 * */
namespace mo {
vector<int> a;
long long ans = 0;

vector<int> cnt;

struct Query {
	int l, r, idx;
};


void Add(int i) {
	cnt[a[i]]++;
	ans += 2 * cnt[a[i]] - 1;
}

void Sub(int i) {
	cnt[a[i]]--;
	ans -= 2 * cnt[a[i]] + 1;
}

long long get_answer() {
	return ans;
}

vector<long long> mo_s_algorithm() {
	int n, q;
	cin >> n >> q;
	vector<int> pos(n);
	a.resize(n);

	int k;
	cin >> k;
	cnt.resize(k + 1, 0);
	
	// sqrt decomposition, read n entries
	int siz = sqrt(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		pos[i] = i / siz;
	}

	// read q queries
	vector<Query> queries(q);
	for (int i = 0; i < q; i++) {
		cin >> queries[i].l >> queries[i].r;		// need to -1 if 1-indexed
		queries[i].l--; queries[i].r--;
		queries[i].idx = i;
	}

	std::sort(queries.begin(), queries.end(),
		[&pos](Query& x, Query& y)->bool {
			return pos[x.l] == pos[y.l] ? x.r < y.r : pos[x.l] < pos[y.l];
	});

	int l = 0, r = -1;   // always reflect the range [l, r]
	vector<long long> res(q);

	for (int i = 0; i < q; i++) {
		while (queries[i].l < l) Add(--l);
		while (queries[i].r > r) Add(++r);
		while (queries[i].l > l) Sub(l++);
		while (queries[i].r < r) Sub(r--);

		// mark down answers
		res[queries[i].idx] = get_answer();
	}
	return res;
}
};


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	auto res = mo::mo_s_algorithm();
	for (auto x: res)
		cout << x << "\n";
	return 0;
}
