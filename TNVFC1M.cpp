#include <iostream>
#include <vector>
using namespace std;

const int K = 25;

int min(int a, int b){
    return (a < b ? a : b);
}

int max(int a, int b){
    return (a > b ? a : b);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while(cin >> n){
        int h, b, e;
        cin >> h >> b >> e;
        b--; e--;
        vector<int> c(n);
        for(int i=0; i<n; i++)
            cin >> c[i];

        vector<int> log(n+1, 0);
        for(int i=2; i<=n; i++)
            log[i] = log[i/2] + 1;

        vector<vector<int>> st(n, vector<int>(K, 0));
        vector<vector<int>> sti(n, vector<int>(K, 0));
        for(int i=0; i<n; i++){
            st[i][0] = c[i];
            sti[i][0] = i;
        }
        for(int j=1; j<K; j++){
            for(int i=0; i<n-(1<<(j-1)); i++){
                if(st[i][j-1] < st[i+(1<<(j-1))][j-1]){
                    st[i][j] = st[i][j-1];
                    sti[i][j] = sti[i][j-1];
                } else {
                    st[i][j] = st[i+(1<<(j-1))][j-1];
                    sti[i][j] = sti[i+(1<<(j-1))][j-1];
                }
            }
        }

        vector<int> res(e-b+1, 0);
        for(int r=0; r<n; r++){
            int l = max(r-h+1, 0);
            int j = log[r-l+1];
            int i = sti[r-(1<<j)+1][j];
            if(st[l][j] < st[r-(1<<j)+1][j])
                i = sti[l][j];
            if(i >= b && i <= e)
                res[i-b]++;
        }

        for(int i=0; i<e-b+1; i++)
            cout << res[i] << ' ';
        cout << '\n';
    }

    return 0;
}