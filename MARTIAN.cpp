#include <iostream>
using namespace std;
 
const int MAXN = 500;
 
int a[MAXN][MAXN], b[MAXN][MAXN];
 
int dp[MAXN][MAXN];
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int n, m;
    cin >> n >> m;
 
    while(n != 0 && m != 0){
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                cin >> a[i][j];
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                cin >> b[i][j];
 
        for(int i=0; i<n; i++)
            for(int j=1; j<n; j++)
                a[i][j] += a[i][j-1];
 
        for(int i=1; i<n; i++)
            for(int j=0; j<m; j++)
                b[i][j] += b[i-1][j];
 
        for(int i=0; i<n; i++)
            dp[i][0] = max(a[i][0] + dp[i-1][0], b[i][0]);
 
        for(int j=0; j<m; j++)
            dp[0][j] = max(a[0][j], b[0][j] + dp[0][j-1]);
 
        for(int i=1; i<n; i++)
            for(int j=1; j<m; j++)
                dp[i][j] = max(dp[i-1][j] + a[i][j], dp[i][j-1] + b[i][j]);
 
        cout << dp[n-1][m-1] << '\n';
 
        cin >> n >> m;
    }
 
    return 0;
}