#include "branch_and_bound.h"

const int ROOT = 0;
const double INF = std::numeric_limits<double>::infinity();

struct bb_node {
  vector<int> cur_path;
  double cost;
  vector<vector<double>> g;
  bb_node(vector<int> _cur_path, double _cost, vector<vector<double>> _g) {
    cur_path = _cur_path;
    cost = _cost;
    g = _g;
  }
  bool operator <(const bb_node &other) const {
    if(cost == other.cost) return cur_path.size() > other.cur_path.size();
    else return cost < other.cost;
  }
};

double reduce(vector<vector<double>> &g) {
  double ret = 0.0;
  int n = (int)g.size();
  for(int i = 0; i < n; i++) {
    double mn = INF;
    for(int j = 0; j < n; j++) {
      mn = min(mn, g[i][j]);
    }
    if(mn == INF) continue;
    ret += mn;
    if(mn > 0) {
      for(int j = 0; j < n; j++) {
        g[i][j] -= mn;
      }
    }
  }
  for(int j = 0; j < n; j++) {
    double mn = INF;
    for(int i = 0; i < n; i++) {
      mn = min(mn, g[i][j]);
    }
    if(mn == INF) continue;
    ret += mn;
    if(mn > 0) {
      for(int i = 0; i < n; i++) {
        g[i][j] -= mn;
      }
    }
  }
  return ret;
}

void inf_row(vector<vector<double>> &m, int row_idx) {
  int n = (int)m.size();
  for(int i = 0; i < n; i++) {
    m[row_idx][i] = INF;
  }
}

void inf_col(vector<vector<double>> &m, int col_idx) {
  int n = (int)m.size();
  for(int i = 0; i < n; i++) {
    m[i][col_idx] = INF;
  }
}

solution branch_and_bound(graph_dist g) {
  int n = g.nodes;
  double ans = INF;
  vector<int> ans_path;
  priority_queue<bb_node> que;
  vector<vector<double>> start_g = g.dist;
  double val = reduce(start_g);
  while(!que.empty() && que.top().cost < upper_bound) {
    bb_node cur = que.top();
    que.pop();
    if((int)cur.cur_path.size() == n) {
      //this is a leaf
      ans = cur.cost;
      ans_path = cur.cur_path;
    } else {
      vector<bool> exist(n, false);
      for(auto &x : cur.cur_path) exist[x] = true;
      for(int nn = 0; nn < n; i++) {
        if(!exist[nn]) {
          //we need to create a new node here
          vector<int> new_path = cur.cur_path;
          new_path.push_back(nn);
          vector<vector<double>> g_mat = cur.g;
          inf_row(g_mat, cur.cur_path.back());
          inf_col(g_mat, nn);
          g_mat[nn][cur.cur_path.back()] = INF;
          double val = reduce(g_mat);
          double new_cost = cur.cost + cur.g[cur.cur_path.back()][nn];
          bb_node ins(new_cost, new_path, g_mat);
          que.push(ins);
        }
      }
    }
    return solution(ans, ans_path);
  }
}

int main() {
	graph_dist g = read_graph_dist();
	g.print();
	solution s = branch_and_bound(g);
	s.print(true);
	return 0;
}
