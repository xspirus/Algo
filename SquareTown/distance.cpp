#include "distance.hpp"

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
