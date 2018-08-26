#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

long long int function(int, int, int, int);

int main() {

    int N, a, b, c;
    int miam, magic, i, sum, max;
    vector<int> sums;
    long long int result = 0L;

    cin >> N;
    cin >> a;
    cin >> b;
    cin >> c;
    //cout << N << endl << a << " " << b << " " << c << endl;

    magic = -(b / (2 * a));
    vector<int> miams(N);
    max = 0;
    for (i = 0; i < N; i++) {
        cin >> miams[i];
        if (miams[i] > max)
            max = miams[i];
    }
    /*i = 0;
    cin >> miam;
    while (i < N) {
        sum = miam;
        i++;
        while (i < N) {
            cin >> miam;
            if ((sum + miam) > magic && (function(a, b, c, sum) > function(a, b, c, sum + miam)))
                break;
            sum += miam;
            i++;
        }
        sums.push_back(sum);
    }*/
    i = 0;
    while (i < N) {
        sum = miams[i];
        i++;
        while (i < N - 1) {
            if (((sum + miams[i]) > magic && (function(a, b, c, sum) > function(a, b, c, sum + miams[i]))) || miams[i] > magic)
                break;
            sum += miams[i];
            i++;
        }
        sums.push_back(sum);
    }
    i = 0;
    sum = sums[i];
    //cout << "Sum[0]: " << sums[i] << endl;
    i++;
    while (i < (signed)sums.size()) {
        //cout << "Sum[" << i << "]: " << sums[i] << endl;
        if (function(a, b, c, sum) < function(a, b, c, sum + sums[i])) {
            sum += sums[i];
        } else {
            //cout << "Sum: " << sum << endl;
            result += function(a, b, c, sum);
            sum = sums[i];
        }
        i++;
    }
    result += function(a, b, c, sum);

    cout << result << endl;

    return 0;

}

long long int function(int a, int b, int c, int x) {
    return (long long int)(a * x * x + b * x + c);
}
