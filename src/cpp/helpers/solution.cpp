#include "solution.h"
#include <float.h>
solution::solution() {
	value = DBL_MAX;
}
solution::solution(double val, vector<int> ind) {
	value = val;
	order = ind;
}
bool solution::operator<(const solution &other) const {
	return value < other.value;
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