#include <bits/stdc++.h>
using namespace std;
 
struct FuelStop{
    int dist, fuel;
};
 
bool comp(const FuelStop& f1, const FuelStop& f2){
    return (f1.dist > f2.dist);
}
 
int minStops(int n, vector<FuelStop>& stops, int l, int p){
    sort(stops.begin(), stops.end(), comp);
    int c=0;
    priority_queue<int> pq;
    for(int i=0; i<n; i++){
        while(!pq.empty() && l-stops[i].dist > p){
            p += pq.top();
            pq.pop();
            c++;
        }
        if(pq.empty() && l-stops[i].dist > p)
            return -1;
        pq.push(stops[i].fuel);
    }
    while(!pq.empty() && l > p){
        p += pq.top();
        pq.pop();
        c++;
    }
    if(pq.empty() && l > p) return -1;
    return c;
}
 
int main()
{
    int t;
    cin >> t;
 
    while(t--){
        int n;
        cin >> n;
        vector<FuelStop> stops(n);
        for(int i=0; i<n; i++)
            cin >> stops[i].dist >> stops[i].fuel;
        int l, p;
        cin >> l >> p;
        cout << minStops(n, stops, l, p) << endl;
    }
 
    return 0;
}