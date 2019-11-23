#include "unweighted_graph.h"

#include <bits/stdc++.h>
using namespace std;

unweighted_graph::unweighted_graph() {
	nodes = 0;
}

unweighted_graph::unweighted_graph(int n) {
	nodes = n;
	adj.clear();
	adj.resize(nodes);
}

void unweighted_graph::add_edge(int u, int v) {
	adj[u].push_back(v);
	adj[v].push_back(u);
}

void unweighted_graph::read() {
	scanf("%d", &nodes);
	adj.clear();
	adj.resize(nodes);
	int edges; scanf("%d", &edges);
	for(int i = 0; i < edges; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		add_edge(u, v);
	}
}

unweighted_graph read_graph() {
	unweighted_graph ret;
	ret.read();
	return ret;
}
