/*
Description
There are n points 1, 2, ..., n, each point i has a number a_i on it.
You're playing a game on them. Initially, you are at point 1.
When you are at point i, take following steps:
    If 1 <= i <= n, go to i + a_i,
    Otherwise, the game ends.
Before the game begins, you can choose two integers x and y satisfying 
1 <= x <= n, -n <= y <= n and replace a_x with y (set a_x := y).
Find the number of distinct pairs (x, y) such that the game that you start 
after making the change ends in a finite number of steps.

Input 
1 <= t <= 1e4 
1 <= n <= 2e5 
-n <= a_i <= n

Output
The number of distinct pairs (x, y) with which the game ends
*/

#include <bits/stdc++.h>

using namespace std;

void dfs(int x, vector<int>& v, vector<int>& s, vector<vector<int>>& B) {
    v[x] = s[x] = 1;
    for (auto y : B[x]) {
        if (v[y] == 0) {
            dfs(y, v, s, B);
            s[x] += s[y];
        }
    }
}

void solve() {
    int n; cin >> n;
    vector<int> A(n+1);
    vector<vector<int>> B(n+1);
    for (int i = 1; i <= n; i++) {
        int a; cin >> a;
        if (1 <= i + a && i + a <= n) {
            A[i] = i + a;
            B[i + a].push_back(i);
        } else {
            A[i] = 0;
            B[0].push_back(i);
        }
    }

    vector<int> v(n+1);
    vector<int> s(n+1);
    dfs(0, v, s, B);

    long long ans = 0;
    if (v[1] > 0) {
        int cur = 1;
        while (cur != 0) {
            ans -= n - s[0] + 1 + s[cur];
            cur = A[cur];
        }
        ans += n * (2 * n + 1);
    } else {
        int cur = 1;
        while (v[cur] == 0) {
            ans += n + s[0];
            v[cur] += 1;
            cur = A[cur];
        }
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}