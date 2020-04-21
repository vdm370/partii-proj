#include "dyn_prog.h"
#include <float.h>
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// I will use the approach with the memoization
// Here, I assume N <= 22 for example

const int N = 22;
pair<double, int> dp[N][1 << N];

vector<int> reconstruct(int node, int mask, int steps) {
	vector<int> ans;
	ans.push_back(node);
	for(int i = 0; i < steps; i++) {
		int new_node = dp[node][mask].second;
		int new_mask = mask ^ (1 << node);
		node = new_node;
		mask = new_mask;
		ans.push_back(node);
	}
	reverse(ans.begin(), ans.end());
	return ans;
}
solution dyn_prog(graph_dist g) {
	const int max_mask = 1 << g.nodes;
	for(int mask = 1; mask < max_mask; mask++) {
		for(int node = 0; node < g.nodes; node++) {
			dp[node][mask] = {DBL_MAX, -1};
			if((mask & (1 << node)) == 0) continue;
			if(mask == (1 << node)) {
				if(node == 0) dp[node][mask] = {0, -1};
				continue;
			}
			//this mask contains this node
			for(int prev_node = 0; prev_node < g.nodes; prev_node++) {
				if(prev_node == node) continue;
				if((mask & (1 << prev_node)) == 0) continue;
				double val_here = g.dist[prev_node][node] + dp[prev_node][mask ^ (1 << node)].first;
				if(val_here < dp[node][mask].first) {
					dp[node][mask].first = val_here;
					dp[node][mask].second = prev_node;
				}
			}
			//printf("dp[%d][%d] = %.2f, %d\n", node, mask, dp[node][mask].first, dp[node][mask].second);
		}
	}
	double best = DBL_MAX;
	int best_ind = -1;
	for(int i = 1; i < g.nodes; i++) {
		//printf("node: %d, dist1: %.2f, dist2: %.2f\n", i, dp[i][max_mask - 1].first, g.dist[i][0]);
		if(dp[i][max_mask - 1].first + g.dist[i][0] < best) {
			best = dp[i][max_mask - 1].first + g.dist[i][0];
			best_ind = i;
		}
	}
	double ans_value = best;
	vector<int> ind = reconstruct(best_ind, max_mask - 1, g.nodes - 1);
	printf("%.2f\n", g.get_value(ind));
	return solution(ans_value, ind);
}

int main() {
	graph_dist g = read_graph_dist();
	printf("%d\n", g.nodes);
	for(int i = 0; i < g.nodes; i++) {
		for(int j = 0; j < g.nodes; j++) {
			printf("%.2f ", g.dist[i][j]);
		}
		printf("\n");
	}
	auto start = high_resolution_clock::now(); 
	solution s = dyn_prog(g);
	auto end = high_resolution_clock::now(); 
	cout << "The computation has taken " << (duration_cast<milliseconds>(end - start)).count() << "ms" << endl;
	s.print(true);
	return 0;
}
