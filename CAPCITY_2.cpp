    #include <bits/stdc++.h>
    using namespace std;
     
    typedef vector<bool> vb;
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    typedef stack<int> sti;
     
    void dfs(int v, int& time, const vvi& adj, vb& visited, vi& disc, vi& low, sti& st, vb& inSt, vvi& scc){
        visited[v] = true;
        disc[v] = low[v] = time++;
        st.push(v);
        inSt[v] = true;
     
        for(int u : adj[v]){
            if(!visited[u]){
                dfs(u, time, adj, visited, disc, low, st, inSt, scc);
                low[v] = min(low[v], low[u]);
            } else if(inSt[v]){
                low[v] = min(low[v], disc[u]);
            }
        }
     
        if(low[v] == disc[v]){
            vi nodes;
            while(st.top() != v){
                int u = st.top();
                nodes.push_back(u);
                st.pop();
                inSt[u] = false;
            }
            nodes.push_back(v);
            st.pop();
            inSt[v] = false;
            scc.push_back(nodes);
        }
    }
     
    vi capital(int n, const vvi& adj){
        vb visited(n, false), inSt(n, false);
        vi disc(n), low(n);
        sti st;
        vvi scc;
        int time = 0;
        for(int i=0; i<n; i++){
            if(!visited[i])
                dfs(i, time, adj, visited, disc, low, st, inSt, scc);
        }
     
        int sccN = scc.size();
        
        vi sccMap(n);
        for(int i=0; i<sccN; i++){
            for(int j : scc[i]){
                sccMap[j] = i;
            }
        }
     
        vi outdegree(sccN, 0);
        for(int i=0; i<n; i++){
            int v = sccMap[i];
            for(int j : adj[i]){
                int u = sccMap[j];
                if(v != u)
                    outdegree[v]++;
            }
        }
     
        int head = -1;
        for(int i=0; i<sccN; i++){
            if(outdegree[i] == 0){
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
        sort(scc[head].begin(), scc[head].end());
        return scc[head];
    }
     
    int main()
    {
        int n, m;
        cin >> n >> m;
        vvi adj(n);
        for(int i=0; i<m; i++){
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[u].push_back(v);
        }
     
        vi cand = capital(n, adj);
        if(cand.empty()){
            cout << "0\n";
        } else {
            cout << cand.size() << '\n';
            for(int v : cand)
                cout << v+1 << ' ';
            cout << '\n';
        }
     
        return 0;
    } 