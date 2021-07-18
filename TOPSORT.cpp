#include <iostream>
#include <vector>
#include <queue>
using namespace std;
 
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<vi> Graph;
 
class comp{
public:
    bool operator()(int a, int b){
        return (a > b);
    }
};
 
typedef priority_queue<int, vi, comp> pqi;
 
bool topSort(int n, const Graph& adj, vi& indegree, vi& res){
    pqi pq;
    for(int i=0; i<n; i++){
        if(indegree[i] == 0)
            pq.push(i);
    }
 
    while(!pq.empty()){
        int v = pq.top();
        pq.pop();
        res.push_back(v);
        for(int u : adj[v]){
            indegree[u]--;
            if(indegree[u] == 0)
                pq.push(u);
        }
    }
 
    return (res.size() == n);
}
 
int main()
{
    int n, m;
    cin >> n >> m;
    Graph adj(n);
    vi indegree(n, 0);
    for(int i=0; i<m; i++){
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        indegree[v]++;
    }
 
    vi res;
    if(topSort(n, adj, indegree, res)){
        for(int v : res){
            cout << v+1 << ' ';
        }
    } else {
        cout << "Sandro fails.";
    }
 
    cout << '\n';
 
    return 0;
}