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

int a[N], block[N], last[N];
struct algo
{
	int move, last;
} ans[N];

void build(int len, int n)
{
	for (int i = n - 1; i >= 0; i--) {
		int c_l, r_l;
		c_l = i / len;
		r_l = (i + a[i]) / len;
		if (i + a[i] >= n) {
			ans[i].move = 1;
			ans[i].last = n;
			last[i] = i;
		}
		else if (c_l != r_l) {
			ans[i].move = 1;
			ans[i].last = (i + a[i]);
			last[i] = i;
		}
		else {
			int pos = i + a[i];
			ans[i].move = 1 + ans[pos].move;
			ans[i].last = ans[pos].last;
			last[i] = last[i + a[i]];
		}
	}
}

void update(int n, int b, int len, int id)
{
	int l = max((b - 1) * len - 1 + len, 0);
	int r = id;
	for (int i = r; i >= l; i--) {
		int c_l, r_l;
		c_l = i / len;
		r_l = (i + a[i]) / len;
		if (i + a[i] >= n) {
			ans[i].move = 1;
			ans[i].last = n;
			last[i] = i;
		}
		else if (c_l != r_l) {
			ans[i].move = 1;
			ans[i].last = (i + a[i]);
			last[i] = i;
		}
		else {
			int pos = i + a[i];
			ans[i].move = 1 + ans[pos].move;
			ans[i].last = ans[pos].last;
			last[i] = last[i + a[i]];
		}
	}
}

void Query(int &pos, int n)
{
	int cnt = 0, lst = pos;
	for (int i = pos; i < n; i = ans[i].last) {
		cnt += (ans[i].move);
		lst = last[i];
	}
	printf("%d %d\n", lst + 1, cnt);
}

void solve()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)scanf("%d", &a[i]);

	int len = sqrt(n);

	// if (len * len != n) len++;
	build(len, n);

	while (m--) {
		int type, idxl, idxr;
		scanf("%d%d", &type, &idxl);
		idxl--;
		if (type == 0) {
			scanf("%d", &idxr);
			a[idxl] = idxr;

			update(n, idxl / len, len, idxl);
		}

		else {
			Query(idxl, n);
		}
	}
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
