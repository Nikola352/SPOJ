// WA 
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
struct Node{
    int a, b, c, la, lb, lc;
    Node(int aa, int ab, int ac, int ala, int alb, int alc){
        a = aa; b = ab; c = ac;
        la = ala; lb = alb; lc = alc;
    }
};

const int MOD = 10007;

vector<Node> tree;
vi as;

int asum(int l, int r){
    if(l == 0) return as[r];
    return (as[r] - as[l-1] + MOD) % MOD;
}

int bsum(int l, int r){
    return (((r+l) % MOD) * ((r-l+1) % MOD) % MOD) / 2 % MOD;
}

int csum(int l, int r){
    return (r-l+1) % MOD;
}

Node combine(const Node& n1, const Node& n2){
    Node node(0,0,0,0,0,0);
    node.a = (n1.a + n2.a) % MOD;
    node.b = (n1.b + n2.b) % MOD;
    node.c = (n1.c + n2.c) % MOD;
    return node;
}

void push(int v, int tl, int tm, int tr){
    int l, r;
    for(int c=2*v+1; c<=2*v+2; c++){
        if(c == 2*v + 1) {
            l = tl;
            r = tm;
        } else {
            l = tm+1;
            r = tr;
        }
        tree[c].a += asum(l,r)*tree[v].la;
        tree[c].a %= MOD;
        tree[c].b += bsum(l,r)*tree[v].lb;
        tree[c].b %= MOD;
        tree[c].c += csum(l,r)*tree[v].lc;
        tree[c].c %= MOD;
        tree[c].la += tree[v].la;
        tree[c].la %= MOD;
        tree[c].lb += tree[v].lb;
        tree[c].lb %= MOD;
        tree[c].lc += tree[v].lc;
        tree[c].lc %= MOD;
    }
    tree[v].la = tree[v].lb = tree[v].lc = 0;
}

void update(int v, int tl, int tr,int l, int r, int aa, int ab, int ac){
    if(l > r) return;
    if(l == tl && r == tr){
        tree[v].a += asum(l,r)*aa % MOD;
        tree[v].a %= MOD;
        tree[v].b += bsum(l,r)*ab % MOD;
        tree[v].b %= MOD;
        tree[v].c += csum(l,r)*ac % MOD;
        tree[v].c %= MOD;
        tree[v].la += aa % MOD;
        tree[v].la %= MOD;
        tree[v].lb += ab % MOD;
        tree[v].lb %= MOD;
        tree[v].lc += ac % MOD;
        tree[v].lc %= MOD;
    } else {
        int tm = tl + (tr-tl)/2;
        push(v, tl, tm, tr);
        update(2*v+1, tl, tm, l, min(r, tm), aa, ab, ac);
        update(2*v+2, tm+1, tr, max(l, tm+1), r, aa, ab, ac);
        tree[v] = combine(tree[2*v+1], tree[2*v+2]);
    }
}

Node query(int v, int tl, int tr, int l, int r){
    if(l > r) 
        return {0,0,0,0,0,0};
    if(l == tl && r == tr)
        return tree[v];
    int tm = tl + (tr-tl)/2;
    push(v, tl, tm, tr);
    return combine(
        query(2*v+1, tl, tm, l, min(r, tm)),
        query(2*v+2, tm+1, tr, max(l, tm+1), r)
    );
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    as.clear();
    as.resize(n);
    as[0] = 0;
    for(long long i=1; i<n; i++)
        as[i] = as[i-1] + (i*i % MOD) % MOD;

    tree.clear(); 
    tree.resize(4*n, {0,0,0,0,0,0});

    while(m--){
        int q, x0, x1;
        cin >> q >> x0 >> x1;
        if(q == 0){
            int a, b, c;
            cin >> a >> b >> c;
            a %= MOD; b %= MOD; c %= MOD;
            update(0, 0, n-1, x0, x1, a, b, c);
        } else if(q == 1){
            Node node = query(0, 0, n-1, x0, x1);
            int res = (node.a + node.b + node.c) % MOD;
            cout << res << '\n';
        }
    }

    return 0;
}