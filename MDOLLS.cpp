#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
 
const int MAX = 20000;
 
struct Doll {
    int h, w;
};
 
bool comp(Doll& d1, Doll& d2) {
    if(d1.h == d2.h)
        return (d1.w > d2.w);
    return (d1.h < d2.h);
}
 
int binarySearch(Doll x, vector<Doll> arr){
    int l=0, r=arr.size()-1, lp=-1;
    while(l<=r){
        int m = l + (r-l)/2;
        if(arr[m].h < x.h && arr[m].w < x.w){
            lp = m;
            r = m-1;
        } else {
            l = m+1;
        }
    }
    return lp;
}
 
int minNestedDolls(int n, Doll dolls[MAX]) {
    vector<Doll> unnested;
    unnested.push_back(dolls[0]);
    for (int i = 1; i < n; i++) {
        int maxIdx = binarySearch(dolls[i], unnested);
        if (maxIdx == -1)
            unnested.push_back(dolls[i]);
        else
            unnested[maxIdx] = dolls[i];
    }
    return unnested.size();
}
 
int main() {
    int t;
    cin >> t;
 
    while (t--) {
        int n;
        cin >> n;
        Doll dolls[MAX];
        for (int i = 0; i < n; i++) {
            cin >> dolls[i].h;
            cin >> dolls[i].w;
        }
        sort(dolls, dolls + n, comp);
        cout << minNestedDolls(n, dolls) << endl;
    }
 
    return 0;
}