#include "weighted_graph.h"

using namespace std;

weighted_graph::weighted_graph() {
	nodes = 0;
}

weighted_graph::weighted_graph(int n) {
	nodes = n;
	adj.clear();
	adj.resize(nodes);
}

void weighted_graph::add_edge(int u, int v, double f) {
	adj[u].push_back({v, f});
	adj[v].push_back({u, f});
}

void weighted_graph::read() {
	scanf("%d", &nodes);
	adj.clear();
	adj.resize(nodes);
	int edges; scanf("%d", &edges);
	for(int i = 0; i < edges; i++) {
		int u, v; double f;
		scanf("%d %d %lf", &u, &v, &f);
		add_edge(u, v, f);
	}
}

weighted_graph read_weighted_graph() {
	weighted_graph ret;
	ret.read();
	return ret;
}
