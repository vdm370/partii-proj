#include <bits/stdc++.h>
#include "christofides.h"
using namespace std;

struct edge {
	int u, v;
	double f;
	edge(int _u, int _v, double _f) {
		u = _u;
		v = _v;
		f = _f;
	}
	bool operator <(const edge &other) const {
		return f < other.f;
	}
};

struct dsu {
	int n;
	vector<int> par, rank;
	dsu(int _n) {
		n = _n;
		par.resize(n);
		rank.resize(n);
		for(int i = 0; i < n; i++) {
			par[i] = i;
			rank[i] = 1;
		}
	}
	int get(int x) {
		if(par[x] == x) return x;
		return par[x] = get(par[x]);
	}
	bool unite(int x, int y) {
		x = get(x);
		y = get(y);
		if(x == y) return false;
		if(rank[x] < rank[y]) swap(x, y);
		par[y] = x;
		rank[x] += rank[y];
		return true;
	}
};

void find_euler(unweighted_graph g, int start, vector<int> &path) {
	stack<int> st;
	int cur = start;
	path.push_back(start);
	while(!st.empty() || !g.adj[cur].empty()) {
		if(g.adj[cur].empty()) {
			path.push_back(cur);
			cur = st.top();
			st.pop();
		} else {
			st.push(cur);
			int some_adj = g.adj[cur].back();
			g.adj[cur].pop_back();
			g.adj[some_adj].erase(find(g.adj[some_adj].begin(), g.adj[some_adj].end(), cur));
			cur = some_adj;
		}
	}
	path.push_back(cur);
}

double make_hamiltonian(vector<int> &path, graph_dist &g) {
	int n = (int)path.size(); //TODO: Mozda -1
	vector<bool> mark(n, false);
	double ret = 0;
	int cur = path[0];
	auto cur_it = path.begin(), nx_it = path.begin() + 1;
	mark[cur] = true;
	while(nx_it != path.end()) {
		if(!mark[*nx_it]) {
			ret += g.dist[*cur_it][*nx_it];
			cur_it = nx_it;
			mark[*cur_it] = true;
			nx_it = cur_it + 1;
		} else {
			nx_it = path.erase(nx_it);
		}
	}
	ret += g.dist[*nx_it][*cur_it];
	return ret;
}

solution solve_euler(unweighted_graph &g, graph_dist &d, int start) {
		vector<int> path;
		find_euler(g, start, path);
		double ans = make_hamiltonian(path, d);
		return solution(ans, path);
}

solution christofides(graph_dist g, int start = -1) {
	assert(start >= -1);
	assert(start < g.nodes);
	//assumption: g is undirected graph
	//first, we want to find a MST of g
	vector<edge> edges;
	for(int i = 0; i < g.nodes; i++) {
		for(int j = 0; j < i; j++) {
			edges.emplace_back(i, j, g.dist[i][j]);
		}
	}
	sort(edges.begin(), edges.end());
	dsu g_dsu(g.nodes);
	vector<int> mst_degree(g.nodes, 0);
	vector<int> edge_indices;
	for(int i = 0; i < (int)edges.size(); i++) {
		if(g_dsu.unite(edges[i].u, edges[i].v)) {
			edge_indices.push_back(i);
			mst_degree[edges[i].u] += 1;
			mst_degree[edges[i].v] += 1;
		}
	}
	unordered_set<int> o;
	for(int i = 0; i < g.nodes; i++) {
		if(mst_degree[i] % 2 == 1) {
			o.insert(i);
		}
	}
	assert(o.size() % 2 == 0);
	auto odds_matching = matching(o, g);
	unweighted_graph mst_enhanced(g.nodes);
	for(auto &idx : edge_indices) {
		int u = edges[idx].u, v = edges[idx].v;
		mst_enhanced.add_edge(u, v);
	}
	for(auto &pr : odds_matching) {
		mst_enhanced.add_edge(pr.first, pr.second);
	}
	if(start == -1) {
		solution best = solve_euler(mst_enhanced, g, 0);
		for(int st = 1; st < g.nodes; st++) {
			solution cur = solve_euler(mst_enhanced, g, st);
			if(cur < best) best = cur;
		}
		 return best;
	}
	return solve_euler(mst_enhanced, g, start);
}

int main() {
	graph_dist g = read_graph_dist();
	printf("%d\n", g.nodes);
	for(int i = 0; i < g.nodes; i++) {
		for(int j = 0; j < g.nodes; j++) {
			printf("%.2f ", g.dist[i][j]);
		}
		printf("\n");
	}
	solution s = christofides(g);
	s.print(true);
	return 0;
}
