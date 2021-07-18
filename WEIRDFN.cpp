#include <bits/stdc++.h> 
using namespace std;
    
#define ll long long
const int MOD = 1000000007;
    
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while(t--){
        int a, b, c, n;
        cin >> a >> b >> c >> n;
    
        priority_queue<int> maxheap;
        priority_queue<int, vector<int>, greater<int>> minheap;
    
        int f = 1;
        ll sum = f;
        maxheap.push(f);
        for(int i=2; i<=n; i++){
            f = (((ll)a*maxheap.top() % MOD) + ((ll)b*i % MOD) + c) % MOD;
            sum += f;
    
            if(f < maxheap.top())
                maxheap.push(f);
            else
                minheap.push(f);
    
            while(maxheap.size() > (i+1)/2){
                minheap.push(maxheap.top());
                maxheap.pop();
            }
    
            while(maxheap.size() < (i+1)/2){
                maxheap.push(minheap.top());
                minheap.pop();
            }
        }
    
        cout << sum << endl;
    }
    
    return 0;
} 