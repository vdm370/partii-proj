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
	}
};

solution christofides(graph_dist g) {
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
	set<int> o;
	for(int i = 0; i < g.nodes; i++) {
		if(mst_degree[i] % 2 == 1) {
			o.insert(i);
		}
	}
	assert(o.size() % 2 == 0);
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
	solution s = dyn_prog(g);
	s.print(true);
	return 0;
}