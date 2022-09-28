///Created by Salim_JnU

#include<bits/stdc++.h>
using namespace std;

#define mx 1000005
#define ll long long

int n, m, ii, k;
char ch[mx], ch1[mx], tt;
/*
backup prime
307,367
1040160883,1066517951
1e9+7,1e9+9,1072857881,1000004249
*/
struct Hash_dui
{
    ll base, mod;
    int sz;
    vector<int>Rev, Forw, P;
    Hash_dui() {}
    Hash_dui(const char* s, ll b, ll m)
    {
        sz = strlen(s), base = b, mod = m;
        Rev.resize(sz + 2, 0), Forw.resize(sz + 2, 0), P.resize(sz + 2, 1);
        for (int i = 1; i <= sz; i++)P[i] = (base * P[i - 1]) % mod;
        for (int i = 1; i <= sz; i++)Forw[i] = (Forw[i - 1] * base + (s[i - 1] - 'a' + 1)) % mod; /// digit hole s[i-1]-'0'
        for (int i = sz; i >= 1; i--)Rev[i] = (Rev[i + 1] * base + (s[i - 1] - 'a' + 1)) % mod; ///alphabet hole s[i-1]-'a'
    }
    void Single_char_ad(char cc)
    {
        P.push_back((P.back()*base) % mod);
        Forw.push_back((Forw.back()*base + (cc - 'a' + 1)) % mod);
    }
    inline int Range_Hash(int l, int r)
    {
        int re_hash = Forw[r + 1] - ((ll)P[r - l + 1] * Forw[l] % mod);
        if (re_hash < 0)re_hash += mod;
        return re_hash;
    }
    inline int Reverse_Hash(int l, int r)
    {
        int re_hash = Rev[l + 1] - ((ll)P[r - l + 1] * Rev[r + 2] % mod);
        if (re_hash < 0)re_hash += mod;
        return re_hash;
    }
};
struct Hash_Main
{
    Hash_dui h1, h2;
    Hash_Main() {}
    Hash_Main(const char* s)
    {
        h1 = Hash_dui(s, 1949313259, 2091573227);
        h2 = Hash_dui(s, 1997293877, 2117566807);
    }
    void Char_Add(char cc)
    {
        h1.Single_char_ad(cc);
        h2.Single_char_ad(cc);
    }
    inline ll Range_Hash(int l, int r) /// O base index
    {
        return ((ll)h1.Range_Hash(l, r) << 32)^h2.Range_Hash(l, r);
    }
    inline ll Reverse_Hash(int l, int r) /// O base index
    {
        return ((ll)h1.Reverse_Hash(l, r) << 32)^h2.Reverse_Hash(l, r);
    }
};
void solve()
{
    scanf("%d %s", &n, ch);
    string re = ch;
    Hash_Main h_ek(ch);
    int sz = re.size();
    for (int i = 2; i <= n; i++)
    {
        scanf("%s", ch1);
        Hash_Main h_dui(ch1);
        int sz2 = strlen(ch1);

        int jabe = 0;
        for (int j = 1; j <= min(sz, sz2); j++)
        {
            if (h_ek.Range_Hash(sz - j, sz - 1) == h_dui.Range_Hash(0, j - 1))jabe = j;
        }
        for (int j = jabe; j < sz2; j++)h_ek.Char_Add(ch1[j]), sz++, re += ch1[j];
    }
    cout << re << "\n";
}

int main()
{
    int t = 1;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        tt++;
        // printf("Case %d: ", i);
        solve();
    }
    return 0;
}
