struct segtree{
    vector<ll>tree, lazy, a;
    void init(int x){
        tree.resize(4*(x+5));
        lazy.resize(4*(x+5));
        a.resize(x+5);
    }
    ll Merge(ll l, ll r)
    {
        return l + r;    
    }
    
    void build (int cn,int b,int e) {
        if (b == e) {
            tree[cn] = a[b];
            return;
        }
        int lc = 2*cn, rc = lc+1, mid = (b+e)/2;
        build(lc,b,mid);
        build(rc,mid+1,e);
        tree[cn] = Merge(tree[lc], tree[rc]);
    }
    void relax (int cn, int b, int e) {
        if (lazy[cn]) {
            tree[cn] += (e-b+1)*lazy[cn] ;
            if (b != e) {
                lazy[2*cn] += lazy[cn] ;
                lazy[2*cn + 1] += lazy[cn] ;
            }
            lazy[cn] = 0;
        }
    }
    void upd (int cn, int b, int e, int i, int j, int add) {
        relax(cn,b,e);
        if (b > j or e < i) {
            return;
        }
        int lc = 2*cn , rc = lc + 1 , mid = (b+e)/2;
        if (b >= i and e <= j) {
            lazy[cn] += add;
            relax(cn,b,e);
            return;
        }
        upd(lc,b,mid,i,j,add);
        upd(rc,mid+1,e,i,j,add);
        tree[cn] = Merge(tree[lc], tree[rc]);
    }
    ll query (int cn, int b, int e, int i, int j) {
        relax(cn,b,e);
        if (b > j or e < i) return 0;
        if (b >= i and e <= j) {
            return tree[cn];
        }
        int lc = 2*cn, rc = lc + 1, mid = (b+e)/2;
        ll p = query(lc,b,mid,i,j);
        ll q = query(rc,mid+1,e,i,j);
        
        return Merge(p, q);
    }
};
