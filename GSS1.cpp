#include <bits/stdc++.h>
using namespace std;
    
struct Node{
    int sum, msum, lsum, rsum;
};
    
Node combine(const Node& left, const Node& right){
    Node node;
    node.sum = left.sum + right.sum;
    node.lsum = max(left.lsum, left.sum + right.lsum);
    node.rsum = max(right.rsum, right.sum + left.rsum);
    node.msum = left.rsum + right.lsum;
    if(left.msum > node.msum)
        node.msum = left.msum;
    if(right.msum > node.msum)
        node.msum = right.msum;
    return node;
}
    
void build(Node segtree[], int arr[],  int v, int tl, int tr){
    if(tl == tr){
        segtree[v] = {arr[tl], arr[tl], arr[tl], arr[tl]};
    } else {
        int tm = tl + (tr-tl)/2;
        build(segtree, arr, 2*v+1, tl, tm);
        build(segtree, arr, 2*v+2, tm+1, tr);
        segtree[v] = combine(segtree[2*v+1], segtree[2*v+2]);
    }
}
    
Node query(Node segtree[], int v, int tl, int tr, int l, int r){
    if(l == tl && r == tr)
        return segtree[v];
    int tm = tl + (tr-tl)/2;
    if(r <= tm)
        return query(segtree, 2*v+1, tl, tm, l, r);
    if(l > tm)
        return query(segtree, 2*v+2, tm+1, tr, l, r);
    return combine(
        query(segtree, 2*v+1, tl, tm, l, tm),
        query(segtree, 2*v+2, tm+1, tr, tm+1, r)
    );
}
    
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int arr[n];
    for(int i=0; i<n; i++)
        cin >> arr[i];
    
    Node segtree[4*n];
    build(segtree, arr, 0, 0, n-1);
    
    int m;
    cin >> m;
    while(m--){
        int x, y;
        cin >> x >> y;
        cout << query(segtree, 0, 0, n-1, --x, --y).msum << '\n';
    }
    
    return 0;
} 