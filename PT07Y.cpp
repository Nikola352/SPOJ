#include <bits/stdc++.h>
using namespace std;
 
typedef vector<vector<int>> Graph;
 
bool tree(const Graph& adj, int n, int m){
    if(m != n-1) return false;
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        int v = q.front();
        q.pop();
        if(visited[v]) return false;
        visited[v] = true;
        for(int u : adj[v]){
            if(!visited[u])
                q.push(u);
        }
    }
    for(int i=0; i<n; i++)
        if(!visited[i]) return false;
    return true;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n, m;
    cin >> n >> m;
    Graph adj(n);
    for(int i=0; i<m; i++){
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    if(tree(adj, n, m))
        cout << "YES\n";
    else
        cout << "NO\n";
 
    return 0;
}
 