#include <bits/stdc++.h>
using namespace std;
    
const int LOG = 14;
    
void dfs(int v, vector<vector<int>>& tree, vector<int>& depth, vector<vector<int>>& anc) {
    for(int u : tree[v]) {
        depth[u] = depth[v] + 1;
        anc[u][0] = v;
        for(int j=1; j<LOG; j++) 
            anc[u][j] = anc[anc[u][j-1]][j-1];
        dfs(u, tree, depth, anc);
    }
}
    
int lca(int u, int v, vector<vector<int>>& tree, vector<int>& depth, vector<vector<int>>& anc) {
    if(depth[u] < depth[v]) swap(u, v);
    int k = depth[u] - depth[v];
    
    for(int j=LOG-1; j>=0; j--)
        if(k & (1<<j)) u = anc[u][j];
    
    if(u == v) return u;
    
    for(int j=LOG-1; j>=0; j--){
        if(anc[u][j] != anc[v][j]){
            u = anc[u][j];
            v = anc[v][j];
        }
    }
    
    return anc[u][0];
}
    
int main()
{
    int n; cin >> n;
    vector<vector<int>> tree(n);
    for(int i=0; i<n; i++){
        int m; cin >> m;
        for(int j=0; j<m; j++){
            int x; cin >> x;
            tree[i].push_back(x);
        }
    }
    
    vector<int> depth(n, 0);
    vector<vector<int>> anc(n, vector<int>(LOG, 0));
    dfs(0, tree, depth, anc);
    
    int q; cin >> q;
    while(q--){
        int u, v; cin >> u >> v;
        cout << lca(u, v, tree, depth, anc) << endl;
    }
    
    return 0;
} 