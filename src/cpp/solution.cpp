#include "solution.h"
solution::solution() {
	value = DBL_MAX;
}
solution::solution(double val, vector<int> ind) {
	value = val;
	order = ind;
}
void solution::print(bool path) {
	printf("Solved the TSP with: %.2f\n", value);
	if(path) {
		for(int i = 0; i < (int)order.size(); i++) {
			if(i + 1 == (int)order.size()) printf("%d\n", order[i]);
			else printf("%d ", order[i]);
		}
	}
}