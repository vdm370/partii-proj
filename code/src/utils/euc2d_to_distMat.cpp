#include <bits/stdc++.h>
using namespace std;
double euclidean(pair<double, double> c1, pair<double, double> c2) {
	double dx = c1.first - c2.first;
  double dy = c1.second - c2.second;
  double rij = sqrt(dx * dx + dy * dy);
  return rij;
}
int main() {
	int n;
	scanf("%d", &n);
	vector<pair<double, double>> coords(n);
	for(int i = 0; i < n; i++) {
		int cd; scanf("%d", &cd); assert(cd == i + 1);
		scanf("%lf %lf", &coords[i].first, &coords[i].second);
	}
	printf("%d\n", n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(i == j) printf("0 ");
			else printf("%.2f ", euclidean(coords[i], coords[j]));
		}
		printf("\n");
	}
	return 0;
}
