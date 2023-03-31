/*
Description
You are given an array of n intergers a_1, a_2, ..., a_n.
The integers are either 1 or -1.
You have to perform the following operation exactly once on the array a:
    Choose an index i (1 <= i < n) and flip the signs of a_i and a_i+1.
What is the maximum possible value of a_1 + a_2 + ... + a_n 
after applying the above operation?

Input
1 <= t <= 500
2 <= n <= 1e5
a_1, a_2, ..., a_n
*/

#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    int acc(0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        acc += a[i];
    }
    
    int mx;
    mx = -1 * (1 << 30);
    for (int i = 0; i < n-1; i++) {
        int val = acc - 2*a[i] - 2*a[i+1];
        if (val > mx) mx = val;
    }

    cout << mx << "\n";
}

int main() {

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}