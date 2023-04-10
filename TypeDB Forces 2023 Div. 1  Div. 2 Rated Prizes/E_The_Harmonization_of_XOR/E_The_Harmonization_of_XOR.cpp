/*
Description 
You ar given an array of exactly n numbers [1, 2, 3, ..., n] along with k and x.
Partition the array in exactly k non-empty disjoint subsequences such that
the bitwise XOR of all numbers in each subsequence is x, and 
each number is in exactly one subsequence.

Input
1 <= t <= 1e4 
n, k, x (1 <= k <= n <= 2e5; 1 <= x <= 1e9)

Output 
"YES"
len(s_i) a_i ...
or
"NO"
*/

#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, k, x; cin >> n >> k >> x;

    int acc = 0;
    for (int i = 1; i <= n; i++) {
        acc ^= i;
    }

    // cout << "acc: " << acc << "\n";

    if (k%2 == 0 && acc != 0) {
        cout << "NO" << "\n";
        return;
    }
    if (k%2 == 1 && acc != x) {
        cout << "NO" << "\n";
        return;
    }

    vector<pair<int, int>> pairs;
    vector<int> visited(n+1);
    int cnt = 0;
    int j;
    for (int i = 1; i <= n; i++) {

        // cout << i << " " << (i^x) << "\n";
        
        if (visited[i] == 1) {
            continue;
        }

        visited[i] = 1;
        j = i ^ x;
        if (0 <= j && j <= n) {
            pairs.push_back(make_pair(i, j));
            visited[j] = 1;
            cnt += 1;
        }
    }

    // cout << "cnt: " << cnt << "\n";

    if (cnt < k) {
        cout << "NO" << "\n";
        return;
    }

    cout << "YES" << "\n";
    pair<int, int> p;
    int v, w;
    int remain = n;
    for (int i = 0; i < k-1; i++) {
        p = pairs[i];
        v = p.first;
        w = p.second;

        visited[v] += 1;
        visited[w] += 1;

        if (v > 0 && w > 0) {
            cout << "2 " << v << " " << w << "\n";
            remain -= 2;
        } else {
            cout << "1 " << v+w << "\n";
            remain -= 1; 
        }
    }
    cout << remain << " ";
    for (int i = 1; i <= n; i++) {
        if (visited[i] != 2) {
            cout << i << " ";
        }
    } 
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}