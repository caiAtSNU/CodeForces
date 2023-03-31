/*
Description
You are given a permutation p of length n, an array of m distinct integers
a_1, a_2, ..., a_m (1 <= a_i <= n), and an integer d.
Let pos(x) be the index of x in the permutation p. The array a is not good if 
    pos(a_i) < pos(a_i+1) <= pos(a_i) + d for all 1 <= i < m.
In one move, you can swap two adjacent elements of the permutation p.
What is the minimum number of moves needed such that the array a becomes good?

Input
1 <= t <= 1e4  
2 <= n <= 1e5, 2 <= m <= n, 1 <= d <= n
p_1, p_2, ..., p_n
a_1, a_2, ..., a_m

Output
The minimum number of moves needed.
*/

#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, m, d; cin >> n >> m >> d;

    vector<int> P(n);
    vector<int> I(n);
    for (int i = 0; i < n; i++) {
        cin >> P[i];
        I[P[i]] = i;
    }

    vector<int> A(m);
    for (int i = 0; i < m; i++) {
        cin >> A[i];
    }

    int mn;
    mn = (1 << 30);
    int x, y;
    for (int i = 0; i < m-1; i++) {
        x = I[A[i]];
        y = I[A[i+1]];
        
        if ((y - x < 0) || (y - x > d)) {
            cout << 0 << "\n";
            return;
        }

        int val;
        val = y-x;
        if (d < n-1) val = min({val, x+d+1-y});
        
        mn = min({mn, val});
    }

    cout << mn << "\n";
}

int main() {
    
    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}