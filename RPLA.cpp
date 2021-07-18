#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
 
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vii;
 
vii getRanks(int n, const vvi& adj, vi& indegree){
    priority_queue<pii> pq;
    for(int i=0; i<n; i++){
        if(indegree[i] == 0)
            pq.push(pii(1, i));
    }
 
    vii res;
 
    while(!pq.empty()){
        int rank = pq.top().first,
            v = pq.top().second;
        pq.pop();
        res.push_back(pii(rank, v));
        for(int u : adj[v]){
            if(--indegree[u] == 0)
                pq.push(pii(rank+1, u));
        }
    }
 
    sort(res.begin(), res.end());
    return res;
}
 
int main()
{
    int test;
    scanf("%d", &test);
 
    for(int t=1; t<=test; t++){
        int n, m;
        scanf("%d%d", &n, &m);
        vvi adj(n);
        vi indegree(n, 0);
        for(int i=0; i<m; i++){
            int u, v;
            scanf("%d%d", &u, &v);
            adj[v].push_back(u);
            indegree[u]++;
        }
        vii rank = getRanks(n, adj, indegree);
        printf("Scenario #%d:\n", t);
        for(int i=0; i<n; i++)
            printf("%d %d\n", rank[i].first, rank[i].second);
    }
 
    return 0;
}