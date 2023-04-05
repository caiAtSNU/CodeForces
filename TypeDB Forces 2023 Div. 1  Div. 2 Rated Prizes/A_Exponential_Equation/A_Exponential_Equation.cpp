/*
Description
You are given an integer n.
Find any pair of integers (x, y) (1 <= x,y <= n)
such that x^y * y + y^x * x = n

Input
1 <= t <= 1e4
1 <= n <= 1e9

Output
If possible print x, y
else -1
*/

#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n; cin >> n;

    if (n%2 == 1) {
        cout << -1 << "\n";
    }
    else {
        cout << 1 << " " << n/2 << "\n";
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