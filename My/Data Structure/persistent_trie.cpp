///Created by Salim_JnU

#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long
#define mod 1000000007 //998244353
const int K = 15;

int a[mx];
char ch[mx];
int n, m, tt, k;

// find maximum value (x^a[j]) in the range (l,r) where l<=j<=r
struct node_t;
typedef node_t * pnode;

struct node_t {
    int time;
    pnode to[2];
    node_t() : time(0) {
        to[0] = to[1] = 0;
    }
    bool go(int l) const {
        if (!this) return false;
        return time >= l;
    }
    pnode clone() {
        pnode cur = new node_t();
        if (this) {
            cur->time = time;
            cur->to[0] = to[0];
            cur->to[1] = to[1];
        }
        return cur;
    }
};

pnode last;
pnode version[mx];

void insert(int a, int time) {
    pnode v = version[time] = last = last->clone();
    for (int i = K - 1; i >= 0; --i) {
        int bit = (a >> i) & 1;
        pnode &child = v->to[bit];
        child = child->clone();
        v = child;
        v->time = time;
    }
}

int query(pnode v, int x, int l) {
    int ans = 0;
    for (int i = K - 1; i >= 0; --i) {
        int bit = (x >> i) & 1;
        if (v->to[bit]->go(l)) { // checking if this bit was inserted before the range
            ans |= 1 << i;
            v = v->to[bit];
        } else {
            v = v->to[bit ^ 1];
        }
    }
    return ans;
}

void solve() {
    int n, q;
    scanf("%d %d", &n, &q);
    last = 0;
    for (int i = 0; i < n; ++i) {
        int a;
        scanf("%d", &a);
        insert(a, i);
    }
    while (q--) {
        int x, l, r;
        scanf("%d %d %d", &x, &l, &r);
        --l, --r;
        printf("%d\n", query(version[r], ~x, l));
        // Trie version[r] contains the trie for [0...r] elements
    }
}

int main()
{
    int t = 1;
    // scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        tt++;
        // printf("Case %d: ", i);
        solve();
    }
    return 0;
}
