#ifndef MATCHING_H
#define MATCHING_H

#include "graph_dist.h"
#include <unordered_set>
using namespace std;

vector<pair<int, int>> matching(unordered_set<int>, graph_dist, bool);

#endif
