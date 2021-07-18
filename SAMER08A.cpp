#include <bits/stdc++.h>
using namespace std;
    
typedef vector<vector<pair<int, int>>> Graph;
    
const int INF = numeric_limits<int>::max();
    
class comp{
public:
    bool operator()(const pair<int,int>& a, const pair<int,int>& b){
        return (a.second > b.second);
    }
};
    
int dijkstra(int n, const Graph& adj, int src, int dest, vector<vector<int>>& parents, const vector<vector<bool>>& exc){
    vector<int> dist(n, INF);
    vector<bool> sptSet(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, comp> pq;
    dist[src] = 0;
    for(int i=0; i<n; i++)
        pq.emplace(i, dist[i]);
    
    while(!pq.empty()){
        int v = pq.top().first;
        pq.pop();
        if(v == dest) break;
        if(sptSet[v]) continue;
        sptSet[v] = true;
        for(pair<int, int> p : adj[v]){
            int u = p.first, w = p.second;
            if(!exc[v][u] && !sptSet[u]){
                if(dist[v] != INF && dist[v] + w <= dist[u]){
                    if(dist[v] + w < dist[u])
                        parents[u].clear();
                    parents[u].push_back(v);
                    dist[u] = dist[v] + w;
                    pq.emplace(u, dist[u]);
                } 
            }
        }
    }
    
    if(dist[dest] == INF)
        return -1;
    return dist[dest];
}
    
void erasePath(int n, int s, vector<vector<int>>& parents, vector<vector<bool>>& exc){
    stack<int> st;
    st.push(s);
    vector<bool> visited(n, false);
    while(!st.empty()){
        int v = st.top();
        st.pop();
        if(visited[v]) continue;
        visited[v] = true;
        for(int u : parents[v]){
            if(!visited[u]){
                exc[u][v] = true;
                st.push(u);
            }
        }
    }
}
    
int almostShortest(int n, const Graph& adj, int src, int dest){
    vector<vector<bool>> exc(n, vector<bool>(n, false));
    
    vector<vector<int>> parents(n);
    int best = dijkstra(n, adj, src, dest, parents, exc);
    if(best == -1) return -1;
    
    erasePath(n, dest, parents, exc);
    return dijkstra(n, adj, src, dest, parents, exc);
}
    
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    while(n !=0 && m!=0){
        int src, dest;
        cin >> src >> dest;
        Graph adj(n);
        for(int i=0; i<m; i++){
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].emplace_back(v, w);
        }
    
        cout << almostShortest(n, adj, src, dest) << '\n';
    
        cin >> n >> m;
    }
    
    return 0;
} 