#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef vector<vector<pair<int,ll> > > Graph;
 
const int INF = numeric_limits<int>::max();
 
ll prim(int n, const Graph& adj){
    vector<ll> key(n, INF);
    vector<bool> mst(n, false);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    key[0] = 0;
    for(int i=0; i<n; i++)
        pq.emplace(key[i], i);
 
    ll total = 0;
 
    while(!pq.empty()){
        int v = pq.top().second;
        pq.pop();
        if(mst[v]) continue;
        mst[v] = true;
        total += key[v];
        for(pair<int,ll> p : adj[v]){
            int u = p.first;
            ll w = p.second;
            if(w < key[u]){
                key[u] = w;
                pq.emplace(w, u);
            }
        }
    }
 
    return total;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int n, m;
    cin >> n >> m;
    Graph adj(n);
    for(int i=0; i<m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
 
    cout << prim(n, adj) << '\n';
 
    return 0;
}