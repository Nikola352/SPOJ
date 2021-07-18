#include <bits/stdc++.h>
using namespace std;
 
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<vi> Graph;
 
const int INF = numeric_limits<int>::max();
 
void dfs(int v, int time, const Graph& adj, vi& parent, vb& visited, vb& ap, vi& disc, vi& low){
    int cc = 0;
    visited[v] = true;
    low[v] = disc[v] = time;
    for(int u : adj[v]){
        if(!visited[u]){
            cc++;
            parent[u] = v;
            dfs(u, time+1, adj, parent, visited, ap, disc, low);
            low[v] = min(low[v], low[u]);
            if(parent[v]==-1 && cc>=2)
                ap[v] = true;
            if(parent[v]!=-1 && low[u] >= disc[v])
                ap[v] = true;
        } else if(u != parent[v]){
            low[v] = min(low[v], disc[u]);
        }
    }
}
 
int apCount(const Graph& adj, int n){
    vb visited(n, false), ap(n, false);
    vi parent(n, -1), disc(n, INF), low(n, INF);
    dfs(0, 0, adj, parent, visited, ap, disc, low);
    int c = 0;
    for(int i=0; i<n; i++){
        if(ap[i]) c++;
    }
    return c;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int n, m;
    cin >> n >> m;
 
    while(n!=0 && m!=0){
        Graph adj(n);
        for(int i=0; i<m; i++){
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        cout << apCount(adj, n) << '\n';
        cin >> n >> m;
    }
 
    return 0;
}