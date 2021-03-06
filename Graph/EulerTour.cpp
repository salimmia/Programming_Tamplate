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

/// Type 2:

ll Linear[N], st[N], en[N], timer;

void dfs(int u, int p)
{
    st[u] = ++timer;
    Linear[timer] = u;

    for (auto v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    en[u] = ++timer;
    Linear[timer] = u;
}

/// Type 3: path from root to any node

ll Linear[N], st[N], en[N], timer;

void dfs(int u, int p)
{
    st[u] = ++timer;
    Linear[timer] = u;

    for (auto v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    en[u] = timer;
    Linear[timer] = u;
}

