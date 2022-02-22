#include <iostream>
#include <vector>
using namespace std;

const int K = 25;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for(int i=0; i<n; i++)
        cin >> arr[i];

    vector<int> log(n+1, 0);
    for(int i=2; i<=n; i++)
        log[i] = log[i/2] + 1;

    vector<vector<int>> st(n+1, vector<int>(K));
    for(int i=0; i<n; i++)
        st[i][0] = arr[i];
    for(int j=0; j<K; j++)
        for(int i=0; i<n-(1<<(j-1)); i++)
            st[i][j] = max(st[i][j-1], st[i+(1<<(j-1))][j-1]);

    int c = 0;
    while(m--){
        int a, b;
        cin >> a >> b;
        a--; b--;
        if(a > b) swap(a, b);
        b--;
        int j = log[b-a+1];
        if(arr[a] == max(st[a][j], st[b-(1<<j)+1][j])) c++;
    }

    cout << c << '\n';

    return 0;
}