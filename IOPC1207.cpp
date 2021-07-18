#include <bits/stdc++.h>
using namespace std;
    
typedef long long ll;
    
struct Node{
    ll red;
    bool lazy;
};
    
vector<Node> stx, sty, stz;
    
void push(vector<Node>& tree, int v, int tl, int tr){
    if(tree[v].lazy){
        tree[v].red = (tr-tl+1) - tree[v].red;
        if(tl != tr){
            tree[2*v+1].lazy = !tree[2*v+1].lazy;
            tree[2*v+2].lazy = !tree[2*v+2].lazy;
        }
        tree[v].lazy = 0;
    } 
}
    
void update(vector<Node>& tree, int v, int tl, int tr, int l, int r){
    push(tree, v, tl, tr);
    if(tl > r || tr < l) return;
    if(tl >= l && tr <= r){
        tree[v].red = (tr-tl+1) - tree[v].red;
        if(tl != tr){
            tree[2*v+1].lazy = !tree[2*v+1].lazy;
            tree[2*v+2].lazy = !tree[2*v+2].lazy;
        }
        tree[v].lazy = 0;
    } else {
        int tm = tl + (tr-tl)/2;
        update(tree, 2*v+1, tl, tm, l, min(r, tm));
        update(tree, 2*v+2, tm+1, tr, max(l, tm+1), r);
        tree[v].red = tree[2*v+1].red + tree[2*v+2].red;
    }
}
    
ll query(vector<Node>& tree, int v, int tl, int tr, int l, int r){
    push(tree, v, tl, tr);
    if(tl > r || tr < l)
        return 0;
    if(tl >= l && tr <= r)
        return tree[v].red;
    int tm = tl + (tr-tl)/2;
    return (
        query(tree, 2*v+1, tl, tm, l, min(r, tm)) +
        query(tree, 2*v+2, tm+1, tr, max(l, tm+1), r)
    );
}
    
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while(t--){
        int nx, ny, nz;
        cin >> nx >> ny >> nz;
        stx.clear();
        sty.clear();
        stz.clear();
        stx.resize(4*nx, {0, 0});
        sty.resize(4*ny, {0, 0});
        stz.resize(4*nz, {0, 0});
    
        int q;
        cin >> q;
        while(q--){
            int type;
            cin >> type;
            if(type == 0){
                int i, j;
                cin >> i >> j;
                update(stx, 0, 0, nx-1, i, j);
            } else if(type == 1){
                int i, j;
                cin >> i >> j;
                update(sty, 0, 0, ny-1, i, j);
            } else if(type == 2){
                int i, j;
                cin >> i >> j;
                update(stz, 0, 0, nz-1, i, j);
            } else if(type == 3){
                int x1, x2, y1, y2, z1, z2;
                cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
                int sx = x2-x1+1, sy = y2-y1+1, sz = z2-z1+1;
                ll rx = query(stx, 0, 0, nx-1, x1, x2),
                    ry = query(sty, 0, 0, ny-1, y1, y2),
                    rz = query(stz, 0, 0, nz-1, z1, z2);
                ll gx = (x2-x1+1) - rx,
                    gy = (y2-y1+1) - ry,
                    gz = (z2-z1+1) - rz;
                ll ans = 1ll*rx*ry*rz;
                ans += 1ll*rx*gy*gz;
                ans += 1ll*gx*ry*gz;
                ans += 1ll*gx*gy*rz;
                cout << ans << '\n';
            }
        }    
    }
    
    return 0;
} 