#include "mergesort.hpp"

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
