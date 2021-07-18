// works for bridges, but not for articulation points
#include <bits/stdc++.h>
using namespace std;

typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<vi> Graph;
typedef pair<int,int> pii;
typedef unordered_set<string> us;

const int INF = numeric_limits<int>::max();

void apUtil(int v, int time, const Graph& adj, vb& ap, vb& visited, vi& parent, vi& disc, vi& low){
    visited[v] = true;
    disc[v] = low[v] = time;
    int cc = 0;
    for(int u : adj[v]){
        if(!visited[u]){
            cc++;
            parent[u] = v;
            apUtil(u, time+1, adj, ap, visited, parent, disc, low);
            low[v] = min(low[v], low[u]);
            if(parent[v]==-1 && cc > 1)
                ap[v] = true;
            if(parent[v]!=-1 && low[u] >= disc[v])
                ap[v] = true;
        } else if(u != parent[v]){
            low[v] = min(low[v], disc[u]);
        }
    }
}

void bridgeUtil(int v, int time, const Graph& adj, us& bridges, vb& visited, vi& parent, vi& disc, vi& low){
    visited[v] = true;
    disc[v] = low[v] = time;
    for(int u : adj[v]){
        if(!visited[u]){
            parent[u] = v;
            bridgeUtil(u, time+1, adj, bridges, visited, parent, disc, low);
            low[v] = min(low[v], low[u]);
            if(parent[v]!=-1 && low[u] > disc[v])
                bridges.insert(to_string(min(u,v))+" "+to_string(max(u,v)));
        } else if(u != parent[v]){
            low[v] = min(low[v], disc[u]);
        }
    }
}

us findBridges(int n, const Graph& adj){
    us bridges;
    vb visited(n, false);
    vi parent(n, -1), disc(n, INF), low(n, INF);
    bridgeUtil(0, 0, adj, bridges, visited, parent, disc, low);
    return bridges;
}

vb findAPs(int n, const Graph& adj){
    vb ap(n, false), visited(n, false);
    vi parent(n, -1), disc(n, INF), low(n, INF);
    apUtil(0, 0, adj, ap, visited, parent, disc, low);
    return ap;
}

bool isBridge(int c1, int c2, const us& bridges){
    if(c1 > c2)
        swap(c1, c2);
    return (bridges.find(to_string(c1)+" "+to_string(c2)) != bridges.end());
}

void dfs(int v, const Graph& adj, vb& visited, vi& parent){
    visited[v] = true;
    for(int u : adj[v]){
        if(!visited[u]){
            parent[u] = v;
            dfs(u, adj, visited, parent);
        }
    }
}

bool edgeOnPath(int a, int b, int c1, int c2, const vi& parent){
    bool ona = false;
    int v = a;
    while(v != b && parent[v] != -1){
        if((v==c1 && parent[v]== c2) || (v==c2 && parent[v]==c1))
            ona = true;
        v = parent[v];
    }
    if(v == b) 
        return ona;

    bool onb = false;
    v = b;
    while(v != a && parent[v] != -1){
        if((v==c1 && parent[v]== c2) || (v==c2 && parent[v]==c1))
            onb = true;
        v = parent[v];
    }
    if(v == a)
        return onb;
    
    return (ona || onb);
}

bool nodeOnPath(int a, int b, int c, const vi& parent){
    bool ona = false;
    int v = a;
    while(v != b && parent[v] != -1){
        if(v == c)
            ona = true;
        v = parent[v];
    }
    if(v == b) 
        return ona;

    bool onb = false;
    v = b;
    while(v != a && parent[v] != -1){
        if(v == c)
            onb = true;
        v = parent[v];
    }
    if(v == a)
        return onb;

    return (ona || onb);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    Graph adj(n);
    for(int i=0; i<m; i++){
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }

    us bridges = findBridges(n, adj);
    vb ap = findAPs(n, adj);

    vi parent(n, -1);
    vb visited(n, false);
    dfs(0, adj, visited, parent);

    int q;
    cin >> q;

    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int a, b, c1, c2;
            cin >> a >> b >> c1 >> c2;
            a--; b--; c1--; c2--;
            if(isBridge(c1, c2, bridges) && edgeOnPath(a, b, c1, c2, parent))
                cout << "ne\n";
            else 
                cout << "da\n";
        } else if(type == 2){
            int a, b, c;
            cin >> a >> b >> c;
            a--; b--; c--;
            if(ap[c] && nodeOnPath(a, b, c, parent))
                cout << "ne\n";
            else 
                cout << "da\n";
        }
    }

	return 0;
}