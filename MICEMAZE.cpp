#include <bits/stdc++.h>
using namespace std;
 
typedef vector<vector<pair<int,int> > > Graph;
 
const int INF = numeric_limits<int>::max();
 
class comp{
public:
    bool operator()(const pair<int,int>& a, const pair<int,int>& b){
        return (a.second > b.second);
    }
};
 
int dijkstra(int n, const Graph& adj, int src, int dest){
    vector<int> dist(n, INF);
    vector<bool> spt(n, false);
    dist[src] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int> >, comp> pq;
    for(int i=0; i<n; i++)
        pq.push(make_pair(i, dist[i]));
 
    while(!pq.empty()){
        int v = pq.top().first;
        pq.pop();
        if(v == dest) break;
        if(spt[v]) continue;
        spt[v] = true;
        for(pair<int,int> p : adj[v]){
            int u = p.first, w = p.second;
            if(!spt[u]){
                if(dist[v]!=INF && dist[v]+w < dist[u]){
                    dist[u] = dist[v] + w;
                    pq.push(make_pair(u, dist[u]));
                }
            }
        }
    }
 
    return dist[dest];
}
 
int main()
{
    int n, e, t;
    cin >> n >> e >> t;
    e--;
    int m;
    cin >> m;
    Graph adj(n);
    for(int i=0; i<m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back(make_pair(v, w));
    }
 
    int c = 0;
    for(int i=0; i<n; i++){
        if(dijkstra(n, adj, i, e) <= t)
            c++;
    }
 
    cout << c << '\n';
 
    return 0;
}