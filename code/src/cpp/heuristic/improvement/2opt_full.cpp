#include "ant_colony.h"
#include "greedy.h"
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

bool opt2_improve(solution &sol, graph_dist &g) {
  int n = g.nodes;
  if(n <= 4) return false; //nothing to improve
  int improved = 0;
  for(int a = 0; a < n; a++) {
    for(int c = a + 2; c < n; c++) {
      if(c == n - 1 && a == 0) continue;
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
        reverse(sol.order.begin() + b, d == 0 ? sol.order.end() : sol.order.begin() + d);
        sol.value -= (first_edge + second_edge) - (new_first_edge + new_second_edge);
        //assert(sol.sane(g));
        improved += 1;
      }
    }
  }
  return improved > 0;
}

solution twoopt(graph_dist g) {
  solution sol = rand_greedy(g);
  double starting_point = sol.value;
  //assert(sol.sane(g));
  bool improved = true;
  while(improved) improved = opt2_improve(sol, g);
  printf("the starting value was %.2f\n", starting_point);
  return sol;
}

int main() {
	graph_dist g = read_graph_dist();
	g.print();
	auto start = high_resolution_clock::now(); 
	solution s = twoopt(g);
	auto end = high_resolution_clock::now(); 
	s.print(true);
	cout << "The computation has taken " << (duration_cast<milliseconds>(end - start)).count() << "ms" << endl;
	return 0;
}
