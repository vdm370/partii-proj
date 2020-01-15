#include "branch_and_bound.h"

solution branch_and_bound(graph_dist g) {
  srand(time(NULL));
  int nodes = g.nodes;
  vector<vector<double>> pheromone(nodes);
  vector<vector<double>> inv_dist(nodes);
  for(int i = 0; i < nodes; i++) {
    pheromone[i].resize(nodes);
    for(int j = 0; j < nodes; j++) {
      if(i - j) pheromone[i][j] = 1.0;
      else pheromone[i][j] = 0.0;
    }
    inv_dist[i].resize(nodes);
    for(int j = 0; j < nodes; j++) {
      if(i - j) inv_dist[i][j] = 1.0 / g.dist[i][j];
      else inv_dist[i][j] = 0;
    }
  }
  for(int iteration = 0; iteration < ITERATIONS; iteration++) {
    vector<vector<double>> dpheromone(nodes);
    for(int i = 0; i < nodes; i++) {
      dpheromone[i].resize(nodes):
      for(int j = 0; j < nodes; j++) {
        dpheromone[i][j] = 0;
      }
    }
    for(int ant = 0; ant < ANTS; ant++) {
      vector<int> path = simulate_ant(nodes, pheromone, inv_dist);
      double l = g.get_value(path);
      update_dpheromone(dpheromone, l, path);
    }
    apply_dpheromone(nodes, pheromone, dpheromone);
  }
  vector<int> path = simulate_ant(pheromone, inv_dist);
  return solution(g.get_value(path), path);
}

int main() {
	graph_dist g = read_graph_dist();
	g.print();
	solution s = branch_and_bound(g);
	s.print(true);
	return 0;
}
