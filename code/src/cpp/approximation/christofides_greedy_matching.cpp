#include <bits/stdc++.h>
#include "christofides_greedy_matching.h"
#include "unweighted_graph.h"

vector<pair<int, int>> matching(unordered_set<int> odds, graph_dist g) {
  vector<pair<int, int>> ret;
  while(!odds.empty()) {
    int first = *odds.begin();
    odds.erase(first);
    double closest = DBL_MAX;
    int closest_idx = -1;
    for(auto &x : odds) {
      if(g.dist[first][x] < closest) {
        closest = g.dist[first][x];
        closest_idx = x;
      }
    }
    odds.erase(closest_idx);
    ret.push_back({first, closest_idx});
  }
  return ret;
}
