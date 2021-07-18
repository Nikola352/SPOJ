#include <bits/stdc++.h>
using namespace std;
    
typedef long long ll;
    
struct Edge{
    int u, v, w;
};
    
bool comp(const Edge& a, const Edge& b){
    return (a.w < b.w);
}
    
int ds_find(int i, vector<int>& parent){
    if(parent[i] == i)
        return i;
    parent[i] = ds_find(parent[i], parent);
    return parent[i];
}
    
void ds_union(int irep, int jrep, vector<int>& parent, vector<int>& rank){
    if(rank[irep] > rank[jrep])
        swap(irep, jrep);
    parent[irep] = jrep;
    if(rank[irep] == rank[jrep])
        rank[jrep]++;
}
    
ll cost(int n, int m, vector<bool>& milk, vector<Edge>& edges){
    sort(edges.begin(), edges.end(), comp);
    
    vector<int> parent(n), rank(n, 0);
    for(int i=0; i<n; i++)
        parent[i] = i;
    
    ll total = 0ll;
    
    for(int i=0; i<m; i++){
        int u = edges[i].u,
            v = edges[i].v,
            w = edges[i].w;
        int urep = ds_find(u, parent),
            vrep = ds_find(v, parent);
        if(urep == vrep)
            continue;
        if(!milk[urep] || !milk[vrep]){
            total += w;
            ds_union(urep, vrep, parent, rank);
            if(milk[urep] || milk[vrep])
                milk[urep] = milk[vrep] = 1;
        }
    }
    
    for(int i=0; i<n; i++){
        if(parent[i] == i && !milk[i])
            return -1;
    }
    
    return total;
}
    
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<bool> milk(n, false);
        for(int i=0; i<n; i++){
            int x; cin >> x;
            if(x == 1) milk[i] = true;
        }
        vector<Edge> edges(m);
        for(int i=0; i<m; i++){
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
            edges[i].u--; edges[i].v--;
        }
    
        ll res = cost(n, m, milk, edges);
        if(res == -1)
            cout << "impossible\n";
        else
            cout << res << '\n';
    }
    
    return 0;
} 