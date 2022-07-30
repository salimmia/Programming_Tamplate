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

int a[N], LOG[N], par[N][20];

template <class T>
struct RMQ { /// 0 base index
	vector<vector<T>>rmq;
	T kInf = numeric_limits<T>::max();
	void build(const vector<T>&v) {
		for (int i = 2; i < N; i++)LOG[i] = LOG[i - 1] + !(i & (i - 1));
		int n = v.size(), l = 1, d = 1;
		while (l < n)l *= 2, d++;
		rmq.assign(d, v);
		for (int i = 0; i < d - 1; i++) {
			for (int j = 0; j < n; j++) {
				rmq[i + 1][j] = min(rmq[i][j], rmq[i][min(n - 1, j + (1 << i))]);
			}
		}
	}
	T query(int a, int b) {
		if (b <= a)return kInf;
		int d = LOG[b - a]; //log(b-a)
		// int d = 31 - __builtin_clz(b - a); //log(b-a)
		return min(rmq[d][a], rmq[d][b - (1 << d)]);
	}
};

struct LCA { //0 base
	vector<int>st, en, d;
	vector<vector<int>>g;
	vector<pair<int, int>>linear;
	RMQ<pair<int, int>>rmq;
	int timer = 0;
	LCA() {}
	LCA(int n): st(n, -1), en(n, -1), d(n), g(n), linear(2 * n - 1) {}
	void dfs(int u, int p, int l) {
		linear[timer] = {l, u};
		st[u] = timer++;
		par[u][0] = p;
		d[u] = l;
		for (int v : g[u])
			if (v != p) {
				dfs(v, u, l + 1);
				linear[timer++] = {l, u};
			}
		en[u] = timer;
	}
	void addedge(int u, int v) {
		g[u].push_back(v);
		g[v].push_back(u);
	}
	void build(int root) {
		dfs(root, -1, 0);
		rmq.build(linear);
	}
	int query(int a, int b) {
		a = st[a], b = st[b];
		return rmq.query(min(a, b), max(a, b) + 1).second;
	}
	int dist(int a, int b) {
		return d[a] + d[b] - 2 * d[query(a, b)];
	}
};

void solve()
{
	int n, q;
	cin >> n >> q;

	for (int i = 0; i < n; i++) cin >> a[i];

	LCA Lca(n);

	for (int i = 1; i < n; i++) {
		int u, v;

		cin >> u >> v;
		--u, --v;

		Lca.addedge(u, v);
	}

	Lca.build(0);

	while (q--) {
		int type;
		cin >> type;

		if (type == 1) {
			ll u, x;
			u--;

			cin >> u >> x;
		}
		else {
			int u, v;
			cin >> u >> v;
			u--, v--;
			int lca = Lca.query(u, v);

			cout << lca << endl;
		}
	}

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
