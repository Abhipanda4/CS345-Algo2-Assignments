#include<LEDA/geo/point.h>
#include<LEDA/geo/circle.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<limits.h>
#include<ctime>

using namespace std;
using namespace leda;

leda::circle _2pointsKnown(std::vector<point> pointList, int idx, point p1, point p2) {
	// returns a circle with p1 and p2 on it
	// and containing all points in pointList upto idx

	// TODO: Take a random shuffle of the input array
	circle C(midpoint(p1, p2), p1);
	int i;
	for (i = 0; i < idx; i++) {
		if (C.outside(pointList[i])) {
			// create a circle that passes through all p1, p2 and pointList[i]
			// if collinear, then simply pass it through pointList[i] and
			// further among p1 and p2.
			circle temp(p1, p2, pointList[i]);
			C = temp;
		}
	}
	return C;
}

leda::circle _1pointKnown(std::vector<point> pointList, int idx, point p1) {
	// returns a circle covering all the points in the pointList
	// upta idx such that p1 lies on the circle
	
	// TODO: Take a random shuffle of the input array
	point center = midpoint(p1, pointList[0]);
	circle C(center, p1);
	int i;
	for (i = 1; i < idx; i++) {
		if (C.outside(pointList[i]) && C.radius() != 0)
			C = _2pointsKnown(pointList, i, p1, pointList[i]);
	}
	return C;
}

leda::circle findEnclosure_linear(std::vector<point> pointList) {
	int len = pointList.size();
	int i;
	point center = midpoint(pointList[0], pointList[1]);
	circle C(center, pointList[0]);
	for (i = 2; i < len; i++) {
		if (C.outside(pointList[i]) && C.radius() != 0)
			C = _1pointKnown(pointList, i, pointList[i]);
	}
	return C;
}

int main(int argc,char* argv[]) {
	int n;
	cin >> n;
	int l = n;
	std::vector<point> coords;
	while(n--) {
		double x, y;
		cin >> x;
		cin >> y;
		point p(x,y);
		coords.push_back(p);
	}
	clock_t begin = clock();
	circle ans = findEnclosure_linear(coords);
	clock_t end = clock();
	double elapsed_sec = double(end - begin) / CLOCKS_PER_SEC;
	//cout << l << "," << elapsed_sec << endl;
	cout << ans.center() << endl;
	cout << ans.radius() << endl;
	return 0;
}
