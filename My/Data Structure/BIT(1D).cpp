struct Fenwick {
    int N, K = 20; vector<long long> ft;
    Fenwick(int n) : N(n + 1), ft(n + 1) {}
    void upd(int x, long long val) {
        for (int i = x; i < N; i += i & -i) ft[i] += val;
    }
    ll query(int x) {
        long long ans = 0;
        for (int i = x; i > 0; i -= i & -i) ans += ft[i];
        return ans;
    }
    ///first k st query(k)>=x, if none returns N=n+1.
    int get(long long x) {
        int ans = 0;
        for (int i = K - 1; i >= 0; i--) {
            int nxt = ans + (1 << i);
            if (nxt < N && ft[nxt] < x) {
                ans = nxt; x -= ft[nxt];
            }
        }
        return ans + 1;
    }
    ll range_query(int l, int r) {return query(r) - query(l - 1);}
    ll range_upd(int l, int r, ll val) {upd(l, val), upd(r + 1, -val);}
};
