#include <iostream>
#include <string.h>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

#define BSIZE 1<<15

char buffer[BSIZE];
int bpos = 0, bsize = 0;

using namespace std;

int readLong() {
	int d = 0, x = 0;
	char c;
	while (1)  {
		if (bpos >= bsize) {
			bpos = 0;
			if (feof(stdin)) return x;
			bsize = fread(buffer, 1, BSIZE, stdin);
		}
		c = buffer[bpos++];
		if (c >= '0' && c <= '9') {
			x = x*10 + (c-'0');
			d = 1;
		} else if (d == 1) return x;
	}
	return -1;
}

struct dist {
	int x;
	int y;
	long long int dist_x;
	long long int dist_y;
};
bool compareByX(const struct dist& a, const struct dist& b)
{
	return a.x < b.x;
}
bool compareByY(const struct dist& a, const struct dist& b)
{	return a.y < b.y;
}
int main() {

	int n, i, k, l;
	n = readLong();
	vector<dist> distances;
	for (i = 0; i <= n - 1; i++) {
		distances.push_back(dist());
		distances[i].x = readLong();
		distances[i].y = readLong();

	}
	sort(distances.begin(), distances.end(), compareByX);
	long long int A = 0;
	for (i = 1; i <= n - 1; i++ ) {
		A = A + abs(distances[0].x - distances[i].x);
	}
	distances[0].dist_x = A ;
	for (i = 1; i <= n - 1; i++) {
		distances[i].dist_x = (distances[i-1].dist_x + (2*i  - n) * (distances[i].x - distances[i - 1].x));

	}
	sort(distances.begin(), distances.end(), compareByY);
	A = 0;
	for (i = 1; i <= n - 1; i++ ) {
		A = A + abs(distances[0].y - distances[i].y);
	}
	distances[0].dist_y = A ;
	for (i = 1; i <= n - 1; i++ ) {
		distances[i].dist_y = distances[i - 1].dist_y + (2*i - n) * (distances[i].y - distances[i - 1].y);
	}
	long long int min_distance = distances[0].dist_x + distances[0].dist_y;
	for  (i = 1; i <= n - 1; i++) {
		long long int b = distances[i].dist_x + distances[i].dist_y;
		if (b < min_distance) { min_distance = b ; }
	}
	cout << min_distance ;
	return 0;
}
