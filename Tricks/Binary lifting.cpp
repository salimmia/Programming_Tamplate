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

#define mt make_tuple
#define eb emplace_back
#define pb push_back

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<": "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

auto sum() { return 0; }

template<typename T, typename... Args>
auto sum(T a, Args... args) { return a + sum(args...); }

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << endl;
    err(++it, args...);
}

void read () { }
template <typename T, typename... Args>
void read (T& t, Args&... args) {
    cin >> t;
    read(args...);
}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
int const N = 2e5 + 5;

ll n, W, m, k, prefix[N], s, Next[N], ans[N];

void solve()
{
    cin >> n >> k >> s;

    vector<ll>a(n);

    for (int i = 0; i < n; i++) cin >> a[i], prefix[i + 1] = prefix[i] + a[i];
    prefix[n + 1] = prefix[n] + s;

    for (int i = 1; i <= n + 1; i++) {
        int lo = 0, hi = n - i;

        while (lo < hi) {
            int mid = (lo + hi + 1) >> 1;

            if (prefix[i + mid] - prefix[i - 1] <= s) lo = mid;
            else hi = mid - 1;
        }
        // cout << i << " " << i + 1 + lo << endl;
        Next[i] = i + lo + 1;
        ans[i] = i;
    }
    Next[n + 1] = n + 1;

    // for (int i = 1; i <= n; i++) cout << Next[i] << " ";
    // cout << endl;

    for (int j = 0; j <= 20; j++) {
        if ((k >> j) & 1LL) {
            for (int i = 1; i <= n + 1; i++) {
                ans[i] = Next[ans[i]];
                // cout << ans[i] << " ";
            }
            // cout << endl;
        }
        for (int i = 1; i <= n + 1; i++) {
            Next[i] = Next[Next[i]];
        }
    }

    ll Ans = 0;

    for (int i = 1; i <= n; i++) Ans = max(Ans, ans[i] - i);
    cout << Ans << endl;

    return;
}

int main()
{
    int t = 1, cs = 1;

    cin >> t;

    FOR(i, 1, t) {
        // cout << "Case " << i << ": ";
        solve();
    }
}
