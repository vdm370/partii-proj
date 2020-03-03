#include "convex_hull_heuristic.h"
using namespace std;

const bool DEBUG = true;

struct point {
  int id;
  double x, y;
  point() {

  }
  void read(int _id) {
    id = _id;
    scanf("%lf %lf", &x, &y);
  }
};

inline double sqr(double a) {
  return a * a;
}

const double EPS = 1e-8;

point origin;
inline bool cmp(point o, point a, point b) {
  return atan2(a.y - o.y, a.x - o.x) < atan2(b.y - o.y, b.x - o.x);
}

inline bool cmp2(point a, point b) {
  return cmp(origin, a, b);
}

inline double ccw(point a, point b, point c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

//this function returns the IDs of the nodes in the convex hull (in order)
vector<int> convex_hull(vector<point> g) {
  int n = (int)g.size();
  g.insert(g.begin(), point());
  int min_i = 1;
  for(int i = 2; i <= n; i++) {
    if(g[i].y < g[min_i].y || (g[i].y == g[min_i].y && g[i].x < g[min_i].x)) {
      min_i = i;
    }
  }
  swap(g[1], g[min_i]);
  origin = g[1];
  sort(g.begin() + 2, g.end(), cmp2);
  g[0] = g[n];
  int hull_size = 1;
  for(int i = 2; i <= n; i++) {
    while(ccw(g[hull_size - 1], g[hull_size], g[i]) <= EPS) {
      if(hull_size > 1) {
        hull_size -= 1;
      } else if(i == n) break;
      else i++;
    }
    swap(g[++hull_size], g[i]);
  }
  vector<int> ret;
  for(int i = 1; i <= hull_size; i++) {
    ret.push_back(g[i].id);
  }
  return ret;
}

double dist(point &a, point &b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

double calculate_value(vector<point> &g, vector<int> &path) {
  double ans = 0.0;
  for(int i = 0; i + 1 < (int)path.size(); i++) {
    ans += dist(g[path[i]], g[path[i + 1]]);
  }
  ans += dist(g[path.back()], g[path[0]]);
  return ans;
}

solution convex_hull_heuristic(vector<point> g) {
  int n = (int)g.size();
  vector<int> path = convex_hull(g);
  if(DEBUG) printf("convex hull size is %d\n", (int)path.size());
  if(DEBUG) for(auto &x : path) printf("%d ", x); printf("\n");
  unordered_set<int> untaken;
  for(int i = 0; i < n; i++) {
    untaken.insert(i);
  }
  for(auto &p : path) {
    untaken.erase(untaken.find(p));
  }
  path.push_back(path[0]);
  while(!untaken.empty()) {
    if(DEBUG) printf("%d left to insert\n", (int)untaken.size());
    double best_ratio = DBL_MAX;
    int best_node = -1, best_place = -1;
    for(auto &x : untaken) {
      double min_value = DBL_MAX;
      int best_pos = -1;
      for(int i = 0; i + 1 < (int)path.size(); i++) {
        if(dist(g[path[i]], g[x]) + dist(g[x], g[path[i + 1]]) < min_value) {
          min_value = dist(g[path[i]], g[x]) + dist(g[x], g[path[i + 1]]);
          best_pos = i;
        }
      }
      double ratio_here = dist(g[path[best_pos]], g[x]) + dist(g[x], g[path[best_pos + 1]]);
      if(ratio_here < best_ratio) {
        best_ratio = ratio_here;
        best_node = x;
        best_place = best_pos;
      }
    }
    path.insert(path.begin() + best_place, best_node);
    untaken.erase(untaken.find(best_node));
  }
  path.pop_back();
  return solution(calculate_value(g, path), path);
}

vector<point> read_points() {
  int n;
  scanf("%d", &n);
  vector<point> ret(n);
  for(int i = 0; i < n; i++) {
    ret[i].read(i);
  }
  return ret;
}

int main() {
  vector<point> g = read_points();
  auto sol = convex_hull_heuristic(g);
  sol.print(true);
  return 0;
}
