#include <bits/stdc++.h>
using namespace std;
    
typedef vector<int> vi;
typedef vector<vi> vvi;
    
void dfs(int v, vvi& adj, vi& euler, vi& first, vi& height){
    first[v] = euler.size();
    euler.push_back(v);
    for(int u : adj[v]){
        height[u] = height[v] + 1;
        dfs(u, adj, euler, first, height);
        euler.push_back(v);
    }
}
    
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int T; cin >> T;
    
    for(int t=1; t<=T; t++){
        cout << "Case " << t << ":\n";
    
        int n; cin >> n;
        vvi adj(n);
        for(int i=0; i<n; i++){
            int m; cin >> m;
            adj[i].resize(m);
            for(int j=0; j<m; j++){
                cin >> adj[i][j];
                adj[i][j]--;
            }
        }
    
    
        vi euler, first(n), height(n);
        euler.reserve(2*n);
        height[0] = 0;
        dfs(0, adj, euler, first, height);
    
        
        int m = euler.size();
    
        int LOG = 1;
        while((1<<LOG) <= m) LOG++;
    
        vi lg(m+1, 0);
        for(int i=2; i<=m; i++)
            lg[i] = lg[i/2] + 1;
    
        vvi stb(m, vi(LOG));
    
        for(int i=0; i<m; i++)
                stb[i][0] = euler[i];
    
        for(int j=1; j<LOG; j++){
            for(int i=0; i<=m-(1<<j); i++){
                stb[i][j] = stb[i][j-1];
                if(height[stb[i+(1<<(j-1))][j-1]] < height[stb[i][j]])
                    stb[i][j] = stb[i+(1<<(j-1))][j-1];
            }
        }
    
    
        int q; cin >> q;
    
        while(q--){
            int u, v; 
            cin >> u >> v;
            u--; v--;
    
            int l = first[u], r = first[v];
            if(l > r) swap(l, r);
    
            int j = lg[r-l+1];
    
            int res = stb[r-(1<<j)+1][j];
            if(height[stb[l][j]] < height[res])
                res = stb[l][j];
    
            cout << ++res << '\n';
        }
    }
    
    return 0;
} 