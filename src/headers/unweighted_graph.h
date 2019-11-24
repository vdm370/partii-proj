#include <bits/stdc++.h>
using namespace std;
struct unweighted_graph {
	int nodes;
	vector<vector<int>> adj;
	unweighted_graph(int);
	unweighted_graph();
	void add_edge(int, int);
	void read();
};

unweighted_graph read_unweighted_graph();