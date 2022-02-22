#include <bits/stdc++.h>
using namespace std;
 
const int MOD = (int)1e9 + 7;
const int INF = numeric_limits<int>::max();
 
struct Edge{
    int to, w, idx;
    Edge(int to, int w, int idx)
    : to(to), w(w), idx(idx) {}
};
 
struct Node{
    int dist, v;
    Edge from;
    Node(int dist, int v, Edge from) 
    : dist(dist), v(v), from(from) {}
};
 
struct cmp{
    bool operator()(const Node& a, const Node& b){
        return a.dist > b.dist;
    }
};
 
typedef vector<Edge> ve;
typedef vector<ve> Graph;
typedef vector<int> vi;
typedef vector<vi> vvi;
  
// returns the graph containing all shortest paths starting at src
Graph dijkstra(int src, int n, const Graph& adj){
    Graph g(n);
    
    vi dist(n, INF);
    vector<bool> spt(n, false);
    priority_queue<Node, vector<Node>, cmp> pq;
 
    dist[src] = 0;
    pq.emplace(dist[src], src, Edge(-1, -1, -1));
 
    while(!pq.empty()){
        int v = pq.top().v, curr_dist = pq.top().dist;
        Edge from=pq.top().from;
        pq.pop();
 
        if(spt[v]) {
            if(dist[v] == curr_dist)
                g[from.to].emplace_back(v, from.w, from.idx);
            continue;
        }
        spt[v] = true;
 
        if(from.to != -1)
            g[from.to].emplace_back(v, from.w, from.idx);
 
        if(dist[v] == INF) continue;
 
        for(const Edge& e : adj[v]){
            if(!spt[e.to] && dist[v] + e.w <= dist[e.to]){
                dist[e.to] = dist[v] + e.w;
                pq.emplace(dist[e.to], e.to, Edge(v, e.w, e.idx));
            } else if(dist[v] + e.w == dist[e.to]){
                pq.emplace(dist[e.to], e.to, Edge(v, e.w, e.idx));
            }
        }
    }
 
    return g;
}
 
vi topsort(int n, const Graph& g){
    vi res;
 
    vi indegree(n, 0);
    for(int i=0; i<n; i++){
        for(const Edge& e : g[i])
            indegree[e.to]++;
    }
 
    queue<int> q;
    for(int i=0; i<n; i++)
        if(indegree[i] == 0) 
            q.push(i);
 
    while(!q.empty()){
        int v = q.front();
        q.pop();
 
        res.push_back(v);
 
        for(const Edge& e : g[v]){
            if(--indegree[e.to] == 0)
                q.push(e.to);
        }
    }
 
    return res;
 
}
 
Graph reverse(const Graph& g, int n){
    Graph gr(n);
    for(int i=0; i<n; i++){
        for(auto& e : g[i]){
            gr[e.to].emplace_back(i, e.w, e.idx);
        }
    }
    return gr;
}
 
vi calcPaths(int src, int n, int m, const Graph& g, const Graph& adj){
    // to[v] = number of paths from src to v
    vi to(n, 0);
    to[src] = 1;
 
    vi ts = topsort(n, g);
 
    for(int v : ts){
        for(auto& e : g[v]){
            to[e.to] += to[v];
            to[e.to] %= MOD;
        }
    }
    
    // from[v] = number of path that start at v and ane anywhere (except v!)
    vi from(n, 0);
 
    Graph gr = reverse(g, n); 
    ts = topsort(n, gr); // just reverse vector ts?
 
    for(int v : ts){
        for(auto& e : gr[v]){
            from[e.to] += from[v] + 1;
            from[e.to] %= MOD;
        }
    }
 
    // res[i] = number of paths containing edge with idx=i
    vi res(m, 0);   
    for(int v=0; v<n; v++){
        for(auto& e : g[v]){
            // each path ending at v can be continued with any path starting at e.to
            // + 1 is for path ending at e.to (it is not counted in from[e.to])
            res[e.idx] = ((long long)to[v] * (from[e.to] + 1ll)) % MOD;
        }
    }
 
    return res;
}
 
int main()
{
    int n, m;
    cin >> n >> m;
    Graph adj(n);
    for(int i=0; i<m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].emplace_back(v, w, i);
    }
 
    vi res(m, 0);
    for(int i=0; i<n; i++){
        Graph g = dijkstra(i, n, adj);
        vi edgeAdd = calcPaths(i, n, m, g, adj);
        for(int j=0; j<m; j++){
            res[j] += edgeAdd[j];
            res[j] %= MOD;
        }
    }
 
    for(int i=0; i<m; i++)
        cout << res[i] << '\n';
    
    return 0;
}