#include <bits/stdc++.h>
using namespace std;
    
typedef long long ll;
    
const int MOD = 1e9;
    
struct Edge{
    int u, v;
    ll w;
};
    
bool comp(const Edge& e1, const Edge& e2){
    return (e1.w > e2.w);
}
    
int ds_find(int i, vector<int>& parent){
    if(parent[i] == i)
        return i;
    parent[i] = ds_find(parent[i], parent);
    return parent[i];
}
    
ll ds_union(int i, int j, vector<int>& parent, vector<int>& rank, vector<int>& count){
    int irep = ds_find(i, parent),
        jrep = ds_find(j, parent);
    if(irep == jrep) 
        return 0;
    if(rank[irep] > rank[jrep])
        swap(irep, jrep);
    parent[irep] = jrep;
    if(rank[irep] == rank[jrep])
        rank[jrep]++;
    ll res = (ll)count[irep] * count[jrep];
    res %= MOD;
    count[jrep] += count[irep];
    return res;
}
    
int costSum(int n, int m, vector<Edge>& edges){
    sort(edges.begin(), edges.end(), comp);
    
    vector<ll> sum(m+1, 0);
    for(int i=m-1; i>=0; i--){
        sum[i] = sum[i+1] + edges[i].w;
        sum[i] %= MOD;
    }
    
    vector<int> parent(n), rank(n, 0), count(n, 1);
    for(int i=0; i<n; i++)
        parent[i] = i;
    
    ll res = 0;
    
    for(int i=0; i<m; i++){
        res += ds_union(edges[i].u, edges[i].v, parent, rank, count) * sum[i];
        res %= MOD;
    }
    
    return res;
}
    
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for(int i=0; i<m; i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].u--; edges[i].v--;
    }
    
    cout << costSum(n, m, edges) << '\n';
    
    return 0;
} 