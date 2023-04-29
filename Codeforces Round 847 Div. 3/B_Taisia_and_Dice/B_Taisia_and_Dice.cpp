/*
Description 
Taisia has n six-sided dice. Each face of the die is marked with a number 
from 1 to 6, each number from 1 to 6 is used once. 
Taisia rolls all n dice at the same time and gets a sequence of values 
a_1, a_2, ..., a_n (1 <= a_i <= 6), where a_i is the value on the upper face 
of the i-th dice. The sum of this sequence is equal to s.
Suddenly, Taisia's pet cat steals exactly one dice with maximum value a_i and
calculates the sum of the values on the remaining n-1 dice, which is equal to r.
You only know the number of dice n and the values of s, r. Restore a
possible sequence a that fulfills the constraints.

Input
1 <= t <= 1000
n, s, r (2 <= n <= 50, 1 <= r < s <= 300) 

Output
a_1, a_2, ..., a_n
*/

#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, s, r; cin >> n >> s >> r;
    int mx = s-r;
    int m = s - mx;

    vector<int> cnt(7);
    int cur = 1;
    while (m > 0) {
        int need = min(m, n-1);
        m -= need;
        cnt[cur-1] -= need;
        cnt[cur] += need;
        cur += 1;
    }

    cout << mx << " ";
    for (int i = 1; i <= mx; i++) {
        for (int j = 0; j < cnt[i]; j++) {
            cout << i << " ";
        }
    }
    cout << "\n";
}

int main() {
    int t; cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}