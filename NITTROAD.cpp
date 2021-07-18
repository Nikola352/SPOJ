#include <bits/stdc++.h>
using namespace std;
    
int ds_find(int i, vector<int>& parent){
    if(parent[i] == i)
        return i;
    parent[i] = ds_find(parent[i], parent);
    return parent[i];
}
    
int ds_union(int i, int j, vector<int>& parent, vector<int>& rank, vector<int>& size){
    int irep = ds_find(i, parent),
        jrep = ds_find(j, parent);
    if(irep == jrep) return 0;
    if(rank[irep] > rank[jrep])
        swap(irep, jrep);
    parent[irep] = jrep;
    int res = size[irep]*size[jrep];
    size[jrep] += size[irep];
    return res;
}
    
void solve(int n, const vector<pair<int,int>>& edges, stack<pair<char,int>>& queries, const vector<bool>& marked){
    vector<int> parent(n), rank(n, 0), size(n, 1);
    for(int i=0; i<n; i++)
        parent[i] = i;
    
    int count = n*(n-1)/2;
    for(int i=0; i<n-1; i++){
        if(!marked[i])
            count -= ds_union(edges[i].first, edges[i].second, parent, rank, size);
    }
    
    stack<int> res;
    while(!queries.empty()){
        char ch = queries.top().first;
        if(ch == 'Q'){
            queries.pop();
            res.push(count);
        } else if(ch == 'R'){
            int e = queries.top().second;
            queries.pop();
            count -= ds_union(edges[e].first, edges[e].second, parent, rank, size);
        }
    }
    
    while(!res.empty()){
        cout << res.top() << '\n';
        res.pop();
    }
}
    
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    
    while(t--){
        int n;
        cin >> n;
        vector<pair<int,int>> edges(n-1);
        for(int i=0; i<n-1; i++){
            cin >> edges[i].first >> edges[i].second;
            edges[i].first--;
            edges[i].second--;
        }
    
        int q;
        cin >> q;
        stack<pair<char,int>> queries;
        vector<bool> marked(n-1, false);
        while(q--){
            char ch;
            cin >> ch;
            if(ch == 'R'){
                int e;
                cin >> e;
                marked[--e] = true;
                queries.emplace(ch, e);
            } else if(ch == 'Q'){
                queries.emplace(ch, -1);
            }
        }
    
        solve(n, edges, queries, marked);
        cout << '\n';
    } 
    
    return 0;
} 