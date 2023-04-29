/*
Description 
A sequence of n numbers is called permutation if it contains all integers from 1 to n
exactly once.
Kristina had a permutation p of n elements. She wrote it on the whiteboard 
n times in such a way that:
    while writing the permutation at the i-th (1 <= i <= n)
    time she skipped the element p_i
So, she worte in total n sequences of length n-1 each.
You know all n of sequences that have been written on the whiteboard,
but you do not know the order in which thye were written.
They are given in arbitrary order. Reconstruct the original permutation from them.

Input
1 <= t <= 1e4
3 <= n <= 100
n lines and n-1 integers

Output
The permutation
*/

#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n; cin >> n;
    vector<vector<int>> mtx(n);
    
    int elem;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-1; j++) {
            cin >> elem;
            mtx[i].push_back(elem);
        }
    }

    vector<int> p;
    vector<int> col(n);
    vector<int> cnt(n+1);
    while (p.size() < n) {
        for (int i = 0; i < n; i++) {
            if (col[i] < n-1) {
                cnt[mtx[i][col[i]]] += 1;
                if (cnt[mtx[i][col[i]]] > 1) elem = mtx[i][col[i]];
            }
        }
        p.push_back(elem);
        cnt[elem] = 0;
        for (int i = 0; i < n; i++) {
            if (mtx[i][col[i]] == elem) col[i] += 1;
        }
    }

    for (auto x : p) cout << x << " ";
    cout << "\n";
}

int main() {
    int t; cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}