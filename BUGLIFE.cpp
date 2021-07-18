#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> Graph;

bool suspicious(int n, const Graph& adj){
    vector<bool> visited(n, false), gender(n, false);
    queue<int> q;
    for(int i=0; i<n; i++){
        if(!visited[i]){
            q.push(i);
            while(!q.empty()){
                int v = q.front();
                q.pop();
                if(!visited[v]){
                    visited[v] = true;
                    for(int u : adj[v]){
                        if(visited[u]){
                            if(gender[u] == gender[v])
                                return true;
                        } else {
                            gender[u] = !gender[v];
                            q.push(u);
                        }
                    }
                }
            }
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    for(int s=1; s<=t; s++){
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

        cout << "Scenario #" << s << ":\n";
        if(suspicious(n, adj))
            cout << "Suspicious bugs found!\n";
        else 
            cout << "No suspicious bugs found!\n";
    }

    return 0;
}