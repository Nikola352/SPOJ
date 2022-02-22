#include <iostream>
#include <vector>
using namespace std;
 
typedef vector<int> vi;
typedef vector<vi> vvi;
 
vi calc(int n){
    vi res(n+1, 1);
 
    vvi dp(n+1, vi(16, 0));
    dp[0][15] = 1;
 
    for(int i=1; i<=n; i++){
        dp[i][0] = dp[i-1][15];
        for(int mask=1; mask<16; mask++){
            dp[i][mask] += dp[i-1][~mask & 15];
            for(int j=0; j<3; j++){
                if((mask & (1<<j)) && (mask & (1<<j+1)))
                    dp[i][mask] += dp[i-1][(~mask & 15) ^ (1<<j | 1<<j+1)];
            }
            if(mask == 15) dp[i][mask] += dp[i-1][15];
        }
        res[i] = dp[i][15];
    }
 
    return res;
}
 
int main()
{
    int n;
    cin >> n;
 
    int maxw = 0;
    vi w(n);
    for(int i=0; i<n; i++){
        cin >> w[i];
        maxw = max(maxw, w[i]);
    }
 
    vi res = calc(maxw);
 
    for(int i=0; i<n; i++)
        cout << i+1 << ' ' << res[w[i]] << '\n';
    
    return 0;
}