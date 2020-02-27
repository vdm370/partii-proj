#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "graph_dist.h"
using namespace std;
struct solution {
	double value;
	vector<int> order;
	solution();
	solution(double, vector<int>);
	bool sane(graph_dist &g);
	void print(bool);
	bool operator <(const solution&) const;
};

#endif
