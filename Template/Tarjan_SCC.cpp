#include <vector>
#include <stack>


struct Edge {
	int to;
};

/**
 * Tarjan's SCC algorithm template
 * scc[u], siz[u]: idx/size of the scc which u belongs to
 * num_scc: # SCCs
 * */
namespace Tarjan_SCC {

int n;
std::vector<int> dfn, low;
std::vector<bool> in_stack;
std::stack<int> stk;
std::vector<int> scc, siz;
int num_scc = 0, timer = 0;

void dfs(int u, const std::vector<std::vector<Edge>>& adj) {
	dfn[u] = low[u] = timer++;
	stk.push(u);
	in_stack[u] = true;
	for (auto& edge: adj[u]) {
		auto v = edge.to;
		if (!dfn[v]) {
			// u is the parent of v
			dfs(v, adj);
			low[u] = std::min(low[u], low[v]);
		} else if (in_stack[v]) {
			// if v is in stack, it is an ancestor or sibling
			low[u] = std::min(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u]) {	// if u is the root of the SCC
		int v;
		do {
			v = stk.top();
			stk.pop();
			in_stack[v] = 0;
			scc[v] = num_scc;
			siz[num_scc]++;
		} while (u != v);
		num_scc++;
	}
}

void run_tarjan(const std::vector<std::vector<Edge>>& adj) {
	int n = adj.size();		// assume 0-indexed
	dfn.resize(n, -1); low.resize(n, -1); in_stack.resize(n, false);
	scc.resize(n); siz.resize(n, 0);
	
	for (int i = 0; i < n; i++)
		if (dfn[i] == -1) dfs(i, adj);
}
}
