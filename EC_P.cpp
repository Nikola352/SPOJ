#include <bits/stdc++.h>
using namespace std;
 
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<vi> Graph;
 
const int INF = numeric_limits<int>::max();
 
void addEdge(int u, int v, Graph& adj){
    adj[u].push_back(v);
    adj[v].push_back(u);
}
 
void dfs(int v, int time, const Graph& adj, set<pair<int, int>>& bridges, vb& visited, vi& parent, vi& disc, vi& low){
    visited[v] = true;
    low[v] = disc[v] = time;
    for(int u : adj[v]){
        if(!visited[u]){
            parent[u] = v;
            dfs(u, time+1, adj, bridges, visited, parent, disc, low);
            low[v] = min(low[v], low[u]);
            if(low[u] > disc[v]){
                if(u < v)
                    bridges.insert(make_pair(u, v));
                else
                    bridges.insert(make_pair(v, u));
            }
        } else if(parent[v] != u){
            low[v] = min(low[v], disc[u]);
        }
    }
}
 
void bridges(int n, const Graph& adj){
    vb visited(n, false);
    vi parent(n, -1), disc(n, INF), low(n, INF);
    set<pair<int, int>> bridges;
    for(int i=0; i<n; i++)
        if(!visited[i])
            dfs(i, 0, adj, bridges, visited, parent, disc, low);
    int t = bridges.size();
    if(t == 0){
        printf("Sin bloqueos\n");
    } else {
        cout << t << '\n';
        for(auto it=bridges.begin(); it!=bridges.end(); it++){
            printf("%d %d\n", it->first+1, it->second+1);
        }
    }
}
 
int main()
{
    int nc;
    cin >> nc;
 
    for(int i=1; i<=nc; i++){
        int n, m;
        scanf("%d%d", &n, &m);
        Graph adj(n);
        for(int i=0; i<m; i++){
            int u, v;
            scanf("%d%d", &u, &v);
            addEdge(--u, --v, adj);
        }
        printf("Caso #%d\n", i);
        bridges(n, adj);
    }
 
    return 0;
}