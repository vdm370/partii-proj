#include "solution.h"
#include "graph_dist.h"
#include <unordered_set>
#include <float.h>

const double EPS = 1e-8;
solution::solution() {
	value = DBL_MAX;
}
solution::solution(double val, vector<int> ind) {
	value = val;
	order = ind;
}
bool solution::operator<(const solution &other) const {
	return value < other.value;
}
bool solution::sane(graph_dist &g) {
	puts("checking sanity right now");
	print(true);
	int n = g.nodes;
	unordered_set<int> act;
	for(auto &x : order) {
		if(x < 0 || x >= n) return false;
		act.insert(x);
	}
	if((int)act.size() != n) return false;
	puts("all nodes are correct");
	double cost = 0;
	for(int i = 0; i + 1 < n; i++) {
		cost += g.dist[order[i]][order[i + 1]];
	}
	cost += g.dist[order.back()][order[0]];
	return abs(cost - value) < EPS;
}
void solution::print(bool path) {
	printf("Solved the TSP with: %.2f\n", value);
	if(path) {
		for(int i = 0; i < (int)order.size(); i++) {
			if(i + 1 == (int)order.size()) printf("%d\n", order[i]);
			else printf("%d ", order[i]);
		}
	}
}
