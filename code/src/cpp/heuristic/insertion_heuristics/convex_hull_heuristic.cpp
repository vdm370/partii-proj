#include "convex_hull_heuristic.h"
using namespace std;

using namespace std::chrono;
const bool DEBUG = true;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct point {
  int id;
  double x, y;
  point() {

  }
  void read(int _id) {
    id = _id;
    int xx;
    scanf("%d %lf %lf", &xx, &x, &y);
    assert(xx == _id + 1);
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

inline double insert_cost(vector<point> &g, int i, int j, int k) {
  return dist(g[i], g[j]) + dist(g[j], g[k]) - dist(g[i], g[k]);
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
  vector<int> untaken;
  unordered_set<int> ch;
  for(auto &p : path) ch.insert(p);
  for(int i = 0; i < n; i++) {
    if(!ch.count(i)) untaken.push_back(i);
  }
  path.push_back(path[0]);
  while(!untaken.empty()) {
    if(DEBUG) printf("%d left to insert\n", (int)untaken.size());
    //I need to chose one of untaken, randomly
    int idx = uniform_int_distribution<int>(0, (int)untaken.size() - 1)(rng);
    int node = untaken[idx];
    untaken.erase(untaken.begin() + idx);
    int best_place = 0;
    double best_cost = insert_cost(g, path[0], node, path[1]);
    for(int i = 1; i < (int)path.size() - 1; i++) {
      double cost_here = insert_cost(g, path[i], node, path[i + 1]);
      if(cost_here < best_cost) {
        best_cost = cost_here;
        best_place = i;
      }
    }
    path.insert(path.begin() + best_place + 1, node);
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

solution convex_times(int tm, vector<point> &g) {
  tm -= 1;
  solution best = convex_hull_heuristic(g);
  while(tm >= 1) {
    best = min(best, convex_hull_heuristic(g));
    tm -= 1;
  }
  return best;
}

int main() {
  vector<point> g = read_points();
  printf("points: %d\n", g.size());
  auto start = high_resolution_clock::now(); 
  auto sol = convex_times((int)g.size(), g);
  auto end = high_resolution_clock::now();
  sol.print(true);
  cout << "The computation has taken " << (duration_cast<milliseconds>(end - start)).count() << "ms" << endl;
  return 0;
}
