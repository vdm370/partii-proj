#include <vector>
using namespace std;
struct weighted_graph {
	int nodes;
	vector<vector<pair<int, double>>> adj;
	weighted_graph(int);
	weighted_graph();
	void add_edge(int, int, double);
	void read();
};

weighted_graph read_weighted_graph();