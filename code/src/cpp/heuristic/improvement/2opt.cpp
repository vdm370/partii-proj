#include "ant_colony.h"
#include "greedy.h"
#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool opt2_improve(solution &sol, graph_dist &g) {
  int n = g.nodes;
  if(n <= 4) return false; //nothing to improve
  int a, c;
  do {
    a = uniform_int_distribution<int>(0, n - 1)(rng);
    c = uniform_int_distribution<int>(0, n - 1)(rng);
    if(a > c) swap(a, c);
  } while(min(abs(a - c), abs(c - a)) <= 1);
  int b = (a + 1) % n;
  int d = (c + 1) % n;
  int node_a = sol.order[a % n];
  int node_b = sol.order[b % n];
  int node_c = sol.order[c % n];
  int node_d = sol.order[d % n];
  double first_edge = g.dist[node_a][node_b];
  double second_edge = g.dist[node_c][node_d];
  double new_first_edge = g.dist[node_a][node_c];
  double new_second_edge = g.dist[node_d][node_b];
  if(new_first_edge + new_second_edge < first_edge + second_edge) {
    reverse(sol.order.begin() + b, sol.order.begin() + d);
    sol.value -= (first_edge + second_edge) - (new_first_edge + new_second_edge);
    assert(sol.sane(g));
    return true;
  }
  return false;
}

solution twoopt(graph_dist g) {
  solution sol = greedy(g);
  assert(sol.sane(g));
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
