#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
int main()
{
    int t;
    cin >> t;
 
    while(t--){
        int n, p;
        cin >> n >> p;
        vector<bool> isopen(2*n);
        for(int i=0; i<p; i++){
            int s; cin >> s;
            isopen[--s] = true;
        }
 
        vector<vector<ll>> dp(n+1, vector<ll>(2*n, 0));
        dp[1][0] = 1;
 
        for(int i=1; i<=n; i++){
            for(int j=1; j<2*n; j++){
                if(j>=i-1 && j<2*i-1)
                    dp[i][j] = dp[i-1][j-1];
                if(!isopen[j])
                    dp[i][j] += dp[i][j-1];
            }
        }
        
        cout << dp[n][2*n-1] << '\n';
 
    }
 
    return 0;
}