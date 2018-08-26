#include <iostream>
#include <cstdio>
#include "mergesort.hpp"
#include "distance.hpp"

#define BSIZE 1<<15

char buffer[BSIZE];
int bpos = 0, bsize = 0;

using namespace std;

int readLong();

int main() {

	int N, i, j;
	int *x, *px;
	int *y, *py;
	long long int *distx, *disty;
	long long int min, temp;

	// read amount of students
	cin >> N;
	// initialise all arrays
	// x, y to keep the coordinates
	// px, py to keep the original order
	x = new int[N];
	px = new int[N];
	y = new int[N];
	py = new int[N];


	// px and py will be 0, 1, 2, ..., n - 1
	for (i = 0; i < N; i++) {

		x[i] = readLong();
		px[i] = i;
		y[i] = readLong();
		py[i] = i;

	}

	// after sorting xs and ys...
	// ...px and py will have the...
	// ...original place of each x, y
	mergesort(x, px, 0, (N - 1));
	mergesort(y, py, 0, (N - 1));

	// distx and disty are sums from all the others to one student
	distx = new long long int[N]{0};
	disty = new long long int[N]{0};

	// check calculate comments
	calculate(distx, x, px, N);
	calculate(disty, y, py, N);

	// set min for first pair
	min = distx[0] + disty[0];

	// find pair of coordinates...
	// ...with minimun sum of sums
	for (i = 1; i < N; i++) {

		temp = distx[i] + disty[i];
		if (temp < min)
			min = temp;

	}

	cout << min << endl;

	return 0;

}

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
