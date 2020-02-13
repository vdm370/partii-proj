#include "bruteforce.h"

using namespace std;

solution bruteforce(graph_dist g) {
	vector<int> indices;
	for(int i = 0; i < g.nodes; i++) {
		indices.push_back(i);
	}
	solution best;
	do {
		double cur = 0.0;
		for(int i = 0; i + 1 < g.nodes; i++) {
			cur += g.dist[indices[i]][indices[i + 1]];
		}
		cur += g.dist[indices.back()][indices[0]];
		if(cur < best.value) {
			best.value = cur;
			best.order = indices;
		}
	} while(next_permutation(indices.begin(), indices.end()));
	return best;
}

int main() {
	graph_dist g = read_graph_dist();
	g.print();
	solution s = bruteforce(g);
	s.print(true);
	return 0;
}