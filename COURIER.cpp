#include <bits/stdc++.h>
using namespace std;
 
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vii;
 
const int INF = numeric_limits<int>::max();
 
void floydWarshall(int n, vvi& dist){
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(dist[i][k] == INF || dist[k][j] == INF) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
 
int bestRoute(int src, int n, const vvi& dist, int z, vii& p){
    p.push_back(pii(src, src));
 
    vvi dp(z+1, vi(1<<z, INF));
    dp[z][0] = 0;
 
    for(int mask=0; mask<(1<<z); mask++){
        for(int i=0; i<z; i++){
            if(mask & (1 << i)){
                for(int j=0; j<=z; j++){
                    if(j == i) continue;
                    int d = dist[p[j].second][p[i].first] + dist[p[i].first][p[i].second];
                    if(dp[j][mask ^ (1<<i)] != INF)
                        dp[i][mask] = min(dp[i][mask], dp[j][mask ^ (1<<i)] + d);
                }
            }
        }
    }
 
    int res = INF;
    for(int i=0; i<z; i++)
        res = min(res, dp[i][(1<<z)-1] + dist[p[i].second][src]);
    return res;
}
 
int main()
{
    int t;
    cin >> t;
 
    while(t--){
        int n, m, src;
        cin >> n >> m >> src;
        src--;
 
        vvi dist(n, vi(n, INF));
        for(int i=0; i<m; i++){
            int u, v, w;
            cin >> u >> v >> w;
            u--; v--;
            dist[u][v] = dist[v][u] = min(dist[u][v], w);
        }
        for(int i=0; i<n; i++)
            dist[i][i] = 0;
 
        floydWarshall(n, dist);
 
        vii packets;
        int z; cin >> z;
        for(int i=0; i<z; i++){
            int u, v, b;
            cin >> u >> v >> b;
            u--; v--;
            for(int j=0; j<b; j++)
                packets.emplace_back(u, v);
        }
 
        cout << bestRoute(src, n, dist, packets.size(), packets) << '\n';
    }
    
    return 0;
}