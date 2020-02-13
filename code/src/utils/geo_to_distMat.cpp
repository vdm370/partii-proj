#include <bits/stdc++.h>
using namespace std;
const double R = 6371; // the radius of the Earth
double earth_dist(pair<double, double> c1, pair<double, double> c2) {
	double phi1 = c1.first;
	double phi2 = c2.first;
	double dphi = c2.first - c1.first;
	double dlam = c2.second - c1.second;
	double a = sin(dphi / 2) * sin(dphi / 2) + cos(phi1) * cos(phi2) * sin(dlam / 2) * sin(dlam / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	return (int)(R * c);
}
int main() {
	int n;
	scanf("%d", &n);
	vector<pair<double, double>> coords(n);
	for(int i = 0; i < n; i++) {
		int cd; scanf("%d", &cd); assert(cd == i + 1);
		scanf("%lf %lf", &coords[i].first, &coords[i].second);
		coords[i].first *= M_PI / 180;
		coords[i].second *= M_PI / 180;
	}
	printf("%d\n", n);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {	
			if(i == j) printf("0 ");
			else printf("%.2f ", earth_dist(coords[i], coords[j]));
		}
		printf("\n");
	}
	return 0;
}