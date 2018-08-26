#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <climits>


#define BSIZE 1<<15

char buffer[BSIZE];
int bpos = 0L, bsize = 0L;

using namespace std;
int a_co,b_co,c_co;
int readLong()
{
    int d = 0L, x = 0L;
    char c;

    while (1)  {
        if (bpos >= bsize) {
            bpos = 0;
            if (feof(stdin)) return x;
            bsize = fread(buffer, 1, BSIZE, stdin);
        }
        c = buffer[bpos++];
        if (c >= '0' && c <= '9') { x = x*10 + (c-'0'); d = 1; }
        else if (d == 1) return x;
    }
    return -1;
}

int max(int a,int b){
	if(a>b) return a;
	else return b;
}

int sum(int a[],int low,int high){
	int i,s=0;
	for (i=low;i<=high;i++){
		s = s + a[i];
	}
	return s;
}

long long int coefficient(int sum){
	return (long long int)( (long long int)(a_co*sum*sum) + (long long int)b_co*sum + (long long int)c_co );
}

int main () {

	int i,j,N;
	int *miam,*solution;


	cin >> N >> a_co >> b_co >> c_co;
	miam = new int [N+1];
	solution = new int [N+1];
	miam[0] = 0;
	solution[0] = 0;
	for(i=1;i<=N;i++){
		miam[i] = readLong();
	}
	for(i=1;i<=N;i++){
		solution[i] = coefficient(sum(miam, 0, i));
		for(j=0;j<i;j++){
			solution[i] = max (solution[i], solution[j] + coefficient(sum(miam,j+1,i)) );
		}
	}
	cout << solution[N] <<endl;

    return 0;
}
