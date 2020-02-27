#include "ant_colony.h"
#include "greedy.h"
#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

/*
1. ABC
2. A'BC
3. ABC'
4. A'BC'
5. A'B'C
6. AB'C
7. AB'C'
8. A'B'C'
*/
vector<pair<double, int>> costs(int A, int B, int C, int D, int E, int F, graph_dist &g) {
  vector<pair<double, int>> ret;
  ret.push_back({0, 1});
  ret.push_back({g.dist[A][B] + g.dist[E][F] - g.dist[B][F] - g.dist[A][E], 2});
  ret.push_back({g.dist[C][D] + g.dist[E][F] - g.dist[D][F] - g.dist[C][E], 3});
  ret.push_back({g.dist[A][B] + g.dist[C][D] + g.dist[E][F] - g.dist[A][D] - g.dist[B][F] - g.dist[E][C], 4});
  ret.push_back({g.dist[A][B] + g.dist[C][D] + g.dist[E][F] - g.dist[C][F] - g.dist[B][D] - g.dist[E][A], 5});
  ret.push_back({g.dist[B][A] + g.dist[D][C] - g.dist[C][A] - g.dist[B][D], 6});
  ret.push_back({g.dist[A][B] + g.dist[C][D] + g.dist[E][F] - g.dist[B][E] - g.dist[D][F] - g.dist[C][A], 7});
  ret.push_back({g.dist[A][B] + g.dist[C][D] + g.dist[E][F] - g.dist[A][D] - g.dist[C][F] - g.dist[B][E], 8});
  return ret;
}

void concat(vector<int> &a, vector<int> &b) {
  a.insert(a.end(), b.begin(), b.end());
}

void adapt(int n, vector<int> &path, int a, int b, int c, int type) {
  vector<int> first_seg, second_seg, third_seg;
  if(c + 1 >= n - 1) {
    first_seg = vector<int>(path.begin() + (c + 2) % n, path.begin() + a + 1);
  } else {
    first_seg = vector<int>(path.begin() + c + 1, path.end());
  }
  second_seg = vector<int>(path.begin() + a + 1, path.begin() + b + 1);
  third_seg = vector<int>(path.begin() + b + 1, path.begin() + c + 1);
  switch(type) {
    case 1:
      break;
    case 2:
      reverse(first_seg.begin(), first_seg.end());
      path.clear();
      concat(path, first_seg);
      concat(path, second_seg);
      concat(path, third_seg);
      break;
    case 3:
        reverse(third_seg.begin(), third_seg.end());
        path.clear();
        concat(path, first_seg);
        concat(path, second_seg);
        concat(path, third_seg);
        break;
    case 4:
      reverse(first_seg.begin(), first_seg.end());
      reverse(third_seg.begin(), third_seg.end());
      path.clear();
      concat(path, first_seg);
      concat(path, second_seg);
      concat(path, third_seg);
      break;
    case 5:
      reverse(first_seg.begin(), first_seg.end());
      reverse(second_seg.begin(), second_seg.end());
      path.clear();
      concat(path, first_seg);
      concat(path, second_seg);
      concat(path, third_seg);
      break;
    case 6:
      reverse(second_seg.begin(), second_seg.end());
      path.clear();
      concat(path, first_seg);
      concat(path, second_seg);
      concat(path, third_seg);
      break;
    case 7:
      reverse(second_seg.begin(), second_seg.end());
      reverse(third_seg.begin(), third_seg.end());
      path.clear();
      concat(path, first_seg);
      concat(path, second_seg);
      concat(path, third_seg);
      break;
    case 8:
      reverse(first_seg.begin(), first_seg.end());
      reverse(second_seg.begin(), second_seg.end());
      reverse(third_seg.begin(), third_seg.end());
      path.clear();
      concat(path, first_seg);
      concat(path, second_seg);
      concat(path, third_seg);
      break;
    default:
      assert(false);
      break;
  }
}

void sort3(int &a, int &b, int &c) {
    if(b < a) swap(a, b);
    if(c < a) swap(a, c);
    if(c < b) swap(b, c);
}

bool opt3_improve(solution &sol, graph_dist &g) {
  int n = g.nodes;
  int a, b, c;
  do {
    a = uniform_int_distribution<int>(0, n - 1)(rng);
    b = uniform_int_distribution<int>(0, n - 1)(rng);
    c = uniform_int_distribution<int>(0, n - 1)(rng);
    sort3(a, b, c);
  } while(abs((a - b) % (n - 1)) <= 1 || abs((a - c) % (n - 1)) <= 1 || abs((b - c) % (n - 1)) <= 1);
  int A = sol.order[a];
  int B = sol.order[(a + 1) == n ? 0 : (a + 1)];
  int C = sol.order[b];
  int D = sol.order[(b + 1) == n ? 0 : (b + 1)];
  int E = sol.order[c];
  int F = sol.order[(c + 1) == n ? 0 : (c + 1)];
  auto perturbs = costs(A, B, C, D, E, F, g);
  int best = max_element(perturbs.begin(), perturbs.end()) - perturbs.begin();
  double improvement = perturbs[best].first;
  if(abs(improvement) < 1e-6) return false;
  sol.value -= improvement;
  adapt(n, sol.order, a, b, c, perturbs[best].second);
  sol.print(true);
  assert(sol.sane(g));
  return true;
}

solution threeopt(graph_dist g) {
  solution sol = greedy(g);
  puts("printing greedy");
  sol.print(true);
  const int ITERATIONS = 100000;
  for(int _iteration = 0; _iteration < ITERATIONS; _iteration++) {
    opt3_improve(sol, g);
  }
  return sol;
}

int main() {
	graph_dist g = read_graph_dist();
	g.print();
	solution s = threeopt(g);
	s.print(true);
	return 0;
}
