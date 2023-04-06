/*
Description
RSJ has a sequence a of n integers a_1, a_2, ..., a_n are an integer s.
For each of a_2, a_3, ..., a_n-1, he chose a pair of non-negative integers 
x_i and y_i such that x_i + y_i = a_i and (x_i - s) * (y_i - s) >= 0.
Now he is interested in the value 
    F = a_1 * x_2 + y_2 * x_3 + y_3 * x_4 + ... + y_n-2 * x_n-1 + y_n-1 * a_n.
Please help him find the minimum possible value F he can get by choosing
x_i and y_i optimally.

Input 
1 <= t <= 1e4 
3 <= n <= 2e5, 0 <= s <= 2e5 
a_1, a_2, ..., a_n (0 <= a_i <= 2e5)

Output 
The minimum possible F.
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long

pair<ll, ll> partition(ll num, ll s) {
    if (num >= 2*s) {
        return make_pair(s, num-s);
    }
    if (num <= s) {
        return make_pair(0, num);
    }
    return make_pair(num-s, s);
}

void solve() {
    ll n, s; cin >> n >> s;
    
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll x0, y0, x1, y1;
    pair<ll, ll> p0, p1; 
    vector<pair<ll, ll>> dp(n);

    dp[0].first = a[0];
    dp[0].second = a[0];

    p1 = partition(a[1], s);
    x1 = p1.first;
    y1 = p1.second;
    dp[1].first = a[0] * x1;
    dp[1].second = a[0] * y1;

    for (int i = 2; i < n-1; i++) {
        p0 = partition(a[i-1], s);
        p1 = partition(a[i], s);
        x0 = p0.first;
        x1 = p1.first;
        y0 = p0.second;
        y1 = p1.second;

        dp[i].first = min(
            dp[i-1].first + y0 * x1, 
            dp[i-1].second + x0 * x1
        );
        dp[i].second = min(
            dp[i-1].first + y0 * y1,
            dp[i-1].second + x0 * y1
        );
    }
    
    p0 = partition(a[n-2], s);
    x0 = p0.first;
    y0 = p0.second;
    ll ans = min(dp[n-2].first + y0 * a[n-1], dp[n-2].second + x0 * a[n-1]);

    cout << ans << "\n";
}

int main() {

    int t; cin >> t; 
    
    while (t--) {
        solve();
    }

    return 0;
}