#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

#define BSIZE 1<<15

char buffer[BSIZE];
int bpos = 0, bsize = 0;

using namespace std;

class Pair {

public:

	int value, index;

	bool operator < (const Pair &other) const {

		return (value < other.value);

	}

};

void calculate(long long int[], vector<Pair>&, int);
int readLong();

int main() {

	int size, i, j;
	long long int min, temp;
	long long int *distx, *disty;

	// read amount of students
	cin >> size;

	// initialise all arrays
	// xs, ys to keep the coordinates
	// and the original order
	vector<Pair> xs(size);
	vector<Pair> ys(size);

	// order will be 0, 1, 2, ..., n - 1
	for (i = 0; i < size; i++) {

		xs[i].value = readLong();
		xs[i].index = i;
		ys[i].value = readLong();
		ys[i].index = i;

	}

	sort(xs.begin(), xs.end());
	sort(ys.begin(), ys.end());

	// distx and disty are sums from all the others to one student
	distx = new long long int[size]{0};
	disty = new long long int[size]{0};

	// check calculate comments
	calculate(distx, xs, size);
	calculate(disty, ys, size);

	// set min for first Pair
	min = distx[0] + disty[0];

	// find Pair of coordinates...
	// ...with minimun sum of sums
	for (i = 1; i < size; i++) {

		temp = distx[i] + disty[i];
		if (temp < min)
			min = temp;

	}

	cout << min << endl;

	return 0;

}

/*
 *	A function to find for each i the sum of distances of all other js.
 *	Important note: in distance array we use coordinate[i].index as index. This is done in
 *					order to be able to match the sums of xs and the sums of ys
 *					to their corresponding pair coordinate. For example in sorted
 *					arrays 1st Pair is in xs[3] and ys[7]. However xs[3].index is 1 and
 *					ys[7],index is also 1. So distx[1] and disty[1] are the same Pair.
 * 	To calculate the sum we use an easy to extract formula. As the values are sorted
 * 	we find the first sum which is the sum of the distances of all the others to this.
 *	After that it is easy to find the sum of the distances of the next one to all the
 *	others. We just need to add the distance between the last two values as many times
 *	as the amount of previous values, as well as subtract that distance the remaining
 *	times.
 *
 *	@param distance The sums for each index
 *	@param coordinate The value of each index
 *	@param Pair The initial index of the values
 *	@param size The size of the array
 *
 *	Complexity: O(n)
 */
void calculate(long long int distance[], vector<Pair> &coordinate, int size) {

	int i;

	for (i = 0; i < size; i++)
		distance[coordinate[0].index] += coordinate[i].value - coordinate[0].value;

	/*
	 *	So we have Sum(i + 1) = Sum(i) + i*(c[i + 1] - c[i]) - (size - i)(c[i + 1] - c[i]).
	 *	However the above is true when i starts from 1.
	 *	In cpp arrays i starts from 0 so in arrays we keep convert i to i - 1 but outside we keep i.
	 *	Basically the i in i*(...) and (n - i)*(...) keeps track of how many coordinates...
	 * 	...there have been before the current.
	 *	So it becomes Sum(i) = Sum(i - 1) + i * (...) - (n - i) * (...) ==>
	 * 	==> Sum(i) = Sum(i - 1) + (2 * i - n) * (...)
	 */
	for (i = 1; i < size; i++)
		distance[coordinate[i].index] = distance[coordinate[i - 1].index] + (2 * i - size) * (coordinate[i].value - coordinate[i - 1].value);

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
