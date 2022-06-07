struct Kruskal
{
    void init()
    {
        for(int i = 0; i <= n; i++){
            parent[i] = i;
            g[i].clear();
        }
    }
    int Find(int u)
    {
        if(u == parent[u]) return u;
        return parent[u] = Find(parent[u]);
    }
    
    void Union(int u, int v)
    {
        if(Rank[u] >= Rank[v]){
            parent[v] = u;
            Rank[u]++;
        }
        else{
            parent[u] = v;
            Rank[v]++;
        }
    }

    ll build_kruskal()
    {
        init();
        int cnt = 0;
        ll cost = 0;
        for(auto p: edge){
            int w = p.first;
            int u = p.second.first;
            int v = p.second.second;
            int paru = Find(u);
            int parv = Find(v);
            if(paru != parv){
                Union(paru, parv);
                
                cnt++;
                
                g[u].pb({v, w});
                g[v].pb({u, w});
                cost += w;
                
                if(cnt == n - 1) break;
            }
        }
        return cost;
    }
};
