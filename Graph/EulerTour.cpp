/// Type 1:

ll Linear[N], st[N], en[N], timer;

void dfs(int u, int p)
{
    Linear[++timer] = u;

    st[u] = timer;

    for (auto v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
        Linear[++timer] = u;
    }
    en[u] = timer;
}
