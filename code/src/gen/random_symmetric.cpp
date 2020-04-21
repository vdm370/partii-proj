#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MAX = 1000;
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
        mat[j][i] = mat[i][j] = uniform_int_distribution<int>(0, MAX)(rng);
      } 
    }
  }
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      printf("%d ", mat[i][j]);
    } 
    printf("\n");
  }
  return 0;
}
