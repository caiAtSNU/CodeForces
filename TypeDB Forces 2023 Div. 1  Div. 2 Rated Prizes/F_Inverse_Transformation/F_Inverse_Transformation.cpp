/*
Description 
a permutation scientist is studying a self-transforming permutation a consisting of 
n elements a_1, a_2, ..., a_n.
A permutation is a sequence of integers from 1 to n of length n contatining
each number exactly once.
The permutation transforms day by day. On each day, each element x becomes a_x,
that is a_x becomes a_a_x. Specifically:
    on the first day, the permutation becomes b, where b_x = a_a_x;
    on the second day, the permutation becomes c, where c_x = b_b_x;
    ...
Define sigma(x) = a_x, and define f(x) as the minimal positive integer m 
such that sigma^m(x) = x.
Find the initial permutation a such that Sum(1/f(i)) is minimum possible.

Input 
1 <= t <= 1e4 
n, k (1 <= n <= 2e5; 1 <= k <= 1e9) 
a'_1, a'_2, ..., a'_n (1 <= a_i <= n): the permutation on the k-th day

Output
"YES"
a_1, a_2, ..., a_n: the initial permutation 
or
"NO"
*/

#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;
using ll = long long;

const int _ = 200005;
int a[_], ans[_];
bool vis[_];
vector<vector<int>> cycs[_];

int mpow(int x, int a, int mod) {
    if (a == 0) return 1;
    int ret = mpow(x * (ull)x % mod, a >> 1, mod);
    if (a & 1) ret = ret * (ull)x % mod;
    return ret;
}

vector<int> rotate(vector<int> cyc, int rot) {
    vector<int> ret; int i = 0;
    for (int rep = 0; rep != cyc.size(); ++rep) {
        ret.push_back(cyc[i]);
        i = (i + rot) % cyc.size();
    } 
    return ret;
}

vector<int> together(vector<vector<int>> cycs) {
    int n = cycs.size(), m = cycs[0].size();
    vector<int> ret;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            ret.push_back(cycs[j][i]);
        }
    }
    return ret;
}

void set_cyc(vector<int> cyc) {
    for (int i = 0; i != cyc.size(); ++i) {
        ans[cyc[i]] = cyc[(i+1) % cyc.size()];
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int n, k; cin >> n >> k;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) cycs[i].clear();
        fill(vis + 1, vis + n + 1, false);
        for (int i = 1; i <= n; ++i) {
            if (vis[i]) continue; 
            int x = i;
            vector<int> vec;
            while (!vis[x]) {
                vis[x] = true;
                vec.push_back(x);
                x = a[x];
            }
            cycs[vec.size()].push_back(vec);
        }
        bool flag = true;
        for (int len = 2; len <= n; len += 2) {
            if (cycs[len].size() > 0) {
                if (k >= 25) { flag = false; break; }
                if (cycs[len].size() % (1 << k)) { flag = false; break; }
                for (int j = 0; j != cycs[len].size(); j += 1 << k) {
                    vector<int> cyc;
                    for (int l = 0; l < len; ++l) {
                        for (int f = j; f != j + (1 << k); ++f) {
                            cyc.push_back(cycs[len][f][l]);
                        }
                        set_cyc(cyc);
                    }
                }
            }
        }
        if (!flag) {
            cout << "NO\n"; continue;
        }
        cout << "YES\n";
        int good = min(k, 25);
        for (int len = 1; len <= n; len += 2) {
            for (int l = good; l >= 0; --l) {
                while (cycs[len].size() >= (1 << l)) {
                    int rot = mpow((len + 1) / 2, k - l, len);
                    vector<vector<int>> vv;
                    for (int rep = 0; rep != 1 << l; ++rep) {
                        vv.push_back(rotate(cycs[len].back(), rot));
                        cycs[len].pop_back();
                    }
                    set_cyc(together(vv));
                }
            }
        }
        for (int i = 1; i <= n; ++i) cout << ans[i] << " \n"[i == n];
    }

    return 0;
}