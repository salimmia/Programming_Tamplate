vector<int> prefix_function (string s) {
    int n = (int) s.length(); vector<int> pi (n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j])  ++j;
        pi[i] = j;
    }
//     for (int i = 0; i < n; i++) {
//         for (char c = 'a'; c <= 'z'; c++) {
//             if (c == s[i])dp[i][c - 'a'] = i + 1;
//             else if (i > 0)dp[i][c - 'a'] = dp[pi[i - 1]][c - 'a'];

//             cout << dp[i][c - 'a'] << " ";
//         }
//         cout << endl;
//     }
    return pi;
}
