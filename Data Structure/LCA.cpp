struct LCA
{
    bool checkbit(int mask, int k)
    {
        return mask & (1 << k);
    }

    void dfs(int u, int p, int d)
    {
        sp_par[u][0] = p;
        depth[u] = d;

        for(auto v: g[u]){
            if(v.first == p) continue;
            
            cost[v.first][0] = v.second;
            dfs(v.first, u, d + 1);
        }
    }

    void sparse_table()
    {
        for(int k = 1; (1 << k) <= n; k++){
            for(int u = 1; u <= n; u++){
                int first_parent = sp_par[u][k - 1];

                if(first_parent != -1){
                    sp_par[u][k] = sp_par[first_parent][k - 1];
                    cost[u][k] = max(cost[u][k - 1], cost[first_parent][k - 1]);
                }
            }
        }
    }

    ll Kth_parent(int u, int k)
    {
        FOR(i, 0, 20){
            if(checkbit(k, i)){
                u = sp_par[u][i];
            }
        }
        return u;
    }

    void build_lca(int root)
    {
        for(int i = 0; i <= n; i++){
            for(int j = 0; (1 << j) <= n; j++){
                sp_par[i][j] = -1;
            }
        }
        
        dfs(1, -1, 0);
        
        sparse_table();
    }

    ll getlca(int root, int u, int v)
    {
        if(depth[u] > depth[v]){
            u = Kth_parent(u, depth[u] - depth[v]);
        }
        else if(depth[u] < depth[v]){
            v = Kth_parent(v, depth[v] - depth[u]);
        }

        
        if(u == v) return u;
        

        ll lo = 0, hi = depth[u], ans = 1;

        while (lo < hi)
        {
            ll mid = (lo + hi) >> 1;

            int p = Kth_parent(u, mid);
            int q = Kth_parent(v, mid);

            if(p == q){
                hi = mid;
                ans = p;
            }
            else lo = mid + 1;
        }
        return ans;
    }
    int query(int u, int v, int lca)
    {
        int ret = 0;
        int dis = depth[u] - depth[lca];
        
        for(int i = 18; i >= 0; i--){
            if(checkbit(dis, i)){
                ret = max(ret, cost[u][i]);
                u = sp_par[u][i];
            }
        }
        dis = depth[v] - depth[lca];
        for(int i = 18; i >= 0; i--){
            if(checkbit(dis, i)){
                ret = max(ret, cost[v][i]);
                v = sp_par[v][i];
            }
        }
        return ret;
    }
};
