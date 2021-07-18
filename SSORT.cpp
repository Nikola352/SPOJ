#include <bits/stdc++.h>
using namespace std;
 
vector<int> parent, rnk, minel, sum, cnt;
 
void ds_init(int n, const vector<int>& arr){
    parent.clear(); parent.resize(n);
    rnk.clear(); rnk.resize(n);
    minel.clear(); minel.resize(n);
    sum.clear(); sum.resize(n);
    cnt.clear(); cnt.resize(n);
    for(int i=0; i<n; i++){
        parent[i] = i;
        rnk[i] = 0;
        minel[i] = sum[i] = arr[i];
        cnt[i] = 1;
    }
}
 
int ds_find(int i){
    if(parent[i] == i)
        return i;
    int p = ds_find(parent[i]);
    parent[i] = p;
    return p;
}
 
void ds_union(int i, int j){
    int irep = ds_find(i),
        jrep = ds_find(j);
    if(irep == jrep) return;
    if(rnk[irep] > rnk[jrep])
        swap(irep, jrep);
    parent[irep] = jrep;
    if(rnk[irep] == rnk[jrep])
        rnk[jrep]++;
    minel[jrep] = min(minel[irep], minel[jrep]);
    sum[jrep] = sum[irep] + sum[jrep];
    cnt[jrep] = cnt[irep] + cnt[jrep];
}
 
int minCost(int n, const vector<int>& arr){
    ds_init(n, arr);
 
    vector<int> sorted(n);
    for(int i=0; i<n; i++)
        sorted[i] = arr[i];
    sort(sorted.begin(), sorted.end());
    unordered_map<int, int> idx;
    for(int i=0; i<n; i++)
        idx[sorted[i]] = i;
 
    for(int i=0; i<n; i++)
        ds_union(i, idx[arr[i]]);
 
    int minall = arr[0];
    for(int i=1; i<n; i++)
        minall = min(minall, arr[i]);
 
    int res = 0;
    for(int i=0; i<n; i++){
        if(parent[i] == i){
            int opt1 = sum[i] + (cnt[i]-2)*minel[i];
            if(minel[i] == minall){
                res += opt1;
            } else {
                int opt2 = sum[i]-minel[i]
                    + (cnt[i]-1)*minall
                    + 2*(minall + minel[i]);
                res += min(opt1, opt2);
            }
        }
    }
 
    return res;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n, cn=1;
    cin >> n;
    while(n != 0){
        vector<int> arr(n);
        for(int i=0; i<n; i++)
            cin >> arr[i];
        cout << "Case " << cn << ": " << minCost(n, arr) << "\n\n";
        cin >> n;
        cn++;
    }
 
    return 0;
}