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
double graph_dist::get_value(vector<int> ind) {
	double ans = 0;
	for(int i = 0; i + 1 < (int)ind.size(); i++) {
		ans += dist[ind[i]][ind[i + 1]];
	}
	ans += dist[ind.back()][ind[0]];
	return ans;
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