/*
Description
Recently, a tree has fallen on Bob's head from the sky.
The tree has n nodes. Each node u of the tree has an integer number a_u
written on it. But the tree has no fixed root, as it has fallen from the sky.
Bob is currently studying the tree. To add some twist, Alice proposes a game.
First, Bob chooses some node r to be the root of the tree.
After that, Alice chooses a  node v and tells him.
Bob then can pick one or more nodes from the subtree of v.
His score will be the bitwise XOR of all the values written on the nodes picked
by him. Bob has to find the maximum score he can achieve for the given r and v.
As Bob is not a good problem-solver, he asks you to help him find the answer.
Can you help him? You need to find the answers for several combinations of r and v
for the same tree.

Input
1 <= t <= 1e5
2 <= n <= 2e5
a_1, a_2, ..., a_n (1 <= a_i <= 1e9)
u, v (n-1 edges)
1 <= q <= 2e5
1 <= r, v <= n

Output
The maximum score Bob can achieve
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define nn '\n'
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(NULL);

const int sz = 2e5 + 10, d = 30;
vector<int> g[sz], Tree[sz];
int a[sz], discover_time[sz], finish_time[sz], nodeOf[sz], tim;

struct BASIS {
    int basis[d];
    int sz;
 
    void init() {
        for(int i = 0; i < d; i++) basis[i] = 0;
        sz = 0;
    }
 
    void insertVector(int mask) {
        for (int i = d-1; i >= 0; i--) {
            if (((mask>>i)&1) == 0) continue;
 
            if (!basis[i]) {
                basis[i] = mask;
                ++sz;
                return;
            }
            mask ^= basis[i];
        }
    }
 
    void mergeBasis(const BASIS &from) {
        for(int i = d-1; i >= 0; i--) {
            if(!from.basis[i])
                continue;
 
            insertVector(from.basis[i]);
        }
    }
 
    int findMax()  {
        int ret = 0;
        for(int i = d-1; i >= 0; i--) {
            if(!basis[i] || (ret>>i & 1))
                continue;
 
            ret ^= basis[i];
        }
        return ret;
    }
} in[sz], out, pre[sz], suf[sz];
 
void in_dfs(int u, int p)
{
    in[u].insertVector(a[u]);
    discover_time[u] = ++tim;
    nodeOf[tim] = u;
 
    for(auto &v : g[u]) {
        if(v == p)
            continue;
 
        Tree[u].pb(v);
        in_dfs(v, u);
 
        in[u].mergeBasis(in[v]);
    }
    finish_time[u] = tim;
}
 
inline bool in_subtree(int sub_root, int v)
{
    return discover_time[sub_root] <= discover_time[v]
            && finish_time[sub_root] >= finish_time[v];
}
 
int findChildOnPath(int sub_root, int v)
{
    int lo = 0, hi = (int)Tree[sub_root].size()-1;
 
    while(lo <= hi) {
        int mid = lo+hi>>1, node = Tree[sub_root][mid];
 
        if(finish_time[node] < discover_time[v]) {
            lo = mid + 1;
        }
        else if(discover_time[node] > discover_time[v]) {
            hi= mid - 1;
        }
        else {
            return node;
        }
    }

    return 0;
}
 
void init(int n) {
 
    for(int i = 0; i <= n+5; i++) {
        g[i].clear(), Tree[i].clear();
        in[i].init();
        pre[i].init(), suf[i].init();
    }
    tim = 0;
}
 
int main()
{
    fastio;
 
    int t;
    cin >> t;
 
    while(t--) {
        int n; cin >> n;
 
        init(n);
 
        for(int i = 1; i <= n; i++) cin >> a[i];
 
        for(int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            g[u].pb(v); g[v].pb(u);
        }
 
        in_dfs(1, -1);
 
        for(int i = 1; i <= n; i++) {
            pre[i].insertVector(a[ nodeOf[i] ]);
            pre[i].mergeBasis(pre[i-1]);
        }
 
        for(int i = n; i >= 1; i--) {
            suf[i].insertVector(a[ nodeOf[i] ]);
            suf[i].mergeBasis(suf[i+1]);
        }
 
        int q; cin >> q;
 
        while(q--) {
            int root, v;
            cin >> root >> v;
 
            if(root == v) {
                cout << in[1].findMax() << nn;
            }
            else if(in_subtree(v, root)) {
                int child = findChildOnPath(v, root);
 
                out.init();
                out.mergeBasis(pre[discover_time[child]-1]);
                out.mergeBasis(suf[finish_time[child]+1]);
                cout << out.findMax() << nn;
            }
            else
                cout << in[v].findMax() << nn;
        }
    }
 
    return 0;
}