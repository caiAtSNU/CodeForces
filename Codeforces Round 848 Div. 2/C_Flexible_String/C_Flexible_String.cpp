/*
Description
You have a string a and a stirng b. Both of the strings have length n.
There are at most 10 different characters in the string a.
You also have a set Q. Initially, Q is empty.  
You can apply the following operation on the string a any number of times:
    Choose an index 1 <= i <= n and a lowercase English letter c.
    Add a_i to the set Q and then replace a_i with c.
You can apply any number of operations on a, but in the end,
the set Q should contain at most k different characters.
Under this constraint, you have to maximize the number of integer pairs (l, r)
(1 <= l <= r <= n) such that a[l, r] = b[l, r].

Input
1 <= t <= 1e4  
1 <= n <= 1e5, 0 <= k <= 10  
a of length n
b of length n

Output
The maximum number of pairs (l, r).
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back 
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

ll count_matching_pair() {
    ll tot_pair = 0, match_count = 0;

    for (ll i = 0; i < a.size(); i++) {
        if (a[i] == b[i] || mark[ a[i]-'a' ]) match_count++;
        else {
            tot_pair += match_count*(match_count+1)/2;
            match_count = 0;
        }
    }
    tot_pair += match_count*(match_count+1)/2;

    return tot_pair;
}

void solve(ll pos, ll cnt) {
    if (cnt > k) return;

    if (pos == char_list.size()) {
        if (cnt == k) ans = max(anx, count_matching_pair());
        return;
    }

    solve(pos+1, cnt);

    mark[ char_list[pos]-'a' ] = 1;
    solve(pos+1, cnt+1);
    mark[ char_list[pos]-'a' ] = 0;
}

int main() {
    fastio;
    ll t;
    cin >> t;
    
    string a, b;
    string char_list;
    bool mark[26];
    ll ans, k;

    while (t--) {
        ll n; cin >> n >> k;
        cin >> a >> b;

        unordered_set<char> unq;
        for(auto &ch: a) unq.insert(ch);

        char_list.clear();
        for(auto &x: unq) char_list.pb(x);

        k = min(k, (ll)unq.size());
        memset(mark, 0, sizeof mark);
        ans = 0;
        solve(0, 0);

        cout << ans << "\n";
    }

    return 0;
}