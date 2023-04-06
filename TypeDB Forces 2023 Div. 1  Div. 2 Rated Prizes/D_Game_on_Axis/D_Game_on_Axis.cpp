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

void solve() {
    int n; cin >> n;
    
    vector<int> a(n+1);
    vector<vector<int>> adj_list(n+1);
    vector<int> stack;
    int x, y;
    for (int i = 1; i < n+1; i++) {
        cin >> a[i];
        x = i;
        y = i + a[i];
        if (1 <= y && y <= n) {
            adj_list[y].push_back(x);
        }
        else {
            stack.push_back(i);
        }
    }

    int S = 0;
    vector<int> endgame(n+1);
    while (stack.size() != 0) {
        x = stack.back();
        stack.pop_back();
        if (endgame[x] == 0) endgame[x] = 1;
        S += 1;
        for (int y : adj_list[x]) {
            if (endgame[y] != 0) {
                endgame[y] = endgame[x] + 1;
                stack.push_back(y);
            }
        }
    }

    int ans = 0;
    vector<int> visited(n+1);
    int cur = 1;
    while (1 <= cur && cur <= n) {
        if (visited[cur] == 1) break;

        visited[cur] = 1;

        ans += n+2;
        if (endgame[cur] == 1) {
            ans += S-1;
        } else {
            ans += S;
        }

        cur = cur + a[cur];
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