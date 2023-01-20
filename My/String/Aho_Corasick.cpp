// Created by Salim_JnU

/// Tested: https://codeforces.com/contest/963/problem/D

#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long
#define mod 1000000007

int ar[mx];
int n, m, ii, k;

struct Aho_Corasick
{
    int Trie[mx][27], Suffix_Link[mx];
    vector<int> Mark[mx];

    int Node;

    void Init()
    {
        fill(Trie[0], Trie[0] + 26, -1);
        Mark[0].clear();
        Node = 0;
    }

    void Insert(char ch[], int idx)
    {
        int len = strlen(ch);

        int cur = 0;

        for (int i = 0; i < len; i++)
        {
            int val = ch[i] - 'a';
            if (Trie[cur][val] == -1)
            {
                Trie[cur][val] = ++Node;
                fill(Trie[Node], Trie[Node] + 26, -1);
                Mark[Node].clear();
            }
            cur = Trie[cur][val];

        }

        Mark[cur].push_back(idx);

    }

    void Cal_Suffix_Link()
    {
        queue<int>q;
        Suffix_Link[0] = 0;
        for (int i = 0; i < 26; i++)
        {
            if (Trie[0][i] != -1)
            {
                q.push(Trie[0][i]);
                Suffix_Link[Trie[0][i]] = 0;

            }
            else Trie[0][i] = 0;
        }

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int v : Mark[Suffix_Link[u]])
            {
                Mark[u].push_back(v);
            }

            for (int i = 0; i < 26; i++)
            {
                if (Trie[u][i] != -1)
                {
                    Suffix_Link[Trie[u][i]] = Trie[Suffix_Link[u]][i];
                    q.push(Trie[u][i]);
                }
                else
                    Trie[u][i] = Trie[Suffix_Link[u]][i];
            }
        }
    }

} Automata;


int cnt[mx];
vector<int>pos[mx * 26 + 5];

void Count_Pattern(char ch[])
{
    int cur = 0;
    int len = strlen(ch);
    for (int i = 0; i < len; i++)
    {
        int val = ch[i] - 'a';
        cur = Automata.Trie[cur][val];
        for (int id : Automata.Mark[cur]) pos[id].push_back(i);
    }
}

int a[mx];
char ch1[1000005], ch[mx];

void solve()
{
    scanf("%s", ch1);
    scanf("%d", &n);
    string s[mx];
    Automata.Init();

    for (int i = 0; i < n; i++)
    {
        scanf("%d%s", &a[i], ch);
        s[i] = ch;

        Automata.Insert(ch, i);
    }
    Automata.Cal_Suffix_Link();

    /// print Occurence Frequency
    for (int i = 0; i < n; i++)
    {
        // printf("%d\n", cnt[i]);
        cnt[i] = 0;
    }

    Count_Pattern(ch1);

    // for (int i = 1; i <= Automata.Node; i++) {
    //     cout << i << " " << Automata.Suffix_Link[i] << endl;
    // }

    // for (int i = 1; i <= Automata.Node; i++) {
    //     cout << i << "---> ";
    //     for (auto x : Automata.Mark[i]) {
    //         cout << x << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 0; i < n; i++) {
        if (pos[i].size() < a[i]) {
            printf("-1\n");
        }
        else {
            int ret = 1e9;
            sort(pos[i].begin(), pos[i].end());
            for (int j = 0; j + a[i] - 1 < pos[i].size(); j++) {
                ret = min(ret, pos[i][j + a[i] - 1] - pos[i][j]);
            }
            int ans = ret + s[i].size();

            printf("%d\n", ans);
        }
    }

}

int main()
{
    int t = 1;
    // scanf("%d", &t);
    while (t--)solve();
    return 0;
}
