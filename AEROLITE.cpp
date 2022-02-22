#include <bits/stdc++.h>
using namespace std;
    
const int MOD = 11380;
const int L = 11, D = 31;
 
int dp[L][L][L][D];
int dpa[L][L][L][D];
 
int main()
{
    int t = 10;
 
    while(t--){
        int l1, l2, l3, dep;
        cin >> l1 >> l2 >> l3 >> dep;
 
        memset(dp, 0, sizeof(dp));
        dp[0][0][0][0] = dpa[0][0][0][0] = 1;
 
        for(int d=1; d<=dep; d++){
 
            for(int i1=0; i1<=l1; i1++){
                for(int i2=0; i2<=l2; i2++){
                    for(int i3=0; i3<=l3; i3++){
 
                        for(int j1=0; j1<=i1; j1++){
                            for(int j2=0; j2<=i2; j2++){
                                for(int j3=0; j3<=i3; j3++){
 
                                    if(j1 > 0){
                                        dp[i1][i2][i3][d] += ( dp[j1-1][j2][j3][d-1] * dpa[i1-j1][i2-j2][i3-j3][d-1] ) % MOD;
                                        if(d > 1)
                                            dp[i1][i2][i3][d] += ( dpa[j1-1][j2][j3][d-2] * dp[i1-j1][i2-j2][i3-j3][d] ) % MOD;
                                        dp[i1][i2][i3][d] += ( dp[j1-1][j2][j3][d-1] * dp[i1-j1][i2-j2][i3-j3][d] ) % MOD;
                                    }
                                    else if(j2 > 0){
                                        dp[i1][i2][i3][d] += ( dp[j1][j2-1][j3][d-1] * dpa[i1-j1][i2-j2][i3-j3][d-1] ) % MOD;
                                        if(d > 1)
                                            dp[i1][i2][i3][d] += ( dpa[j1][j2-1][j3][d-2] * dp[i1-j1][i2-j2][i3-j3][d] ) % MOD;
                                        dp[i1][i2][i3][d] += ( dp[j1][j2-1][j3][d-1] * dp[i1-j1][i2-j2][i3-j3][d] ) % MOD;
                                    }
                                    else if(j3 > 0){
                                        dp[i1][i2][i3][d] += ( dp[j1][j2][j3-1][d-1] * dpa[i1-j1][i2-j2][i3-j3][d-1] ) % MOD;
                                        if(d > 1)
                                            dp[i1][i2][i3][d] += ( dpa[j1][j2][j3-1][d-2] * dp[i1-j1][i2-j2][i3-j3][d] ) % MOD;
                                        dp[i1][i2][i3][d] += ( dp[j1][j2][j3-1][d-1] * dp[i1-j1][i2-j2][i3-j3][d] ) % MOD;
 
                                    }
 
                                    dp[i1][i2][i3][d] %= MOD;
 
                                }
                            }
                        }
 
 
                        dpa[i1][i2][i3][d] = (dp[i1][i2][i3][d] + dpa[i1][i2][i3][d-1]) % MOD;
 
                    }
                }
            }
 
        }
 
        cout << dp[l1][l2][l3][dep] << '\n';
 
    }
    
    return 0;
}