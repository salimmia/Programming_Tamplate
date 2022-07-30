#include<bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define INF 1e18
#define nl "\n"
#define PI 3.141592653589793238462

typedef long long int ll;
typedef unsigned long long ull;
typedef long double lld;
#define ff first
#define ss second
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define ROF(i, a, b) for(int i = a; i >= b; i--)
#define all(x) (x).begin(), (x).end()
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))

int const N = 2e5 + 5;

ll n, W, m, k, a[N];

const int M = 5005, LOG = 20;

ll rmq[N][LOG];
ll lg[N];

void preprocess() {
    for (int i = 1; i <= n; i++) rmq[i][0] = a[i] ;
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            if (i + (1 << j) - 1 <= n) {
                rmq[i][j] = min(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j - 1]) ;
            }
            else break ;
        }
    }
    for (int i = 2; i < N; i++) {
        lg[i] = lg[i / 2] + 1;
    }
}

ll query (int i , int j) {
    int k = lg[j - i + 1];
    ll ans = min(rmq[i][k], rmq[j - (1 << k) + 1][k]);
    return ans;
}

void solve()
{
    cin >> n;

    for (int i = 1; i <= n; i++) cin >> a[i];

    preprocess();

    cin >> k;

    while (k--) {
        int l, r;
        cin >> l >> r;

        ll ans = query(l + 1, r + 1);

        cout << ans << endl;
    }

    return;
}

int main()
{
    int t = 1, cs = 1;

    // cin >> t;

    FOR(i, 1, t) {
        // cout << "Case " << i << ": ";
        solve();
    }
}

