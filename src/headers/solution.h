#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
using namespace std;
struct solution {
	double value;
	vector<int> order;
	solution();
	solution(double, vector<int>);
	bool sane();
	void print(bool);
	bool operator <(const solution&) const;
};

#endif
