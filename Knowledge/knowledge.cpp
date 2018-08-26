#include <iostream>
#include <cstdio>
#include <climits>

using namespace std;

#define BSIZE 1<<15

char buffer[BSIZE];
int bpos = 0, bsize = 0;

int read_int();
#define MAX(A, B) ((A > B) ? A : B)

int main(int argc, char *argv[]) {

    int N, M, i, j;
    int best;
    int *value, **gain;

    N = read_int();
    M = read_int();

    value = new int[N];
    gain = new int*[N];
    /**
     *  Read value from input
     *  and make the dynamic array
     */
    for (i = 0; i < N; i++) {
        value[i] = read_int();
        gain[i] = new int[2];
        gain[i][0] = 0;
    }

    /**
     *  Done reading
     */

    /**
     *  We use % 2 because we only
     *  need to remember the previous
     *  gain (with one less buysell).
     *  So with % 2 we keep current and
     *  previous gain. In this way the
     *  array is always in cache so no
     *  miss penalty.
     */
    for (j = 1; j <= M; j++) {
        gain[0][j] = 0;
        best = INT_MIN;
        for (i = 1; i < N; i++) {
            //cout << i << " " << j << endl;
            //cout << "Best: " << best << endl;
            //cout << "Candidate: " << (gain[i - 1][(j - 1) % 2] - value[i - 1]) << endl;
            best = MAX(best, gain[i - 1][(j - 1) % 2] - value[i - 1]);
            gain[i][j % 2] = MAX(gain[i - 1][j % 2], best + value[i]);
        }
    }

    cout << gain[N - 1][M % 2] << endl;

    return 0;

}

int read_int() {

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
            x = x * 10 + (c - '0');
            d = 1;
        } else if (d == 1)
            return x;
    }

    return -1;

}

int max(int &a, int &b) {
    return ((a > b) ? a : b);
}
