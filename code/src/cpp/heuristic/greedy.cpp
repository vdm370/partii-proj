#include "greedy.h"
#include <float.h>
#include <bits/stdc++.h>
using namespace std::chrono;

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

solution rand_greedy(graph_dist g) {
  srand(time(NULL));
  int s = rand() % g.nodes;
  return greedy(g, s);
}

solution greedy(graph_dist g) {
	solution ans = greedy(g, 0);
	for(int start = 1; start < g.nodes; start++) {
		solution tmp = greedy(g, start);
		if(tmp < ans) {
			ans = tmp;
		}
	}
	return ans;
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
	solution s = greedy(g);
  auto end = high_resolution_clock::now(); 
  cout << "The computation has taken " << (duration_cast<milliseconds>(end - start)).count() << "ms" << endl;
  s.print(true);
	return 0;
}

