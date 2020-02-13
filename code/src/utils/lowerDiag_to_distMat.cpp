#include <bits/stdc++.h>
using namespace std;
int main() {
	int n;
	scanf("%d", &n);
	vector<vector<double>> dist(n);
	for(int i = 0; i < n; i++) {
		dist[i].resize(n);
		for(int j = 0; j <= i; j++) {
			scanf("%lf", &dist[i][j]);
			dist[j][i] = dist[i][j];
		}
	}
	printf("%d\n", n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			printf("%.2f ", dist[i][j]);
		}
		printf("\n");
	}
	return 0;
}