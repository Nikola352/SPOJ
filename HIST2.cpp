#include <iostream>
using namespace std;
 
const int N = 15;
 
int h[N];
pair<int, int> dp[N][1<<N];
 
int main()
{
    int n;
    cin >> n;
    
    while(n > 0){
        for(int i=0; i<n; i++)
            cin >> h[i];
 
        for(int i=0; i<n; i++){
            for(int mask=0; mask<(1<<n); mask++){
                dp[i][mask] = {0,0};
            }
        }
 
        for(int i=0; i<n; i++)
            dp[i][1<<i] = {2*h[i], 1};
 
        for(int mask=0; mask<(1<<n); mask++){
            for(int i=0; i<n; i++){
                if(!(mask & (1<<i))) continue;
 
                for(int j=0; j<n; j++){
                    if(mask & (1<<j) && j != i){
                        auto prev = dp[j][mask ^ (1<<i)];
 
                        int pot = prev.first;
                        if(h[i] > h[j]) pot += 2 * (h[i] - h[j]);
 
                        if(pot > dp[i][mask].first)
                            dp[i][mask] = {pot, prev.second};
                        else if(pot == dp[i][mask].first)
                            dp[i][mask].second += prev.second;
 
                    }
                }
 
            }
        }
 
        int maxp = 0, cnt = 0;
        for(int i=0; i<n; i++){
            if(dp[i][(1<<n)-1].first > maxp){
                maxp = dp[i][(1<<n)-1].first;
                cnt = dp[i][(1<<n)-1].second;
            } else if(dp[i][(1<<n)-1].first == maxp){
                cnt += dp[i][(1<<n)-1].second;
            }
        }
 
        cout << (maxp + 2*n) << ' ' << cnt << '\n';
 
        cin >> n;
    }
 
 
    return 0;
}