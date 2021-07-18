#include <bits/stdc++.h>
using namespace std;

struct Query{
    int y, x, i;
};

bool compQ(const Query& a, const Query& b){
    return (a.y < b.y);
}

class Segtree{
private:
    int n;
    vector<int> curr, best, lazy, best_lazy;

    void push(int v){
        for(int child=2*v+1; child<=2*v+2; child++){
            best_lazy[child] = max(best_lazy[child], lazy[child]+best_lazy[v]);
            lazy[child] += lazy[v];
            best[child] = max(best[child], curr[child] + best_lazy[v]);
            curr[child] += lazy[v];
        }
        lazy[v] = best_lazy[v] = 0;
    }

    void build(int v, int tl, int tr){
        curr[v] = best[v] = lazy[v] = best_lazy[v] = 0;
        if(tl == tr) return;
        int tm = tl + (tr-tl)/2;
        build(2*v+1, tl, tm);
        build(2*v+2, tm+1, tr);
    }

    void updateUtil(int v, int tl, int tr, int l, int r, int add){
        if(l > r) return;
        if(l == tl && r == tr){
            curr[v] += add;
            best[v] = max(best[v], curr[v]);
            lazy[v] += add;
            best_lazy[v] = max(best_lazy[v], lazy[v]);
        } else {
            push(v);
            int tm = tl + (tr-tl)/2;
            updateUtil(2*v+1, tl, tm, l, min(r, tm), add);
            updateUtil(2*v+2, tm+1, tr, max(l, tm+1), r, add);
            curr[v] = max(curr[2*v+1], curr[2*v+2]);
            best[v] = max(best[v], curr[v]);
        }
    }

    int query(int v, int tl, int tr, int l, int r){
        if(l > r) return 0;
        if(l == tl && r == tr)
            return best[v];
        push(v);
        int tm = tl + (tr-tl)/2;
        return max(
            query(2*v+1, tl, tm, l, min(r, tm)),
            query(2*v+2, tm+1, tr, max(l, tm+1), r)
        );
    }

public:
    Segtree(int n) : n(n) {
        curr.resize(4*n);
        best.resize(4*n);
        lazy.resize(4*n);
        best_lazy.resize(4*n);
        build(0, 0, n-1);
    }

    int get(int l, int r){
        return query(0, 0, n-1, l, r);
    }

    void update(int l, int r, int val){
        updateUtil(0, 0, n-1, l, r, val);
    }

};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int arr[n];
    for(int i=0; i<n; i++)
        cin >> arr[i];

    Segtree segtree(n);

    int q;
    cin >> q;
    vector<Query> qu(q);
    for(int i=0; i<q; i++){
        cin >> qu[i].x >> qu[i].y;
        qu[i].i = i;
    }

    sort(qu.begin(), qu.end(), compQ);

    map<int, int> li;
    vector<int> res(q);

    int e = 0;
    for(int i=0; i<q; i++){
        while(qu[i].y > e){
            if(li.find(arr[e]) == li.end()){
                segtree.update(0, e, arr[e]);
            } else {
                segtree.update(li[arr[e]], e, arr[e]);
            }
            li[arr[e]] = e + 1;
            e++;
        }
        res[qu[i].i] = segtree.get(--qu[i].x, --qu[i].y);
    }

    for(int i=0; i<q; i++)
        cout << res[i] << '\n';

    return 0;
}