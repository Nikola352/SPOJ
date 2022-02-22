#include <iostream>
#include <vector>
#include <limits>
#include <queue>
using namespace std;
 
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef vector<vii> Graph;
 
struct Node{
    int v, mask;
    double dist;
    Node(int v, int m, double d) : v(v), mask(m), dist(d) {}
};
 
class cmp{
public:
    bool operator()(const Node& a, const Node& b){
        return a.dist > b.dist;
    }
};
 
const double inf = numeric_limits<double>::infinity();
 
double dijkstra(int n, int m, int src, int dest, const Graph& adj, const vi& tickets){
    vvd dist(m, vd(1<<n, inf));
    vvb vis(m, vb(1<<n, false));
 
    priority_queue<Node, vector<Node>, cmp> pq;
 
    dist[src][0] = 0.0;
    pq.emplace(src, 0, 0.0);
 
    while(!pq.empty()){
        int v = pq.top().v, vmask = pq.top().mask;
        pq.pop();
 
        if(vis[v][vmask]) continue;
        vis[v][vmask] = true;
 
        for(int i=0; i<n; i++){
            if(vmask & (1<<i)) continue;
            int umask = vmask | (1<<i);
 
            for(auto e : adj[v]){
                int u = e.first, d = e.second;
                if(vis[u][umask]) continue;
 
                double pot = dist[v][vmask] + (double)d / (double)tickets[i];
                if(pot < dist[u][umask]){
                    dist[u][umask] = pot;
                    pq.emplace(u, umask, pot);
                }
            }
        }
    }
 
    double res = inf;
    for(int mask=0; mask<(1<<n); mask++)
        res = min(res, dist[dest][mask]);
    return res;
}
 
int main()
{
    int n, m, p, a, b;
    cin >> n >> m >> p >> a >> b;
    a--; b--;
 
    while(n != 0 && m != 0){
        vi tickets(n);
        for(int i=0; i<n; i++)
            cin >> tickets[i];
 
        Graph adj(m);
        for(int i=0; i<p; i++){
            int u, v, w;
            cin >> u >> v >> w;
            u--; v--;
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
 
        double res = dijkstra(n, m, a, b, adj, tickets);
        if(res == inf) cout << "Impossible\n";
        else cout << res << '\n';
 
        cin >> n >> m >> p >> a >> b;
        a--; b--;
    }
 
    return 0;
}