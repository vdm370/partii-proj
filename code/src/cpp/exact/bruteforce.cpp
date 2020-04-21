#include "bruteforce.h"
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
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
	} while(next_permutation(indices.begin() + 1, indices.end()));
	return best;
}

int main() {
	graph_dist g = read_graph_dist();
	g.print();
	auto start = high_resolution_clock::now(); 
	solution s = bruteforce(g);
	auto end = high_resolution_clock::now(); 
	s.print(true);
	cout << "The computation has taken " << (duration_cast<milliseconds>(end - start)).count() << "ms" << endl;
	return 0;
}
