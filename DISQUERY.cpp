#include <bits/stdc++.h>
using namespace std;
    
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vii;
typedef vector<vii> vvii;
    
int LOG = 1;
    
void dfs(int v, vvii& adj, vvi& up, vvi& minr, vvi& maxr, vi& depth){
    for(pii& p : adj[v]){
        int u = p.first, w = p.second;
        if(u == up[v][0]) continue;
        depth[u] = depth[v] + 1;
        up[u][0] = v;
        minr[u][0] = maxr[u][0] = w;
        for(int j=1; j<LOG; j++){
            if(up[u][j-1] == -1) continue;
            up[u][j] = up[up[u][j-1]][j-1];
            minr[u][j] = min(minr[u][j-1], minr[up[u][j-1]][j-1]);
            maxr[u][j] = max(maxr[u][j-1], maxr[up[u][j-1]][j-1]);
        }
        dfs(u, adj, up, minr, maxr, depth);
    }
}
    
int lca(int a, int b, vvi& up, vi& depth){
    if(depth[a] < depth[b]) swap(a, b);
    int k = depth[a] - depth[b];
    for(int j=LOG-1; j>=0; j--){
        if(k & (1<<j)) a = up[a][j];
    }
    if(a == b) return a;
    for(int j=LOG-1; j>=0; j--){
        if(up[a][j] != up[b][j]){
            a = up[a][j];
            b = up[b][j];
        }
    }
    return up[a][0];
}
    
int minRoad(int v, int k, vvi& up, vvi& minr){
    int res = INT_MAX;
    for(int j=LOG-1; j>=0; j--){
        if(k & (1<<j)){
            res = min(res, minr[v][j]);
            v = up[v][j];
        }
    }
    return res;
}
    
int maxRoad(int v, int k, vvi& up, vvi& maxr){
    int res = 0;
    for(int j=LOG-1; j>=0; j--){
        if(k & (1<<j)){
            res = max(res, maxr[v][j]);
            v = up[v][j];
        }
    }
    return res;
}
    
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vvii adj(n);
    for(int i=0; i<n-1; i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    
    while((1<<LOG) < n) LOG++;
    
    vvi up(n, vi(LOG, -1));
    vvi minr(n, vi(LOG, -1)), maxr(n, vi(LOG, -1));
    vi depth(n, 0);
    dfs(0, adj, up, minr, maxr, depth);
    
    int q; 
    cin >> q;
    
    while(q--){
        int a, b; 
        cin >> a >> b; 
        a--; b--;
    
        int x = lca(a, b, up, depth);
    
        int minres = min(
            minRoad(a, depth[a]-depth[x], up, minr),
            minRoad(b, depth[b]-depth[x], up, minr)
        );
    
        int maxres = max(
            maxRoad(a, depth[a]-depth[x], up, maxr),
            maxRoad(b, depth[b]-depth[x], up, maxr)
        );
    
        cout << minres << ' ' << maxres << '\n';
    }
    
    return 0;
} 