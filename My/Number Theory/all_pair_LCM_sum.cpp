#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long
#define mod 132021913 //998244353

int a[mx];
char ch[mx];
int n, m, ii, k;
ll cnt[mx], dp[mx];


ll inv[mx], invfact[mx], fact[mx];

ll add(ll a, ll b)
{
    a += b;
    if (a >= mod)a -= mod;
    return a;
}
ll sub(ll a, ll b)
{
    a -= b;
    a %= mod;
    if (a < 0)a += mod;
    return a;
}
ll mul(ll a, ll b)
{
    ll re = a;
    re *= b;
    if (re >= mod)re %= mod;
    return re;
}

ll bigmod(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

void Fact()
{
    fact[0] = 1;
    for (int i = 1; i < mx; i++) fact[i] = mul(fact[i - 1], i);

    invfact[mx - 1] = bigmod(fact[mx - 1], mod - 2);

    for (int i = mx - 2; i >= 0; i--) invfact[i] = mul(invfact[i + 1], i + 1);
}

void mod_inverse()
{
    inv[1] = 1;
    for (int i = 2; i < mx; ++i) {
        inv[i] = sub(mod, mul((mod / i), inv[mod % i]));
    }
}

ll nCr(ll n, ll r)
{
    return mul(mul(fact[n], invfact[r]), invfact[n - r]);
}


void solve()
{
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        cnt[a[i]]++;
    }

    ll ans = 0;

    for (int i = mx - 1; i >= 1; i--) {
        ll ex = 0, tot = 0, baad = 0;

        ll sumofsquare = 0, squareofsum = 0;

        for (int j = i; j < mx; j += i) {
            sumofsquare += cnt[j] * j;

            squareofsum += cnt[j] * j * j;

            baad = add(baad, dp[j]);
        }

        sumofsquare = mul(sumofsquare, sumofsquare);

        // dp[i] = sub(nCr(tot, 2), ex);

        // ans = add(ans, mul(i, dp[i]));

        ll all_pair_sum = sub(mul(sub(sumofsquare, squareofsum), inv[2]), baad);

        dp[i] = all_pair_sum;

        ll part_of_lcm_sum = mul(all_pair_sum, inv[i]);

        ans = add(ans, part_of_lcm_sum);
        // cout << i << " " << part_of_lcm_sum << "\n";
    }
    // cout << endl;

    for (int i = 0; i <= mx; i++) {
        cnt[i] = 0;
        dp[i] = 0;
    }

    cout << ans << endl;

    return;
}

int main()
{
    int t = 1;
    Fact();
    mod_inverse();
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        printf("Case %d: ", i);
        solve();
    }
    return 0;
}
