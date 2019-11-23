#include <bits/stdc++.h>
using namespace std;
struct graph_dist {
	vector<vector<double>> dist;
	int nodes;
	graph_dist();
	graph_dist(int n);
	void read();
};
graph_dist read_graph_dist();