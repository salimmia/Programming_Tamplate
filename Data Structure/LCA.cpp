vector<pair<int, int>>g[N];
int depth[N], maxcost[N][20], mncost[N][20], LOG, par[N][20], L[N][20];
/// check the constrains

struct LCA
{
    bool checkbit(int mask, int k)
    {
        return mask & (1 << k);
    }

    void dfs(int u, int p, int d)
    {
        par[u][0] = p;
        depth[u] = d;

        for(auto it: g[u]){
            int v = it.first;
            int w = it.second;
            
            if(v == p) continue;
            
            L[v][0] = w;
            dfs(v, u, d + 1);
        }
    }

    void sparse_table()
    {
        for(int k = 1; (1 << k) <= n; k++){
            for(int u = 1; u <= n; u++){
                int first_parent = par[u][k - 1];

                if(first_parent != -1){
                    par[u][k] = par[first_parent][k - 1];
                    L[u][k] = max(L[u][k - 1], L[first_parent][k - 1]);
                }
                else par[u][k] = -1;
            }
        }
    }

    ll Kth_parent(int u, int k)
    {
        for(int i = LOG; i >= 0; i--){
            if(checkbit(k, i)){
                u = par[u][i];
            }
        }
        return u;
    }

    void build_lca(int root)
    {        
        dfs(root, -1, 0);
        
        sparse_table();
    }

    ll getlca(int root, int u, int v)
    {
        if(depth[u] < depth[v]) swap(u, v);
        
        int log = 1;
        while(1){
            int next = log+1;
            
            if((1 << next) > depth[u]) break;
            
            log++;
        }
        
        for(int i = log;i >= 0; i--){
            if(depth[u] - (1 << i) >= depth[v]){
                u = par[u][i];
            }
        }
        
        if(u == v) return u;

        for(int i = log; i >= 0; i--)
        {
            if(par[u][i] != -1 && par[u][i] != par[v][i]){
                u = par[u][i];
                v = par[v][i];
            }
        }
        return par[v][0];
    }
    
    int dist(int root, int u, int v)
    {
        return depth[u] + depth[v] - 2 * depth[getlca(root, u, v)];
    }
    
    pair<int, int> query(int u,int v)
    {
        if(u == v) return 0;
        
        int mx = 0, mn = 1e9;
        
        if(depth[u] < depth[v]) swap(u,v);
        
        int diff = depth[u] - depth[v];
        
        ll re = 0;
        
        for(int i = LOG; i >= 0; i--){
            if(diff >= (1 << i)){
                diff -= (1 << i);
                
                mx = max(mx, L[u][i]);
                
                u = par[u][i];
            }
        }
        
        if(u == v) return mx;

        for(int i = LOG-1; i >= 0; i--){
            if(par[u][i] != par[v][i]){
                mx = max({mx, L[u][i], L[v][i]});
                
                u = par[u][i];
                
                v = par[v][i];
            }
        }
        
        mx = max({mx, L[u][0], L[v][0]});
        
        return mx;
    }
};
