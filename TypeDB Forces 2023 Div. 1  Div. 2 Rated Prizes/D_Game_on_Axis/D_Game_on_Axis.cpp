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
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}