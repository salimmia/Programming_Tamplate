int lca_after_change_root(int u, int v, int root)
{
    int u_root = lca(u, root), v_root = lca(v, root), u_v = lca(u, v);

    if (st[root] < st[u] && en[u] <= en[root] && st[v] > st[root] && en[v] <= en[root]) return u_v;

    if ((st[u] > st[root] && en[u] <= en[root]) || (st[v] > st[root] && en[v] <= en[root])) return root;

    if (depth[u_root] > depth[v_root]) return u_root;

    return v_root;
}
