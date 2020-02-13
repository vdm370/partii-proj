#include "ant_colony.h"
#include "greedy.h"
#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool opt2_improve(solution &sol, graph_dist &g) {
  int n = g.nodes;
  if(n <= 4) return false; //nothing to improve
  int a = uniform_int_distribution<int>(0, n - 1)(rng);
  int b = a + 1;
  int c = uniform_int_distribution<int>(0, n - 4)(rng);
  c += (b + 1);
  c %= n;
  int d = c + 1;
  int node_a = sol.order[a % n];
  int node_b = sol.order[b % n];
  int node_c = sol.order[c % n];
  int node_d = sol.order[d % n];
  double first_edge = g.dist[node_a][node_b];
  double second_edge = g.dist[node_c][node_d];
  double new_first_edge = g.dist[node_a][node_c];
  double new_second_edge = g.dist[node_b][node_d];
  if(new_first_edge + new_second_edge < first_edge + second_edge) {
    if(a < c) {
      reverse(sol.order.begin() + b, sol.order.begin() + d);
    } else {
      reverse(sol.order.begin() + d, sol.order.begin() + b);
    }
    sol.value -= (first_edge + second_edge) - (new_first_edge + new_second_edge);
    return true;
  }
  return false;
}

solution twoopt(graph_dist g) {
  solution sol = greedy(g);
  const int ITERATIONS = 100000;
  for(int _iteration = 0; _iteration < ITERATIONS; _iteration++) {
    opt2_improve(sol, g);
  }
  return sol;
}

int main() {
	graph_dist g = read_graph_dist();
	g.print();
	solution s = twoopt(g);
	s.print(true);
	return 0;
}
