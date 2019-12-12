#include "greedy.h"
#include <float.h>
solution greedy(graph_dist g, int start) {
	double value = 0.0;
	vector<bool> mark(g.nodes, false);
	mark[start] = true;
	vector<int> order;
	order.push_back(start);
	int cur = start;
	for(int i = 0; i < g.nodes - 1; i++) {
		double best = DBL_MAX;
		int best_ind = -1;
		for(int j = 0; j < g.nodes; j++) {
			if(mark[j]) continue;
			if(g.dist[cur][j] < best) {
				best = g.dist[cur][j];
				best_ind = j;
			}
		}
		order.push_back(best_ind);
		value += best;
		cur = best_ind;
		mark[cur] = true;
	}
	value += g.dist[cur][start];
	return solution(value, order);
}
solution greedy(graph_dist g) {
	solution ans;
	for(int start = 0; start < g.nodes; start++) {
		solution tmp = greedy(g, start);
		if(tmp < ans) {
			ans = tmp;
		}
	}
	return ans;
}

int main() {
	graph_dist g = read_graph_dist();
	g.print();
	solution s = greedy(g);
	s.print(true);
	return 0;
}