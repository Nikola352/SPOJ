#include <bits/stdc++.h>
using namespace std;
 
const int INF = numeric_limits<int>::max();
 
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vii;
 
struct Node{
    int r, c, dist;
    Node(int r, int c, int d) : r(r), c(c), dist(d) {}
};
 
struct cmp{
    bool operator()(const Node& a, const Node& b){
        return a.dist > b.dist;
    }
};
 
pii pom[4] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
 
vi dijkstra(pii src, int n, int m, vector<string>& arr, vii& buildings){
    vvi dist(n, vi(m, INF));
    vvb vis(n, vb(m, false));
    priority_queue<Node, vector<Node>, cmp> pq;
 
    dist[src.first][src.second] = 0;
    pq.emplace(src.first, src.second, 0);
 
    while(!pq.empty()){
        int vr = pq.top().r, vc = pq.top().c;
        pq.pop();
 
        if(vis[vr][vc]) continue;
        vis[vr][vc] = true;
 
        if(dist[vr][vc] == INF) continue;
 
        for(int p=0; p<4; p++){
            int ur = vr + pom[p].first,
                uc = vc + pom[p].second;
            if(ur<0 || ur>=n || uc<0 || uc>=m) continue;
 
            int d = -1;
            if(arr[ur][uc] == '$' || arr[ur][uc] == 'X' || arr[vr][vc] == '$' || arr[vr][vc] == 'X')
                d = 2;
            else if(arr[vr][vc] == arr[ur][uc])
                d = 1;
            else if(abs(arr[vr][vc] - arr[ur][uc]) == 1)
                d = 3;
 
            if(d == -1) continue;
 
            if(dist[vr][vc] + d < dist[ur][uc]){
                dist[ur][uc] = dist[vr][vc] + d;
                pq.emplace(ur, uc, dist[ur][uc]);
            }
        }
    }
 
    int z = buildings.size();
    vi res(z);
    for(int i=0; i<z; i++)
        res[i] = dist[buildings[i].first][buildings[i].second];
    return res;
}
 
int calc(const vi& dist){
    int n = dist.size();
 
    vi time(1<<n, 0);
 
    for(int mask=0; mask<(1<<n); mask++){
        int maxt = 0;
        for(int i=0; i<n; i++){
            if(mask & (1<<i)){
                time[mask] += 2 * dist[i];
                maxt = max(maxt, dist[i]);
            }
        }
        time[mask] -= maxt;
    }
 
    int res = INF;
    for(int mask=0; mask<(1<<n); mask++){
        int mask2 = ( (1<<n)-1 ) ^ mask;
        res = min(res, max(time[mask], time[mask2]));
    }
 
    return res;
}
 
int main()
{
    int t;
    cin >> t;
 
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<string> arr(n);
        for(int i=0; i<n; i++)
            cin >> arr[i];
 
        pii src;
        vii buildings;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(arr[i][j] == 'X')
                    src = {i, j};
                else if(arr[i][j] == '$')
                    buildings.emplace_back(i, j);
            }
        }
 
        vi dist = dijkstra(src, n, m, arr, buildings);
 
        bool ok = true;
        for(int d : dist){
            if(d == INF){
                ok = false; break;
            }
        }
 
        if(ok) cout << calc(dist) << '\n';
        else cout << "-1\n";
    }
    
    return 0;
}