#include <vector>
using namespace std;
struct graph_dist {
	vector<vector<double>> dist;
	int nodes;
	graph_dist();
	graph_dist(int);
	void print();
	double get_value(vector<int>);
	void read();
};
graph_dist read_graph_dist();