void compress() {
    vector<ll> v;

    for (int i = 1; i <= n; i++)v.push_back(a[i]);

    sort(v.begin(), v.end());

    v.resize(unique(v.begin(), v.end()) - v.begin());

    for (int i = 1; i <= n; i++) {
        ll x = a[i];
        x = lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
        a[i] = x;
    }
}
