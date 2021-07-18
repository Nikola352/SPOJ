#include <bits/stdc++.h>
using namespace std;
 
int minSmoke(int n, int arr[100]){
    int col[100][100];
    for(int i=0; i<n; i++){
        col[i][i] = arr[i];
        for(int j=i+1; j<n; j++){
            col[i][j] = (col[i][j-1] + arr[j]) % 100;
        }
    }
 
    int smoke[100][100];
    for(int i=0; i<n; i++){
        smoke[i][i] = 0;
    }
    for(int l=2; l<=n; l++){
        for(int i=0; i<n-l+1; i++){
            int j = i+l-1;
            int mins = INT_MAX;
            for(int k=i; k<j; k++){
                int pot = smoke[i][k] + smoke[k+1][j] + col[i][k]*col[k+1][j];
                if(pot < mins)
                    mins = pot;
            }
            smoke[i][j] = mins;
        }
    }
    return smoke[0][n-1];
}
 
int main() {
    int n;
    int arr[100];
 
    while(cin >> n){
        for(int i=0; i<n; i++)
            cin >> arr[i];
        cout << minSmoke(n, arr) << endl;
    }
 
    return 0;
}