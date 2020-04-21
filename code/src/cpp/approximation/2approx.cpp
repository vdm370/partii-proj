#include "2approx.h"
using namespace std;

using namespace std::chrono;
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

vector<int> ret;
unordered_set<int> visited;
void dfs(unweighted_graph &g, int src) {
  visited.insert(src);
  ret.push_back(src);
  for(auto &xt : g.adj[src]) {
    if(!visited.count(xt)) {
      dfs(g, xt);
    }
  }
}

vector<int> dfs_order(unweighted_graph g, int start = 0) {
  ret.clear();
  visited.clear();
  dfs(g, start);
  return ret;
}

solution approx2(graph_dist g) {
	//we want to find the MST
	vector<edge> edges;
	for(int i = 0; i < g.nodes; i++) {
		for(int j = 0; j < i; j++) {
			edges.emplace_back(i, j, g.dist[i][j]);
		}
	}
	sort(edges.begin(), edges.end());
	dsu g_dsu(g.nodes);
  unweighted_graph minimum_spanning_tree(g.nodes);
	for(int i = 0; i < (int)edges.size(); i++) {
		if(g_dsu.unite(edges[i].u, edges[i].v)) {
			minimum_spanning_tree.add_edge(edges[i].u, edges[i].v);
		}
	}
  int root = 0; //just for the example, this is a parameter
	vector<int> cycle = dfs_order(minimum_spanning_tree, root);
  //vector<int> cycle = remove_duplicates(dfs_order);
  return solution(g.get_value(cycle), cycle);
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
  auto start = high_resolution_clock::now(); 
	solution s = approx2(g);
  auto end = high_resolution_clock::now(); 
	s.print(true);
  cout << "The computation has taken " << (duration_cast<milliseconds>(end - start)).count() << "ms" << endl;
	return 0;
}
