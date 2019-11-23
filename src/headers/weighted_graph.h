#include <bits/stdc++.h>
using namespace std;
struct weighted_graph {
	int nodes;
	vector<vector<pair<int, double>>> adj;
	weighted_graph(int n);
	weighted_graph();
	void add_edge(int u, int v, double f);
	void read();
};

weighted_graph read_weighted_graph();