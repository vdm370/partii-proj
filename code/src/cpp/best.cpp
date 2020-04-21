#include "kernighen_lin.h"
#include "greedy.h"
#include "random_insertion_heuristic.h"
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

typedef pair<int, int> edge;
typedef set<edge> edge_set;

const bool DEBUG = false;
const double EPS = 1e-8;

const int NBTRY = 5;

solution best_sol;

vector<int> get_neighbs(vector<int> &a, int x) {
  int i = -1;
  for(int j = 0; j < (int)a.size(); j++) {
    if(a[j] == x) {
      i = j;
      break;
    }
  }
  assert(i + 1);
  vector<int> ret;
  if(i) ret.push_back(a[i - 1]);
  else ret.push_back(a.back());
  if(i < (int)a.size() - 1) ret.push_back(a[i + 1]);
  else ret.push_back(a[0]);
  return ret;
}

pair<int, int> edge_pair(int i, int j) {
    if(i < j) return make_pair(i, j);
    else return make_pair(j, i);
}

vector<pair<int, pair<double, double>>> get_closest(graph_dist &g, int node, vector<int> path, double gain, edge_set broken, edge_set joined) {
  vector<pair<int, pair<double, double>>> ret;
  unordered_map<int, int> ret_map;
  vector<int> node_nbs = get_neighbs(path, node);
  for(int xt = 0; xt < g.nodes; xt++) {
    if(node == xt) continue; //can't be the same node
    bool wrong = false;
    for(int i = 0; i < 2; i++) {
      if(node_nbs[i] == xt) {
        wrong = true;
        break;
      }
    }
    if(wrong) continue;
    edge join_edge = edge_pair(node, xt);
    if(broken.count(join_edge)) continue;
    double cur_gain = gain - g.dist[node][xt];
    if(cur_gain < EPS) continue;
    vector<int> xt_nbs = get_neighbs(path, xt);
    for(auto xt2 : xt_nbs) {
      edge break_edge = edge_pair(xt, xt2);
      if(broken.count(break_edge)) continue;
      if(joined.count(break_edge)) continue;
      double d = g.dist[xt][xt2] - g.dist[node][xt];
      if(ret_map.find(xt) == ret_map.end()) {
        ret.push_back({xt, {d, cur_gain}});
        ret_map[xt] = (int)ret.size() - 1;
      } else {
        ret[ret_map[xt]].second.first = max(ret[ret_map[xt]].second.first, d);
      }
    }
  }
  return ret;
}

void sort_nodes(vector<pair<int, pair<double, double>>> &vec) {
  sort(vec.begin(), vec.end(), [](pair<int, pair<double, double>> a, pair<int, pair<double, double>> b) {
    return a.second.first > b.second.first;
  });
}

set<vector<int>> already_found;

edge_set get_edges(vector<int> &path) {
  edge_set ret;
  for(int i = 0; i + 1 < (int)path.size(); i++) {
    ret.insert(edge_pair(path[i], path[i + 1]));
  }
  ret.insert(edge_pair(path.back(), path[0]));
  return ret;
}

vector<int> traversal;
unordered_set<int> visited;
vector<vector<int>> adj;
void dfs(int src) {
  traversal.push_back(src);
  visited.insert(src);
  for(auto &xt : adj[src]) {
    if(!visited.count(xt)) dfs(xt);
  }
}

bool alter(vector<int> &path, vector<int> &new_path, edge_set broken, edge_set joined) {
  if(DEBUG) {
    printf("Called alter with\n");
    for(auto &x : path) printf("%d ", x); printf("\n");
    printf("%d %d\n", (int)broken.size(), (int)joined.size());
    for(auto &e : broken) printf("break %d %d\n", e.first, e.second);
    for(auto &e : joined) printf("join %d %d\n", e.first, e.second);
  }
  int n = (int)path.size();
  edge_set edges = get_edges(path);
  if(DEBUG) printf("edges.size = %d\n", (int)edges.size());
  for(auto &br : broken) edges.erase(br);
  if(DEBUG) printf("edges.size = %d\n", (int)edges.size());
  for(auto &jo : joined) edges.insert(jo);
  if(DEBUG) printf("edges.size = %d\n", (int)edges.size());
  if((int)edges.size() < n) return false;
  adj.resize(n);
  for(int i = 0; i < n; i++) adj[i].clear();
  for(auto &e : edges) {
    adj[e.first].push_back(e.second);
    adj[e.second].push_back(e.first);
  }
  for(int i = 0; i < n; i++) {
    if((int)adj[i].size() != 2) return false;
  }
  traversal.clear();
  visited.clear();
  dfs(0);
  if(traversal.size() == n) {
    new_path = traversal;
    return true;
  } else return false;
}

bool lk_choosey(graph_dist&, vector<int>&, int, int, double, edge_set, edge_set);

bool lk_choosex(graph_dist &g, vector<int> &path, int node1, int node2, double gain, edge_set broken, edge_set joined) {
  vector<int> nbs = get_neighbs(path, node2);
  if((int)broken.size() == 4) {
    if(g.dist[nbs[0]][node2] > g.dist[nbs[1]][node2]) {
      nbs.pop_back();
    } else {
      reverse(nbs.begin(), nbs.end());
      nbs.pop_back();
    }
  }
  for(auto xt : nbs) {
    edge break_edge = edge_pair(node2, xt);
    double gain_here = gain + g.dist[node2][xt];
    if(joined.count(break_edge)) continue;
    if(broken.count(break_edge)) continue;
    edge_set joined1 = joined;
    edge_set broken1 = broken;
    broken1.insert(break_edge);
    edge join_edge = edge_pair(xt, node1);
    joined1.insert(join_edge);
    double d = gain_here - g.dist[xt][node1];
    vector<int> new_path;
    bool okay = alter(path, new_path, broken1, joined1);
    if(!okay && (int)joined1.size() > 2) {
      continue;
    }
    if(already_found.find(new_path) != already_found.end()) {
      continue;
    }
    if(okay && d > EPS) {
      best_sol.order = new_path;
      best_sol.value -= d;
      if(DEBUG) printf("I've improved my solution by %.2f\n", d);
      assert(best_sol.sane(g));
      return true;
    } else {
      bool choice = lk_choosey(g, best_sol.order, node1, xt, gain_here, broken1, joined);
      if((int)broken.size() == 2 && choice) {
        return true;
      } else {
        return choice;
      }
    }
  }
  return false;
}

bool lk_choosey(graph_dist &g, vector<int> &path, int node1, int node2, double gain, edge_set broken, edge_set joined) {
  auto closest = get_closest(g, node2, path, gain, broken, joined);
  sort_nodes(closest);
  int checks = ((int)broken.size() == 2) ? 5 : 1;
  for(int i = 0; i < min(checks, (int)closest.size()); i++) {
    int xt = closest[i].first;
    edge join_edge = edge_pair(node2, xt);
    double gain_here = closest[i].second.second;
    edge_set joined1 = joined;
    joined1.insert(join_edge);
    bool choose_x = lk_choosex(g, path, node1, xt, gain_here, broken, joined1);
    if(choose_x) return true;
  }
  return false;
}

bool lk_improve(graph_dist &g) {
  int n = g.nodes;
  for(int n1_idx = 0; n1_idx < n; n1_idx++) {
    int node1 = best_sol.order[n1_idx];
    vector<int> neighbs = get_neighbs(best_sol.order, node1);
    for(auto node2 : neighbs) {
      //we need to create a set of broken edges
      edge_set broken;
      broken.insert(edge_pair(node1, node2));
      double gain = g.dist[node1][node2];
      auto closest = get_closest(g, node2, best_sol.order, gain, broken, {});
      sort_nodes(closest);
      for(int i = 0; i < min(NBTRY, (int)closest.size()); i++) {
        int node3 = closest[i].first;
        bool wrong = false;
        for(auto &nb : neighbs) {
          if(nb == node3) {
            wrong = true;
            break;
          }
        }
        if(wrong) continue;
        double gain_here = closest[i].second.second;
        edge_set joined;
        joined.insert(edge_pair(node2, node3));
        bool choose_x = lk_choosex(g, best_sol.order, node1, node3, gain_here, broken, joined);
        if(choose_x) return true;
      }
    }
  }
  return false;
}

solution lin_kernighen(graph_dist g) {
  best_sol = random_insertion_heuristic(g);
  assert(best_sol.sane(g));
  bool improvement = true;
  while(improvement) {
    improvement = lk_improve(g);
  }
  return best_sol;
}

int main() {
	graph_dist g = read_graph_dist();
	g.print();
  auto start = high_resolution_clock::now(); 
	solution s = lin_kernighen(g);
  auto end = high_resolution_clock::now(); 
	cout << "The computation has taken " << (duration_cast<milliseconds>(end - start)).count() << "ms" << endl;
  s.print(true);
	return 0;
}
