#include "random.h"

using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

solution random(graph_dist g) {
  srand(time(NULL));
	const int ITERATIONS = 10000;
  vector<int> path;
  for(int i = 0; i < g.nodes; i++) {
    path.push_back(i);
  }
  shuffle(path.begin(), path.end(), rng);
  solution ans(g.get_value(path), path);
  //printf("Current sol: %.2f\n", g.get_value(path));
  for(int _ = 0; _ < ITERATIONS; _++) {
    shuffle(path.begin(), path.end(), rng);
    solution tmp(g.get_value(path), path);
    //printf("Trying sol: %.2f\n", g.get_value(path));
    if(tmp < ans) ans = tmp;
  }
  return ans;
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
	solution s = random(g);
	s.print(true);
	return 0;
}
