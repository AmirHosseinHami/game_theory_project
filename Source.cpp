
#include <iostream>
using namespace std;
#include <stdlib.h>
#include <algorithm>

struct Point {

	int x;//profit of first player in this point
	int y;//profit of second player in this point
	string strX;//name of strategy of first player in this point
	string strY;//name of strategy of second player in this point

	bool operator<(Point p){
		return x < p.x || (x == p.x && y < p.y);
	}
};

int cross_product(Point O, Point A, Point B){
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

Point* convex_hull(Point* arr, int arrPointsSize,int* ansSize){
	int k = 0;
	if (arrPointsSize <= 3) {
		(*ansSize) = arrPointsSize;
		return arr;
	}
	Point* ans = new Point[2 * arrPointsSize];
	sort(arr, arr+ arrPointsSize);
	for (int i = 0; i < arrPointsSize; ++i) {
		while (k >= 2 && cross_product(ans[k - 2], ans[k - 1], arr[i]) <= 0){
			k--;
	    }
		ans[k++] = arr[i];
	}
	for (int i = arrPointsSize - 1, t = k + 1; i > 0; --i) {
		while (k >= t && cross_product(ans[k - 2], ans[k - 1], arr[i - 1]) <= 0){
			k--;
	    }
		ans[k++] = arr[i - 1];
	}
	(*ansSize) = k - 1;//storing number of points of convexhull(size of hte array)
	return ans;
}

int main() {
	
	int numOfFirstPlayerStrs, numOfSecPlayerStrs;//number of player s strategies
	cout << "number of first player strategies: ";
	cin >> numOfFirstPlayerStrs;
	cout << "number of second player strategies: ";
	cin >> numOfSecPlayerStrs;
	string* strsOfFirstPlayer = new string[numOfFirstPlayerStrs];
	string* strsOfSecPlayer = new string[numOfSecPlayerStrs];
	cout << "\n\n";
	for (int i = 0; i < numOfFirstPlayerStrs; i++) {
		cout << "name of " << i+1 << "th strategy of first player: ";
		cin >> strsOfFirstPlayer[i];
	}
	cout << "\n";
	for (int i = 0; i < numOfSecPlayerStrs; i++) {
		cout << "name of " << i + 1 << "th strategy of second player: ";
		cin >> strsOfSecPlayer[i];
	}
	cout << "\n\n";
	int arrPointsSize = numOfFirstPlayerStrs * numOfSecPlayerStrs;
	Point* arrPoints = new Point[arrPointsSize];//array of profits of two players that
	// actually is an array of points with two coordinates
	Point* arrPointsTemp = new Point[arrPointsSize];
	cout << "*****(first player strategy,second player strategy)*****\n";
	for (int i = 0; i < numOfFirstPlayerStrs; i++) {
		for (int j = 0; j < numOfSecPlayerStrs; j++) {
			arrPoints[i * numOfSecPlayerStrs + j].strX = strsOfFirstPlayer[i];
			arrPoints[i * numOfSecPlayerStrs + j].strY = strsOfSecPlayer[j];
			cout << "(" << strsOfFirstPlayer[i] << "," << strsOfSecPlayer[j] << "):\n";
			cout << "   profit of first palyer: ";
			cin >> arrPoints[i * numOfSecPlayerStrs + j].x;
			cout << "   profit of second palyer: ";
			cin >> arrPoints[i * numOfSecPlayerStrs + j].y;
		}
	}

		int cnt = 0;
		int tempIndex = 0;
		for (int i = 0; i < arrPointsSize; i++) {
			for (int j = i - 1; j >= 0; j--) {
				if (arrPoints[i].x == arrPoints[j].x && arrPoints[i].y == arrPoints[j].y) {
					cnt++;
				}
			}
			if (!cnt) {
				arrPointsTemp[tempIndex].x = arrPoints[i].x;
				arrPointsTemp[tempIndex].y = arrPoints[i].y;
				arrPointsTemp[tempIndex].strX = arrPoints[i].strX;
				arrPointsTemp[tempIndex].strY = arrPoints[i].strY;
				tempIndex++;
			}
			cnt = 0;
		}
		arrPointsSize = tempIndex;
		for (int i = 0; i < arrPointsSize; i++) {
			arrPoints[i].x = arrPointsTemp[i].x;
			arrPoints[i].y = arrPointsTemp[i].y;
			arrPoints[i].strY = arrPointsTemp[i].strY;
			arrPoints[i].strX = arrPointsTemp[i].strX;
		}

		if (arrPointsSize == 1) {
			cout << "\n\n";
			cout << "convex hull and pareto optimal point is : (" << arrPoints[0].x << "," << arrPoints[0].y << ")";
		}
		else {

			system("cls");
			int convexHullSize=0;
			Point* convexHull = convex_hull(arrPoints, arrPointsSize, &convexHullSize);
			cout << "\n\n";
			cout << "vertices of convex hull are as followed(counter clockwise ordered(if there are more than three)):\n";
			for (int i = 0; i < convexHullSize; i++) {
				cout << "(" << convexHull[i].x << "," << convexHull[i].y << ")\n";
			}
			cout << "\n\n";
				Point maxX;
				int maxXIndex;
				maxX.x = -2147483647;
				Point maxY;
				int maxYIndex;
				maxY.y = -2147483647;
				for (int i = 0; i < convexHullSize; i++) {
					if (convexHull[i].x > maxX.x) {
						maxX.x = convexHull[i].x;
						maxX.y = convexHull[i].y;
						maxX.strX = convexHull[i].strX;
						maxX.strY = convexHull[i].strY;
						maxXIndex = i;
					}
					else if (convexHull[i].x == maxX.x) {
						if (convexHull[i].y > maxX.y) {
							maxX.x = convexHull[i].x;
							maxX.y = convexHull[i].y;
							maxX.strX = convexHull[i].strX;
							maxX.strY = convexHull[i].strY;
							maxXIndex = i;
						}
					}

					if (convexHull[i].y > maxY.y) {
						maxY.x = convexHull[i].x;
						maxY.y = convexHull[i].y;
						maxY.strX = convexHull[i].strX;
						maxY.strY = convexHull[i].strY;
						maxYIndex = i;
					}
					else if (convexHull[i].y == maxY.y) {
						if (convexHull[i].x > maxY.x) {
							maxY.x = convexHull[i].x;
							maxY.y = convexHull[i].y;
							maxY.strX = convexHull[i].strX;
							maxY.strY = convexHull[i].strY;
							maxYIndex = i;
						}
					}
				}

				if (arrPointsSize == 2) {
					if (maxXIndex == maxYIndex) {
						cout << "the only pareto optimal point is: (" << convexHull[maxXIndex].x << "," << convexHull[maxXIndex].y << ")\n";
						//cout<<"which is the profile strategy: ("<< convexHull[maxXIndex].strX << "," << convexHull[maxXIndex].strY << ")\n";
					}
					else {
						cout << "pareto optimal points are all points on this line:\n";	
						cout << "line segment with two ending points:\n";
						cout << "(" << convexHull[0].x << "," << convexHull[0].y << ")\n";
						cout << "(" << convexHull[1].x << "," << convexHull[1].y << ")\n";
					}
				}
				else if (arrPointsSize == 3) {
					if (maxXIndex == maxYIndex) {
						cout << "the only pareto optimal point is: (" << convexHull[maxXIndex].x << "," << convexHull[maxXIndex].y << ")\n";
						//cout<<"which is the profile strategy: ("<< convexHull[maxXIndex].strX << "," << convexHull[maxXIndex].strY << ")\n";
					}
					else {
						int minIndex;
						int maxIndex;
						if (maxXIndex < maxYIndex) {
							minIndex = maxXIndex;
							maxIndex = maxYIndex;
						}
						else {
							minIndex = maxYIndex;
							maxIndex = maxXIndex;
						}
						int med = 0;
						if (minIndex == med) {
							med++;
						}
						if (maxIndex == med) {
							med++;
						}
						if ((convexHull[med].x<convexHull[minIndex].x && convexHull[med].x>convexHull[maxIndex].x)
							|| (convexHull[med].x > convexHull[minIndex].x && convexHull[med].x < convexHull[maxIndex].x)) {
							cout << "pareto optimal points are all points on these line(s):\n";
							cout << "line segment with two ending points:\n";
							cout << "(" << convexHull[minIndex].x << "," << convexHull[minIndex].y << ")\n";
							cout << "(" << convexHull[med].x << "," << convexHull[med].y << ")\n";
							cout << "line segment with two ending points:\n";
							cout << "(" << convexHull[med].x << "," << convexHull[med].y << ")\n";
							cout << "(" << convexHull[maxIndex].x << "," << convexHull[maxIndex].y << ")\n";
						}
						else{
							cout << "pareto optimal points are all points on this line:\n";
							cout << "line segment with two ending points:\n";
							cout << "(" << convexHull[minIndex].x << "," << convexHull[minIndex].y << ")\n";
							cout << "(" << convexHull[maxIndex].x << "," << convexHull[maxIndex].y << ")\n";
						}
					}
				}
				else {
					if (maxXIndex == maxYIndex) {
						cout << "the only pareto optimal point is: (" << convexHull[maxXIndex].x << "," << convexHull[maxXIndex].y << ")\n";
						//cout<<"which is the profile strategy: ("<< convexHull[maxXIndex].strX << "," << convexHull[maxXIndex].strY << ")\n";
					}
					else {
						cout << "pareto optimal points are all points on these line(s):\n";
						for (int i = maxXIndex; i < maxYIndex; i++) {
							cout << "line segment with two ending points:\n";
							cout << "(" << convexHull[i].x << "," << convexHull[i].y << ")\n";
							cout << "(" << convexHull[i + 1].x << "," << convexHull[i + 1].y << ")\n";
						}
					}
				}
		}
}