#include <bits/stdc++.h>
using namespace std;
    
typedef long long ll;
    
struct Edge{
    int src, dest;
    ll dist;
    Edge(int tsrc, int tdest, ll tdist){
        src = tsrc;
        dest = tdest;
        dist = tdist;
    }
};
    
bool comp(const Edge& a, const Edge& b){
    return (a.dist < b.dist);
}
    
int ds_find(int i, vector<int>& parent){
    if(parent[i] == i)
        return i;
    parent[i] = ds_find(parent[i], parent);
    return parent[i];
}
    
void ds_union(int i, int j, vector<int>& parent, vector<int>& rank){
    int irep = ds_find(i, parent),
        jrep = ds_find(j, parent);
    if(irep == jrep) return;
    if(rank[irep] > rank[jrep])
        swap(irep, jrep);
    parent[irep] = jrep;
    if(rank[irep] == rank[jrep])
        rank[jrep]++;
}
    
ll kruskal(int n, int m, vector<Edge>& edges){
    vector<int> parent(n), rank(n, 0);
    for(int i=0; i<n; i++)
        parent[i] = i;
    
    sort(edges.begin(), edges.end(), comp);
    
    ll total = 0;
    
    for(int i=0; i<m; i++){
        int r1 = ds_find(edges[i].src, parent),
            r2 = ds_find(edges[i].dest, parent);
        if(r1 != r2){
            ds_union(r1, r2, parent, rank);
            total += edges[i].dist;
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
    vector<Edge> edges;
    for(int i=0; i<m; i++){
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--; v--;
        edges.emplace_back(u, v, w);
    }
    
    cout << kruskal(n, m, edges) << '\n';
    
    return 0;
} 