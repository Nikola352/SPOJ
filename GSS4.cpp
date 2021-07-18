#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
    
typedef long long ll;
typedef vector<ll> vi;
    
vi arr, tree, lazy;
    
void build(int v, int tl, int tr){
    if(tl == tr){
        tree[v] = arr[tl];
    } else {
        int tm = tl + (tr-tl)/2;
        build(2*v+1, tl, tm);
        build(2*v+2, tm+1, tr);
        tree[v] = tree[2*v+1] + tree[2*v+2];
    }
}
    
void update(int v, int tl, int tr,int l, int r){
    if(l > r) return;
    if(tree[v] == r-l+1) return;
    if(tl == tr){
        tree[v] = (ll)sqrt((double)tree[v]);
    } else {
        int tm = tl + (tr-tl)/2;
        update(2*v+1, tl, tm, l, min(r, tm));
        update(2*v+2, tm+1, tr, max(l, tm+1), r);
        tree[v] = tree[2*v+1] + tree[2*v+2];
    }
}
    
ll query(int v, int tl, int tr, int l, int r){
    if(l > r) 
        return 0ll;
    if(l == tl && r == tr)
        return tree[v];
    int tm = tl + (tr-tl)/2;
    return (
        query(2*v+1, tl, tm, l, min(r, tm)) +
        query(2*v+2, tm+1, tr, max(l, tm+1), r)
    );
}
    
int main()
{
    int n, cn=1;
    while(scanf("%d", &n) != EOF){
        arr.clear();
        arr.resize(n);
        for(int i=0; i<n; i++)
            scanf("%lld", &arr[i]);
    
        tree.clear(); lazy.clear();
        tree.resize(4*n); 
        lazy.resize(4*n, 0);
        build(0, 0, n-1);
    
        printf("Case #%d:\n", cn);
        cn++;
    
        int m;
        scanf("%d", &m);
        while(m--){
            int q, x, y;
            scanf("%d%d%d", &q, &x, &y);
            if(x > y) swap(x, y);
            if(q == 0){
                update(0, 0, n-1, --x, --y);
            } else if(q == 1){
                printf("%lld\n", query(0, 0, n-1, --x, --y));
            }
        }
    
        printf("\n");
    }
    
    return 0;
} 