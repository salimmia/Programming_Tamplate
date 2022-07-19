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
ll a[N], st[N], en[N], node[N], freq[N];
int timer, q;
bool taken[2 * N];

struct Query {
	int l, r, id, lca;
	ll ans;

	Query() {}
	Query(int l, int r, int id, int lca) : l(l), r(r), id(id), lca(lca) {}

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
	block_size = sqrt(timer);
	for (int i = 0; i <= block_size; i++) block_id[i] = 0;
	for (int i = 0; i <= n; i++) freq[i] = 0, taken[i] = false;
}

void include(int id)
{
	int u = node[id];
	if (taken[u]) {
		freq[a[u]]--;
		if (freq[a[u]] == 0) now--;
	}
	else {
		freq[a[u]]++;
		if (freq[a[u]] == 1) now++;
	}
	taken[u] ^= 1;
}
void remove(int id)
{
	int u = node[id];
	if (taken[u]) {
		freq[a[u]]--;
		if (freq[a[u]] == 0) now--;
	}
	else {
		freq[a[u]]++;
		if (freq[a[u]] == 1) now++;
	}
	taken[u] ^= 1;
}

ll get_ans()
{
	return now;
}

int compress() {
	vector <int> v ; map<int, int> Map ;
	for (int i = 1 ; i <= n ; i++) {
		v.push_back(a[i]) ;
	}
	sort (v.begin(), v.end()) ;
	v.erase(unique(v.begin(), v.end()), v.end()) ;
	for (int i = 0 ; i < v.size() ; i++) {
		Map[v[i]] = i + 1 ;
	}
	for (int i = 1 ; i <= n ; i++) {
		a[i] = Map[a[i]] ;
	}
	return (int)v.size() ;
}

void compute()
{
	int L = query[0].l, R = query[0].l - 1, now = 0;

	for (int i = 0; i < q; i++) {
		int ql = query[i].l;
		int qr = query[i].r;

		while (R < qr) include(++R);
		while (L > ql) include(--L);
		while (L < ql) remove(L++);
		while (R > qr) remove(R--);
		int u = node[L], v = node[R];

		if (query[i].lca != u && query[i].lca != v) include(st[query[i].lca]);

		ans[query[i].id] = get_ans();

		if (query[i].lca != u && query[i].lca != v) include(en[query[i].lca]);
	}
}

}
using namespace MO;

int const LOG = 20;
int par[N][LOG] , depth[N] ;
vector <int> g[N] ;

void dfs (int u , int p , int lvl) {
	par[u][0] = p ;
	depth[u] = lvl ;
	st[u] = ++timer ;
	node[timer] = u ;
	for (auto v : g[u]) {
		if (v == p) continue ;
		dfs(v, u, lvl + 1) ;
	}
	en[u] = ++timer ;
	node[timer] = u ;
}


void init(int root , int n) {
	dfs(root, -1, 0) ;
	for (int k = 1 ; k < LOG ; k++) {
		for (int i = 1 ; i <= n ; i++) {
			if (par[i][k - 1] != -1)
				par[i][k] = par[par[i][k - 1]][k - 1] ;
			else
				par[i][k] = -1 ;
		}
	}
}


int lca (int u , int v) {
	if (depth[u] < depth[v]) {
		swap(u, v) ;
	}
	int diff = depth[u] - depth[v] ;
	for (int i = LOG - 1 ; i >= 0 ; i--) {
		if (diff >= (1 << i)) {
			diff -= (1 << i) ;
			u = par[u][i] ;
		}
	}
	if (u == v) return u ;
	for (int i = LOG - 1 ; i >= 0 ; i--) {
		if (par[u][i] != par[v][i]) {
			u = par[u][i] ;
			v = par[v][i] ;
		}
	}
	return par[v][0] ;
}

void solve()
{
	scanf("%d", &n);

	timer = 0;

	scanf("%d", &q);

	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	compress();
	// for (int i = 1; i <= n; i++) printf("%lld ", a[i]);

	for (int i = 0; i < n - 1; i++) {
		int u, v;

		scanf("%d%d", &u, &v);

		g[u].push_back(v);
		g[v].push_back(u);
	}

	init(1, n);

	reset();

	for (int i = 0; i < q; i++) {
		int u, v;

		scanf("%d%d", &u, &v);

		if (st[u] > st[v]) swap(u, v);

		int _lca = lca(u, v);

		if (en[u] >= en[v]) query[i] = Query(st[u], st[v], i, _lca);
		else query[i] = Query(en[u], st[v], i, _lca);
	}

	sort(query, query + q);

	compute();

	for (int i = 0; i < q; i++) printf("%d\n", ans[i]);

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
