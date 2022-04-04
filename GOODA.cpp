#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<unordered_set<int>> vus;
typedef pair<int,int> pii;

void dfs(int v, vvi& adj, vb& visited, vi& cache){
    visited[v] = true;
    for(int u : adj[v]){
        if(!visited[u]) 
            dfs(u, adj, visited, cache);
    }
    cache.push_back(v);
}

ll dfsF(int v, vvi& adj, vb& visited, vi& f, int cmp, vi& sccMap){
    visited[v] = true;
    sccMap[v] = cmp;
    ll res = f[v];
    for(int u : adj[v]){
        if(!visited[u])
            res += dfsF(u, adj, visited, f, cmp, sccMap);
    }
    return res;
}

pii sccGraph(int n, vvi& adj, vvi& rev, vi& f, int s, int e, vvi& g, vll& sum){
    vb visited(n, false);
    vi order;
    for(int i=0; i<n; i++){
        if(!visited[i]) 
            dfs(i, adj, visited, order);
    }
    reverse(order.begin(), order.end());

    int sccN = 0;
    vi sccMap(n);
    fill(visited.begin(), visited.end(), false);
    for(int i=0; i<n; i++){
        if(!visited[order[i]])
            sum.push_back(dfsF(order[i], rev, visited, f, sccN++, sccMap));
    }

    vus sccAdj(sccN);
    for(int i=0; i<n; i++){
        int v = sccMap[i];
        for(int j : adj[i]){
            int u = sccMap[j];
            if(u != v) sccAdj[v].insert(u);
        }
    }

    // converting from vus to vvi is not necessary
    g.resize(sccN);
    for(int i=0; i<sccN; i++){
        for(int j : sccAdj[i]){
            g[i].push_back(j);
        }
    }

    return pii(sccMap[s], sccMap[e]);
}

ll maxFun(int src, int dest, vvi& adj, vll& sum){
    int n = adj.size();

    vi topsort;
    vb visited(n, false);
    for(int i=0; i<n; i++){
        if(!visited[i])
            dfs(i, adj, visited, topsort);
    }
    reverse(topsort.begin(), topsort.end());

    vll dp(n, -1);
    dp[src] = sum[src];

    for(int i=0; i<n; i++){
        int v = topsort[i];
        if(dp[v] == -1) continue;
        for(int u : adj[v])
            dp[u] = max(dp[u], dp[v] + sum[u]);
    }

    return dp[dest];
}

int main()
{
    int n, m, s, e;
    cin >> n >> m >> s >> e;
    s--; e--;
    vi f(n);
    for(int i=0; i<n; i++)
        cin >> f[i];
    vvi adj(n), rev(n);
    for(int i=0; i<m; i++){
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        rev[v].push_back(u);
    }

    vvi g; vll sum;
    pii p = sccGraph(n, adj, rev, f, s, e, g, sum);

    cout << maxFun(p.first, p.second, g, sum) << '\n';

    return 0;
}