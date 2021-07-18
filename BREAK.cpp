#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
 
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef stack<int> sti;
 
void dfsSCC(int v, int& time, const vvi& adj, vi& disc, vi& low, sti& st, vb& inSt, vvi& scc){
    st.push(v);
    inSt[v] = true;
    disc[v] = low[v] = time++;
 
    for(int u : adj[v]){
        if(disc[u] == -1){
            dfsSCC(u, time, adj, disc, low, st, inSt, scc);
            low[v] = min(low[v], low[u]);
        } else if(inSt[u]){
            low[v] = min(low[v], disc[u]);
        }
    }
 
    if(low[v] == disc[v]){
        vi nodes;
        while(st.top() != v){
            int u = st.top();
            st.pop();
            inSt[u] = false;
            nodes.push_back(u);
        }
        nodes.push_back(v);
        st.pop();
        inSt[v] = false;
        scc.push_back(nodes);
    }
}
 
 
void dfsImp(int v, const vvi& adj, vb& visited){
    if(visited[v]) return;
    visited[v] = true;
    for(int u : adj[v]){
        dfsImp(u, adj, visited);
    }
}
 
vi calcImp(int n, const vvi& adj, const vi& val){
    vb visited(n, false);
    vi res(n, 0);
    for(int i=0; i<n; i++){
        dfsImp(i, adj, visited);
        for(int j=0; j<n; j++){
            if(j == i) continue;
            if(visited[j])
                res[i] += val[j];
        }
        fill(visited.begin(), visited.end(), false);
    }
    return res;
}
 
vi mostImportant(int n, const vvi& adj){
    vi disc(n, -1), low(n, -1);
    sti st;
    vb inSt(n, false);
    vvi scc;
    int time = 0;
    for(int i=0; i<n; i++){
        if(disc[i] == -1)
            dfsSCC(i, time, adj, disc, low, st, inSt, scc);
    }
 
    int sccN = scc.size();
 
    vi sccMap(n);
    vi sccVal(sccN, 0);
    for(int i=0; i<sccN; i++){
        sccVal[i] = scc[i].size();
        for(int j : scc[i]){
            sccMap[j] = i;
        }
    }
 
    vvi sccG(sccN);
    for(int i=0; i<n; i++){
        int u = sccMap[i];
        for(int j : adj[i]){
            int v = sccMap[j];
            if(u != v)
                sccG[u].push_back(v);
        }
    }
 
    vi importance = calcImp(sccN, sccG, sccVal);
 
    int mx = importance[0];
    for(int i=1; i<sccN; i++){
        if(importance[i] > mx)
            mx = importance[i];
    }
 
    vi res;
    for(int i=0; i<n; i++){
        if(importance[sccMap[i]] == mx)
            res.push_back(i+1);
    }
    return res;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int t;
    cin >> t;
 
    while(t--){
        int n, m;
        cin >> n >> m;
        vvi adj(n);
        for(int i=0; i<m; i++){
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[v].push_back(u);
        }
        vi res = mostImportant(n, adj);
        for(int e : res)
            cout << e << ' ';
        cout << '\n';
    }
 
    return 0;
}