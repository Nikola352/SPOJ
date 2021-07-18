#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
 
const int MAX = 5000;
 
struct Stick {
    int l, w;
};
 
bool comp(Stick& s1, Stick& s2) {
    if (s1.l == s2.l)
        return (s1.w < s2.w);
    return (s1.l < s2.l);
}
 
int binarySearch(int x, vector<Stick> arr) {
    int l = 0, r = arr.size()-1, lp=-1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m].w <= x) {
            lp = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return lp;
}
 
int minSetupTime(int n, Stick arr[MAX]) {
    vector<Stick> potPrevs;
    potPrevs.push_back(arr[0]);
    for (int i = 1; i < n; i++) {
        int maxIdx = binarySearch(arr[i].w, potPrevs);
        if (maxIdx == -1)
            potPrevs.push_back(arr[i]);
        else
            potPrevs[maxIdx] = arr[i]; 
    }
    return potPrevs.size();
}
 
int main() {
    int t;
    cin >> t;
 
    while (t--) {
        int n;
        cin >> n;
        Stick arr[MAX];
        for (int i = 0; i < n; i++) {
            cin >> arr[i].l;
            cin >> arr[i].w;
        }
        sort(arr, arr + n, comp);
        cout << minSetupTime(n, arr) << endl;
    }
 
    return 0;
}