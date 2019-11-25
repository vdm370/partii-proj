#include <vector>
using namespace std;
struct solution {
	double value;
	vector<int> order;
	solution();
	solution(double, vector<int>);
	void print(bool);
	bool operator <(const solution&) const;
};