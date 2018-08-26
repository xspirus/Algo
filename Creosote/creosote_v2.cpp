#include <iostream>
#include <vector>

using namespace std;

long long int function(int, int, int, int);

int main() {

    int n, a, b, c, i, j;
    long long int temp;

    cin >> n >> a >> b >> c;

    vector<int> miam(n);
    vector<int> S(n, 0);
    vector<long long int> gain(n);

    for (i = 0; i < n; i++) {
        cin >> miam[i];
        if (i == 0)
            S[i] = miam[i];
        else
            S[i] = S[i - 1] + miam[i];
    }

    gain[0] = function(a, b, c, S[0]);
    for (i = 1; i < n; i++) {
        gain[i] = function(a, b, c, S[i]);
        for (j = 0; j < i; j++) {
            temp = gain[j] + function(a, b, c, (S[i] - S[j]));
            if (temp > gain[i])
                gain[i] = temp;
        }
    }

    cout << gain[n - 1] << endl;

    return 0;

}

long long int function(int a, int b, int c, int x) {
    return (long long int)((long long int)a * x * x + (long long int)b * x + (long long int)c);
}
