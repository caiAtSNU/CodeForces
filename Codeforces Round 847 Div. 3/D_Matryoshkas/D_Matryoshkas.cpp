/*
Description
Mashtryohka is a wooden toy in the form of a painted out doll, 
inside which you can put a simillar doll of a smaller size.
A set of nesting dolls contains one or more nesting dolls, 
their sizes are consecutive positive integers.
You had one or more sets of nesting dolls. Recently, you found that someone
mixed all your sets in one and recorded a sequence of doll sizes
You do not remember how many sets you had, so you want to find the minimum
number of sets that you could initially have.
According to a given sequence of sizes of nesting dolls a_1, a_2, ..., a_n,
detemine the minimum number of nesting dolls that can make this sequence.

Input
1 <= t <= 1e4
1 <= n <= 2e5
a_1, a_2, ..., a_n (1 <= a_i <= 1e9)

Output 
The minimum possible number of matryoshkas sets
*/

#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n; cin >> n;
    int a;
    map<int, int> M;
    for (int i = 0; i < n; i++) {
        cin >> a;
        if (M.find(a) == M.end()) {
            M.insert({a, 1});
        }
        else {
            M[a] += 1;
        }
    }
    M[1000000000+7] = 0;

    int sol = 0;
    int prev = M.begin()->first-1;
    int val = 0;
    for (auto iter = M.begin(); iter != M.end(); iter++) {
        if (iter->first != prev+1) {
            sol += val;
        }
        else {
            sol += max(0, val - (iter->second));
        }
        prev = iter->first;
        val = M[prev];
    }

    cout << sol << "\n";
}

int main() {
    int t; cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}