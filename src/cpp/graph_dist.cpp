#include "graph_dist.h"
graph_dist::graph_dist() {
	nodes = 0;
}
graph_dist::graph_dist(int n) {
	nodes = n;
	dist.resize(n);
	for(int i = 0; i < n; i++) {
		dist[i].resize(n);
	}
}
void graph_dist::read() {
	for(int i = 0; i < nodes; i++) {
		for(int j = 0; j < nodes; j++) {
			scanf("%lf", &dist[i][j]);
		}
	}
}
graph_dist read_graph_dist() {
	int n; scanf("%d", &n);
	graph_dist ret(n);
	ret.read();
	return ret;
}