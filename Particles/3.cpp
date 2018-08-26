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
            x = x * 10 + (c - '0');
            d = 1;
        } else if (d == 1)
        return x;
    }
    return -1;
}

struct bomb {
    int t;
    int u;
    double tend; //auto einai to t pou vriskw
    int start;
};

bool compareByX(const struct bomb& c, const struct bomb& d)
{
    return c.tend < d.tend;
}

int main() {
    int n, i, k, l;
    n = readLong();
    l = readLong();
    k = readLong();
    vector<bomb> a,b;
    for (i = 0; i <= n - 1; i++) {
        a.push_back(bomb());
        a[i].t = readLong();
        a[i].u = readLong();
        a[i].start=i+1; // ayto einai gia na krataw thn arxikh thesi
    }
    for (i= 0; i <= n - 1; i++) {
        b.push_back(bomb());
        b[i].t = readLong();
        b[i].u = readLong();
        b[i].start=i+1;
        b[i].tend=l/(b[i].u)+ b[i].t ;
    }
    sort(b.begin(), b.end(), compareByX);
    double time[n+1] ;
    for (i=0; i<=n-1; i++){ time[i]=b[i].tend;}
    double low,up,mid,up1 ;
    low=0;
    //up=b[0].tend ;
    int c=0;
    up=time[0];
    for (i=0; i<=k-1;){
        if (i!=0) {
            low=up;
            up=time[c];
        }
        while (up-low>=0.00001) {
            mid=(low+up)/2 ;
            //cout<<mid<<endl ;
            double max_a=0; double max_b=0;
            for(int j=0; j<=n-1; j++) {
                double aa=(a[j].u)*(mid-a[j].t);
                double bb=(b[j].u)*(mid-b[j].t);
                if (aa>max_a) {
                    max_a=aa;
                }
                if (bb>max_b) {
                    max_b=bb;
                }
            }
            //cout <<max_a<<endl ;
            //cout<<max_b<<endl ;
            //cout <<max_a+max_b<<endl;
            if (max_a+max_b>=l) {
                up1=up; up=mid;
            }
            else {
                low=mid;
            }
            if(up-low<=0.00001) {
                double max_a=0; double max_b=0;
                int thesi_a=-1; int thesi_b=-1;  //th thesi_a th thelw gia thn arxikh thesi
                int posa=-1; 	int posb=-1;
                for(int j=0; j<=n-1; j++) {
                    double aa=(a[j].u)*(up-a[j].t);
                    if (aa>max_a) {
                        max_a=aa;
                        thesi_a=a[j].start;
                        posa=j;
                    }
                }
                for(int j=0; j<=n-1; j++ ){
                    double bb=(b[j].u)*(up-b[j].t);
                    if (bb>max_b) {
                        max_b=bb;
                        thesi_b=b[j].start;
                        posb=j;
                    }
                }

                //cout <<max_a<<endl ;
                //cout <<max_b<<endl ;
                bool flag=true;
                if ((thesi_a==1) and (thesi_b==1) and (max_a+max_b<l)){
                    flag=false;
                }
                if((thesi_a>=0) and (thesi_b>=0) and (flag) and (max_a+max_b>=l)){
                    cout <<thesi_a<<" " ;
                    cout <<thesi_b<<endl ;
                    i++ ;
                    c++;
                    a.erase (a.begin()+posa);
                    b.erase (b.begin()+posb);
                    n=n-1;
                }
                else {
                    low=up;
                    c++;
                    up=time[c];
                }
            }
        }
    }
    return 0;
}
