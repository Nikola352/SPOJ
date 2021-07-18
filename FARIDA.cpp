#include <bits/stdc++.h> 
using namespace std;
    
#define ll long long
    
ll max(ll& a, ll& b){ return (a>b ? a : b); }
    
int main()
{
    int t;
    cin >> t;
    
    for(int tc=1; tc<=t; tc++){
        int n;
        cin >> n;
    
        ll ends=0, not_ends=0;
    
        for(int i=0; i<n; i++){
            ll num;
            cin >> num;
            ll temp = ends;
            ends = not_ends + num;
            not_ends = max(not_ends, temp);
        }
    
        ll x = max(not_ends, ends);
    
        cout << "Case " << tc << ": " << x << '\n';
    }
    
    return 0;
} 