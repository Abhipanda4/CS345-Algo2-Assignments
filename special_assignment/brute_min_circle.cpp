#include <LEDA/geo/point.h>
#include <LEDA/geo/circle.h>
#include <iostream>
#include <vector>
#include <limits.h>
#include <ctime>

using namespace std;
using namespace leda;

leda::circle findEnclosure(std::vector<point> pointList) {
	// Function to return the center of the minimum radius circle
	// formed by taking any 3 or 2 points at a time
	int len = pointList.size();
	int i, j, k, curr;
	float min_till_now = (float)INT_MAX - 1;
	circle res(0, 0, 0);
	circle candidate(0,0,(double)INT_MAX);
	for (i = 0; i < len; i++) {
		for (j = i + 1; j < len; j++) {
			for (k = j; k < len; k++) {
				bool found = true;
				if (!collinear(pointList[i], pointList[j], pointList[k])) {
					// 3 non collinear points define the circle
					circle temp(pointList[i], pointList[j], pointList[k]);
					candidate = temp;
				} else {
					// points are collinear
					// sufficient to check for 2 point circles
					//
					if (j == k) {
						point center = midpoint(pointList[i], pointList[j]);
						circle temp(center, pointList[i]);
						candidate = temp;
					}
				}
				// check if the circle encloses all points
				for (curr = 0; curr < len; curr++) {
					if (candidate.outside(pointList[curr])) {
						found = false;
						break;
					}
				}

				// if encloses, compare with the min_radius circle till now
				if (found) {
					if (candidate.radius() < min_till_now) {
						res = candidate;
						min_till_now = candidate.radius();
					}
				}
			}
		}
	}
	return res;
}

int main(int argc,char* argv[]) {
	int n;
	cin >> n;
	int l = n;
	std::vector<point> coords;
	while(n--) {
		float x, y;
		cin >> x;
		cin >> y;
		point p(x,y);
		coords.push_back(p);
	}
	clock_t begin = clock();
	circle ans = findEnclosure(coords);
	clock_t end = clock();
	double elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;
	//cout << l << "," << elapsed_time << endl;
	cout << ans.center() << endl;
	cout << ans.radius() << endl;
	return 0;
}
