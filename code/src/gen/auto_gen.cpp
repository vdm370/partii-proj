#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MAX = 1000000;
int main(int argc, char *argv[]) {
  assert(argc == 2);
  int n;
  sscanf(argv[1], "%d", &n);
  printf("%d\n", n);
  vector<vector<int>> mat(n);
  for(int i = 0; i < n; i++) {
    mat[i].resize(n);
  }
  for(int i = 0; i < n; i++) {
    for(int j = 0; j <= i; j++) {
      if(j == i) mat[i][j] = 0;
      else {
        mat[j][i] = mat[i][j] = uniform_int_distribution<int>(MAX / 10, MAX)(rng);
      } 
    }
  }
  vector<int> perm;
  for(int i = 0; i < n; i++) perm.push_back(i);
  shuffle(perm.begin(), perm.end(), rng);
  for(int i = 0; i + 1 < n; i++) {
    mat[perm[i]][perm[i + 1]] = mat[perm[i + 1]][perm[i]] = 3;
  }
  mat[perm.back()][perm[0]] = mat[perm[0]][perm.back()] = 3;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      printf("%d ", mat[i][j]);
    } 
    printf("\n");
  }
  return 0;
}
