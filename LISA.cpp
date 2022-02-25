#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int INF = numeric_limits<long long>::max();

typedef vector<long long> vi;
typedef vector<vi> vvi;

int main()
{
    int t;
    cin >> t;

    while(t--){
        string s;
        cin >> s;

        vi a, ops;
        a.reserve(s.size()/2);
        ops.reserve(s.size()/2);
        for(int i=0; i<s.size(); i++){
            if(i & 1)
                ops.push_back(s[i]);
            else
                a.push_back(s[i] - '0');
        }

        int n = a.size();

        vvi dp1(n, vi(n, 0)), dp2(n, vi(n, INF));
        for(int i=0; i<n; i++)
            dp1[i][i] = dp2[i][i] = a[i];

        for(int l=2; l<=n; l++){
            for(int i=0; i<n-l+1; i++){
                int j = i + l - 1;
                for(int k=i; k<j; k++){
                    if(ops[k] == '+'){
                        dp1[i][j] = max(dp1[i][j], dp1[i][k] + dp1[k+1][j]);
                        dp2[i][j] = min(dp2[i][j], dp2[i][k] + dp2[k+1][j]);
                    } else if(ops[k] == '*'){
                        dp1[i][j] = max(dp1[i][j], dp1[i][k] * dp1[k+1][j]);
                        dp2[i][j] = min(dp2[i][j], dp2[i][k] * dp2[k+1][j]);
                    }
                }
            }
        }

        cout << dp1[0][n-1] << ' ' << dp2[0][n-1] << '\n';

    }
    
    return 0;
}