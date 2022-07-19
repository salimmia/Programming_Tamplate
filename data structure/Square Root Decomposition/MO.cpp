#include<bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define INF 1e18
#define nl "\n"
#define PI 3.141592653589793238462

typedef long long int ll;
typedef unsigned long long ull;
typedef long double lld;
int const N = 2e5 + 5;

namespace MO {

int n;
int block_size;
ll block_id[N];
ll ans[N];
ll a[N];
int q;

struct Query {
    int l, r, id;
    ll ans;

    Query() {}
    Query(int l, int r, int id) : l(l), r(r), id(id) {}

    bool operator<(Query &other) const {
        int cur_block = l / block_size;
        int other_block = other.l / block_size;

        if (cur_block != other_block) return cur_block < other_block;

        return r < other.r;
    }
} query[N];

ll now;

void reset()
{
    now = 0;
    block_size = sqrt(n);
    for (int i = 0; i <= block_size; i++) block_id[i] = 0;
}

void include(int id)
{
    now += a[id];
}
void remove(int id)
{
    now -= a[id];
}

ll get_ans()
{
    return now;
}

void compute()
{
    int L = 1, R = 0;

    for (int i = 0; i < q; i++) {
        int ql = query[i].l;
        int qr = query[i].r;

        while (R < qr) include(++R);
        while (L > ql) include(--L);
        while (L < ql) remove(L++);
        while (R > qr) remove(R--);

        ans[query[i].id] = get_ans();
    }
}

}
using namespace MO;

void solve()
{
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);

    reset();

    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int l, r;

        scanf("%d%d", &l, &r);

        query[i] = Query(l, r, i);
    }

    sort(query, query + q);

    compute();

    for (int i = 0; i < q; i++) printf("%lld\n", ans[i]);

    return;
}

int main()
{
    int t = 1, cs = 1;
    // scanf("%d", &t);

    for (int i = 1; i <= t; i++) {
        // printf("Case %d: ", i);
        solve();
    }
}
