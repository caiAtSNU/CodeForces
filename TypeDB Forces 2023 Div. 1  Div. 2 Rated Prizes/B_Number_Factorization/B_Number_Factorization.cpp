/*
Description
Given an integer n.
Consider all pairs of integer arrays a and p of the same length such that 
n = [Product] a_i^p_i (a_i > 1; p_i > 0) and 
a_i is the product of some distinct prime numbers.
Your task is to find the maximum value of [Sum] a_i * p_i.

Input
1 <= t <= 1000 
2 <= n <= 1e9 

Output 
The maximum value of the sum
*/

#include <bits/stdc++.h>

using namespace std; 

void solve() {
    vector<pair<int, int>> pfs;

    int n; cin >> n;
    for (int a = 2; a*a <= n; a++) {
        int p = 0;
        while (n%a == 0) {
            n /= a;
            p += 1;
        }
        if (p > 0) {
            pfs.push_back(make_pair(p, a));
        }
    }
    if (n != 1) {
        pfs.push_back(make_pair(1, n));
    }

    sort(pfs.begin(), pfs.end());
    vector<int> pps(pfs.size());
    pps[pps.size()-1] = pfs[pfs.size()-1].second;

    for (int i = pps.size()-2; i >= 0; i--) {
        pps[i] = pfs[i].second * pps[i+1];
    }

    int ans = 0;
    ans += pfs[0].first * pps[0];
    for (int i = 1; i < pfs.size(); i++) {
        if (pfs[i].first > pfs[i-1].first) {
            ans += (pfs[i].first - pfs[i-1].first) * pps[i];
        }
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
