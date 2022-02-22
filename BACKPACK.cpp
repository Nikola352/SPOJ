#include <bits/stdc++.h>
using namespace std;
 
struct Item{
    int v, c, u;
    int na;
    int adds[3];
    Item(){
        na = 0;
    }
};
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int t;
    cin >> t;
 
    while(t--){
        int v, n;
        cin >> v >> n;
        vector<Item> a(n);
        for(int i=0; i<n; i++){
            cin >> a[i].v >> a[i].c >> a[i].u;
            a[i].u--;
            if(a[i].u != -1)
                a[a[i].u].adds[a[a[i].u].na++] = i;
        }
 
        int res = 0;
 
        vector<int> dp(v+1, 0);
 
        for(int i=0; i<n; i++){
            if(a[i].u != -1) continue;
 
            for(int j=v; j>=0; j--){
                for(int mask=0; mask<(1<<a[i].na); mask++){
                    int cv = j - a[i].v, val = a[i].v * a[i].c;
                    for(int ui=0; ui<a[i].na; ui++){
                        if(mask & (1<<ui)){
                            int u = a[i].adds[ui];
                            cv -= a[u].v;
                            val += a[u].v * a[u].c;
                        }
                    }
                    if(cv >= 0)
                        dp[j] = max(dp[j], dp[cv] + val);
                }
 
                res = max(res, dp[j]);
            }
        }
 
        cout << res << '\n';
 
    }
    
    return 0;
}