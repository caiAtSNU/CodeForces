/*
Description 
Polycarp worte out all the digits that he managed to remember.
For example, if Polycarp remembered Pi as 3.1415, he wrote out 31415.
Polycarp was in hurry and could have made mistake, so you decided to 
check how many first digits of the number Pi Polycarp actually remembered
correctly.

Input 
1 <= t <= 1e3 
n <= 30 digits

Output
How many first digits of the number Pi Polycarp remembers correctly.
*/

#include <bits/stdc++.h>

using namespace std; 

string const Pi = "314159265358979323846264338327";

void solve() {
    string n; cin >> n;
    for (int i = 0; i < n.size(); i++) {
        if (n[i] != Pi[i]) {
            cout << i << "\n";
            return;
        }
    }
    cout << n.size() << "\n";
}

int main() {
    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}