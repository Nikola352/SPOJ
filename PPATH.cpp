#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n){
    if(n < 2) return false;
    if(n == 2 || n == 3) return true;
    if(n%2==0 || n%3==0) return false;
    for(int i=5; i*i<n; i+=6){
        if(n % i == 0) return false;
        if(n % (i+2) == 0) return false;
    }
    return true;
}

int minCost(int a, int b){
    unordered_set<int> visited;
    queue<pair<int,int>> q;
    q.push(make_pair(a, 0));
    while(!q.empty()){
        int v = q.front().first,
            lvl = q.front().second;
        q.pop();
        if(visited.find(v) == visited.end()){
            visited.insert(v);
            if(v == b){
                return lvl;
            } 
            int d = 1;
            for(int i=0; i<4; i++){
                int dig = v/d % 10;
                for(int j=0; j<10; j++){
                    if(dig == j) continue;
                    int u = v - d*dig + d*j;
                    if(u < 1000) continue;
                    if(!isPrime(u)) continue;
                    if(isPrime(u) && visited.find(u) == visited.end())
                        q.push(make_pair(u, lvl+1));
                }
                d *= 10;
            }
        }
    }
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    
    while(t--){
        int a, b;
        cin >> a >> b;
        int res = minCost(a, b);
        if(res == -1) cout << "Impossible\n";
        else cout << res << '\n';
    }

    return 0;
}