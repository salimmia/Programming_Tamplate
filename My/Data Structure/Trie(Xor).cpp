// Created by: Salim_JnU
//http://lightoj.com/volume_showproblem.php?problem=1269

#include<bits/stdc++.h>
using namespace std;
#define mx 2000005

typedef long long ll;
int a[50005];
int n, ii;

int trie[mx][2];
int End[mx], node;

void init()
{
    for (int i = 0; i < mx; i++) trie[i][0] = trie[i][1] = End[i] = 0;
    node = 1;
}

void Insert(int val)
{
    int cur = 1;
    for (int i = 31; i >= 0; i--)
    {
        int bit = 0;
        if (((1 << i) & val))bit = 1;
        if (trie[cur][bit] == 0)trie[cur][bit] = ++node;
        cur = trie[cur][bit];
    }
    End[cur] = val;
}

int query_min(int val)
{
    int cur = 1;
    for (int i = 31; i >= 0; i--)
    {
        int bit = 0;
        if (((1 << i) & val))bit = 1;
        if (trie[cur][bit]) cur = trie[cur][bit];
        else if (trie[cur][bit ^ 1])cur = trie[cur][bit ^ 1];
    }
    return End[cur] ^ val;
}

int query_max(int val)
{
    int cur = 1;
    for (int i = 31; i >= 0; i--)
    {
        int bit = 0;
        if (((1 << i) & val))bit = 1;
        if (trie[cur][bit ^ 1])cur = trie[cur][bit ^ 1];
        else if (trie[cur][bit])cur = trie[cur][bit];
    }

    return End[cur] ^ val;
}


void solve()
{
    scanf("%d", &n);
    int prefix = 0;

    init();

    int re_min = INT_MAX, re_max = 0;
    Insert(0);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        prefix ^= a[i];
        re_min = min(re_min, query_min(prefix));
        re_max = max(re_max, query_max(prefix));
        Insert(prefix);
    }
    printf("Case %d: %d %d\n", ++ii, re_max, re_min);
}

int main()
{
    int t = 1;
    scanf("%d", &t);
    while (t--)
    {
        solve();
    }

    return 0;
}
