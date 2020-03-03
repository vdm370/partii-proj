#include "ant_colony.h"
#include <bits/stdc++.h>

const double RHO = 0.5;
const double ALPHA = 1;
const double BETA = 1;
const int ITERATIONS = 10000;
const int ANTS = 20;
const double Q = 100;
const bool DEBUG = false;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<int> simulate_ant(int nodes, vector<vector<double>> &pheromone, vector<vector<double>> &inv_dist) {
  int node = uniform_int_distribution<int>(0, nodes - 1)(rng);
  vector<int> ret;
  ret.push_back(node);
  vector<bool> visited(nodes);
  visited[node] = true;
  for(int i = 0; i + 1 < nodes; i++) {
    int next = -1;
    vector<pair<int, double>> probs;
    double prob_sum = 0;
    for(int nn = 0; nn < nodes; nn++) {
      if(visited[nn]) continue;
      double prob = pow(pheromone[node][nn], ALPHA) * pow(inv_dist[node][nn], BETA);
      probs.push_back({nn, prob_sum + prob});
      prob_sum += prob;
    }
    double rnd = uniform_real_distribution<double>(0, prob_sum)(rng);
    for(auto &xt : probs) {
      if(rnd <= xt.second) {
        next = xt.first;
        break;
      }
    }
    assert(next + 1);
    ret.push_back(next);
    visited[next] = true;
    node = next;
  }
  return ret;
}

void update_dpheromone(vector<vector<double>> &dpheromone, double len, vector<int> path) {
  for(int i = 0; i + 1 < (int)path.size(); i++) {
    dpheromone[path[i]][path[i + 1]] += Q / len;
  }
  if((int)path.size() > 1) dpheromone[path.back()][path[0]] += Q / len;
}

void apply_dpheromone(int nodes, vector<vector<double>> &pheromone, vector<vector<double>> &dpheromone) {
  for(int i = 0; i < nodes; i++) {
    for(int j = 0; j < nodes; j++) {
      pheromone[i][j] = RHO * pheromone[i][j] + dpheromone[i][j];
    }
  }
}

solution ant_colony(graph_dist g) {
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
  if(DEBUG) puts("UMESTO PEHARA");
  for(int iteration = 0; iteration < ITERATIONS; iteration++) {
    if(DEBUG) printf("ITERATION %d\n", iteration);
    vector<vector<double>> dpheromone(nodes);
    for(int i = 0; i < nodes; i++) {
      dpheromone[i].resize(nodes);
    }
    for(int i = 0; i < nodes; i++) {
      for(int j = 0; j < nodes; j++) {
        dpheromone[i][j] = 0;
      }
    }
    if(DEBUG) printf("HALFWAY THROUGH\n");
    for(int ant = 0; ant < ANTS; ant++) {
      if(DEBUG) printf("ANT %d STARTING\n", ant);
      vector<int> path = simulate_ant(nodes, pheromone, inv_dist);
      double l = g.get_value(path);
      update_dpheromone(dpheromone, l, path);
    }
    if(DEBUG) printf("UPDATING PHEROMONE\n");
    apply_dpheromone(nodes, pheromone, dpheromone);
  }
  if(DEBUG) puts("U RUKAMA CE BITI NASA KURCINA");
  vector<int> path = simulate_ant(nodes, pheromone, inv_dist);
  return solution(g.get_value(path), path);
}

int main() {
	graph_dist g = read_graph_dist();
	g.print();
	solution s = ant_colony(g);
	s.print(true);
	return 0;
}
