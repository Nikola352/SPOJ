#include <iostream>
#include <vector>
using namespace std;

const int K = 25;

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i=0; i<n; i++)
        cin >> arr[i];

    vector<vector<int>> st(n+1, vector<int>(K));
    for(int i=0; i<n; i++)
        st[i][0] = arr[i];
    for(int j=1; j<K; j++){
        for(int i=0; i<=n-(1<<(j-1)); i++)
            st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
    }

    vector<int> log(n+1, 0);
    for(int i=2; i<=n; i++)
        log[i] = log[i/2] + 1;

    int q;
    cin >> q;
    while(q--){
        int l, r;
        cin >> l >> r;
        int j = log[r-l+1];
        cout << min(st[l][j], st[r-(1<<j)+1][j]) << '\n';
    }

    return 0;
}