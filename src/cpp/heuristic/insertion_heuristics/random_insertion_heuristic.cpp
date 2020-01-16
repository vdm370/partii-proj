#include "random_insertion_heuristic.h"
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

inline double insert_cost(graph_dist &g, int i, int j, int k) {
  return g.dist[i][j] + g.dist[j][k] - g.dist[i][k];
}

solution random_ins(graph_dist &g, int start) {
    vector<int> path;
    path.push_back(start);
    path.push_back(start);
    vector<int> untaken;
    int n = g.nodes;
    for(int i = 0; i < n; i++) {
      if(i - start) untaken.push_back(i);
    }
    for(int steps = 0; steps < n - 1; steps++) {
      //I need to chose one of untaken, randomly
      int idx = uniform_int_distribution<int>(0, n - steps - 1)(rng);
      int node = untaken[idx];
      untaken.erase(untaken.begin() + idx);
      int best_place = 0;
      double best_cost = insert_cost(path[0], node, path[1]);
      for(int i = 1; i < steps + 1; i++) {
        double cost_here = insert_cost(path[i], node, path[i + 1]);
        if(cost_here < best_cost) {
          best_cost = cost_here;
          best_place = i;
        }
      }
      path.insert(path.begin() + best_place + 1, node);
    }
    assert(path[0] == path.back());
    path.pop_back();
    return solution(g.get_value(path), path);
}

solution random_insertion_heuristic(graph_dist g) {
  srand(time(NULL));
  solution best = random_ins(g, 0);
  for(int i = 1; i < g.nodes; i++) {
    best = min(best, random_ins(g, i));
  }
  return best;
}

int main() {
  graph_dist g;
  g.read();
  g.print();
  auto sol = random_insertion_heuristic(g);
  sol.print(true);
  return 0;
}
