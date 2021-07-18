#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <algorithm>
using namespace std;
    
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<bool> vb;
typedef vector<unordered_set<int>> vus;
    
void dfs(int v, const vii& g, vb& visited, vi& cache){
    visited[v] = true;
    for(int u : g[v]){
        if(!visited[u]){
            dfs(u, g, visited, cache);
        }
    }
    cache.push_back(v);
}
    
vi capital(int n, const vii& g, const vii& gt){
    vb visited(n, false);
    vi cache;
    for(int i=0; i<n; i++){
        if(!visited[i])
            dfs(i, g, visited, cache);
    }
    
    fill(visited.begin(), visited.end(), false);
    
    vii sccNodes;
    for(int i=n-1; i>=0; i--){
        if(!visited[cache[i]]){
            vector<int> nodes;
            dfs(cache[i], gt, visited, nodes);
            sccNodes.push_back(nodes);
        }
    }
    
    int sccN = sccNodes.size();
    
    vector<int> sccMap(n);
    for(int i=0; i<sccN; i++){
        for(int j : sccNodes[i]){
            sccMap[j] = i;
        }
    }
    
    vus sccGraph(sccN);
    for(int i=0; i<n; i++){
        int from = sccMap[i];
        for(int j : gt[i]){
            int to = sccMap[j];
            if(from != to)
                sccGraph[from].insert(to);
        }
    }
    
    vi indegree(sccN, 0);
    for(int i=0; i<sccN; i++){
        for(int j : sccGraph[i]){
            indegree[j]++;
        }
    }
    
    int head = -1;
    for(int i=0; i<sccN; i++){
        if(indegree[i] == 0){
            if(head == -1){
                head = i;
            } else {
                head = -1;
                break;
            }
        }
    }
    
    if(head == -1)
        return vi();
    vi res = sccNodes[head];
    sort(res.begin(), res.end());
    return res;
}
    
int main()
{
    int n, m;
    cin >> n >> m;
    
    vii g(n), gt(n);
    for(int i=0; i<m; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        gt[b].push_back(a);
    }
    
    vi candidates = capital(n, g, gt);
    
    if(candidates.empty()){
        cout << "0\n";
    } else {
        cout << candidates.size() << '\n';
        for(int c : candidates)
            cout << c+1 << ' ';
        cout << '\n';
    }
    
    return 0;
} 