#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> Graph;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while(t--){
        int n;
        cin >> n;
        Graph adj(n);
        for(int i=0; i<n-1; i++){
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int end = 0;
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(0);

        while(!q.empty()){
            int v = q.front();
            q.pop();
            visited[v] = true;
            end = v;
            for(int u : adj[v]){
                if(!visited[u])
                    q.push(u);
            }
        }

        int maxlen = 0;
        fill(visited.begin(), visited.end(), false);
        queue<pair<int,int>> qu;
        qu.push(make_pair(end, 0));
        while(!qu.empty()){
            int v = qu.front().first,
                len = qu.front().second;
            qu.pop();
            visited[v] = true;
            if(len > maxlen)
                maxlen = len;
            for(int u : adj[v]){
                if(!visited[u])
                    qu.push(make_pair(u, len+1));
            }
        }

        int res = (maxlen + 1) / 2;
        cout << res << '\n'; 
    }

    return 0;
}