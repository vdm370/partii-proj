#include <bits/stdc++.h>
#include "christofides_matching.h"
#include <lemon/list_graph.h>
#include <lemon/matching.h>
using namespace lemon;

vector<pair<int, int>> greedy_matching(unordered_set<int> odds, graph_dist g) {
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

vector<pair<int, int>> perfect_matching(unordered_set<int> odds, graph_dist g) {
  vector<int> nod;
  for(auto &x : odds) nod.push_back(x);
  ListGraph gg;
  int n = nod.size();
  vector<ListGraph::Node> nodes(n);
  map<ListGraph::Node, int> idx;
  for(int i = 0; i < n; i++) {
    nodes[i] = gg.addNode();
    idx[nodes[i]] = nod[i];
  }
  ListGraph::EdgeMap<double> weight(gg);
  vector<ListGraph::Edge> edges;
  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) {
      ListGraph::Edge e = gg.addEdge(nodes[i], nodes[j]);
      weight[e] = -g.dist[nod[i]][nod[j]];
    }
  }
  MaxWeightedPerfectMatching<ListGraph, ListGraph::EdgeMap<double>> perfect(gg, weight);
  perfect.run();
  vector<pair<int, int>> ret;
  for(int i = 0; i < n; i++) {
    ListGraph::Node m = perfect.mate(nodes[i]);
    int id = idx[m];
    if(id > nod[i]) ret.push_back({id, nod[i]});
  }
  return ret;
}

vector<pair<int, int>> matching(unordered_set<int> odds, graph_dist g, bool greedy) {
  if(greedy) return greedy_matching(odds, g);
  else return perfect_matching(odds, g);
}
