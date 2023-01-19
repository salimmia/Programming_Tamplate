
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

/*
ll mul(ll a, ll b) {
	long long res = 0LL;
	a = a % mod;
	while (b > 0) {
		if (b & 1) res = add(res, a);
		a = add(a, a);
		b >>= 1;
	}
	return res;
}*/

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
