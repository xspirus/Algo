#include <iostream>

using namespace std;

void merge(int[], int[], int, int, int);
void mergesort(int[], int[], int, int);
void calculate(long long int[], int[], int[], int);

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

		cin >> x[i];
		px[i] = i;
		cin >> y[i];
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

void merge(int a[], int p[], int l, int m, int r) {

	int b[r - l + 1], ptemp[r - l + 1];
	int i = l, j = m + 1, k = 0;

	while (i <= m && j <= r) {

		if (a[i] < a[j]) {

			ptemp[k] = p[i];
			b[k++] = a[i++];

		} else {

			ptemp[k] = p[j];
			b[k++] = a[j++];

		}

	}

	while (i <= m) {

		ptemp[k] = p[i];
		b[k++] = a[i++];

	}

	while (j <= r) {

		ptemp[k] = p[j];
		b[k++] = a[j++];

	}

	for (i = 0; i < k; i++) {

		a[l + i] = b[i];
		p[l + i] = ptemp[i];

	}

}

void mergesort(int a[], int p[], int l, int r) {

	if (l < r) {

		int m = (l + r) / 2;

		mergesort(a, p, l, m);
		mergesort(a, p, (m + 1), r);
		merge(a, p, l, m, r);

	}

}

/*
 *	A function to find for each i the sum of distances of all other js.
 *	Important note: in distance array we use pair[i] as index. This is done in
 *					order to be able to match the sums of xs and the sums of ys
 *					to their corresponding pair coordinate. For example in sorted
 *					arrays 1st pair is in x[3] and y[7]. However px[3] is 1 and
 *					py[7] is also 1. So distx[1] and disty[1] are the same pair.
 * 	To calculate the sum we use an easy to extract formula. As the values are sorted
 * 	we find the first sum which is the sum of the distances of all the others to this.
 *	After that it is easy to find the sum of the distances of the next one to all the
 *	others. We just need to add the distance between the last two values as many times
 *	as the amount of previous values, as well as subtract that distance the remaining
 *	times.
 *
 *	@param distance The sums for each index
 *	@param coordinate The value of each index
 *	@param pair The initial index of the values
 *	@param size The size of the array
 *
 *	Complexity: O(n)
 */
void calculate(long long int distance[], int coordinate[], int pair[], int size) {

	int i;

	for (i = 0; i < size; i++)
		distance[pair[0]] += coordinate[i] - coordinate[0];

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
		distance[pair[i]] = distance[pair[i - 1]] + (2 * i - size) * (coordinate[i] - coordinate[i - 1]);

}
