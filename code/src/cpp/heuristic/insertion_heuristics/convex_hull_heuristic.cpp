#include "convex_hull_heuristic.h"
using namespace std;

solution convex_hull_heuristic(graph_dist g) {
  vector<int> path = convex_hull(g);
}

struct point {
  double x, y;
};

vector<point> read_points() {
  
}

int main() {
  vector<point> g = read_points();
  auto sol = convex_hull_heuristic(g);
  sol.print(true);
  return 0;
}
