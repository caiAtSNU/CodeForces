/*
Description
An edge-weighted tree of n nodes is given with each edge colored in some color.
Each node of this tree can be blocked or unblocked, all nodes are unblocked
initially.
A simple path is a path in a graph that does not have repeating nodes.
The length of a path is defined as the sum of weights of all edges on the path.
A path is good when it is a simple path consisting of edges of the same color c,
all the edges of color c are on this path,
and every node on the path is unblocked.
You need to operate 2 kinds of queries:
    1. block a node,
    2. unblock a node.
After each query, print the maximum length among all good paths.
If there are no good paths, print 0.

Input
n, q (1 <= n, q <= 2e5)
n-1 edges with a form 1 <= u, v, w, c <= n
q lines of queries with p, x
if p == 0, block x;
if p == 1, unblock x.

Output
The maximum length of a good path.
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, m, head[200100], cnt;

struct node
{
    int to, next, col;
} edge[400100];

void ae(int u, int v, int c)
{
    edge[cnt].next = head[u], edge[cnt].to = v, edge[cnt].col = c, head[u] = cnt++;
    edge[cnt].next = head[v], edge[cnt].to = u, edge[cnt].col = c, head[v] = cnt++;
}

map<int, int> mp[200100];
int enm[200100], eds[200100];

bool chn[200100];

int lca[200100];
ll len[200100];

int fid[200100];

multiset<ll> s[200100], t;

bool des[200100];

void dfs_init(int x, int fa)
{
    for (int i = head[x], y; i != -1; i = edge[i].next)
    {
        if ((y = edge[i].to) != fa)
        {
            dfs_init(y, x), fid[y] = i;
            if (!chn[edge[i].col])
                continue;
            lca[edge[i].col] = x;
        }
    }
}

void destroy(int x)
{
    des[x] = true;
    if (!s[x].empty())
        t.erase(t.find(*s[x].rbegin()));
    if (x == 1 || !chn[edge[fid[x]].col])
        return;
    int c = edge[fid[x]].col;
    if (!eds[c]++)
    {
        if (!des[lca[c]] && !s[lca[c]].empty())
            t.erase(t.find(*s[lca[c]].rbegin()));
        s[lca[c]].erase(s[lca[c]].find(len[c]));
        if (!des[lca[c]] && !s[lca[c]].empty())
            t.insert(*s[lca[c]].rbegin());
    }
}

void repair(int x)
{
    des[x] = false;
    if (!s[x].empty())
        t.insert(*s[x].rbegin());
    if (x == 1 || !chn[edge[fid[x]].col])
        return;
    int c = edge[fid[x]].col;
    if (!--eds[c])
    {
        if (!des[lca[c]] && !s[lca[c]].empty())
            t.erase(t.find(*s[lca[c]].rbegin()));
        s[lca[c]].insert(len[c]);
        if (!des[lca[c]] && !s[lca[c]].empty())
            t.insert(*s[lca[c]].rbegin());
    }
}

int main()
{
    int n, q;
    cin >> n >> q;
    memset(head, -1, sizeof(head));
    for (int i = 1, x, y, w, c; i < n; i++)
    {
        cin >> x >> y >> w >> c;
        ae(x, y, c), mp[c][x]++, mp[c][y]++, enm[c]++, len[c] += w;
    }
    for (int i = 1; i <= n; i++)
    {
        if (mp[i].size() != enm[i] + 1)
            continue;
        chn[i] = true;
        for (auto x : mp[i])
            if (x.second > 2)
            {
                chn[i] = false;
                break;
            }
    }
    dfs_init(1, 0);
    for (int i = 1; i <= n; i++)
        if (chn[i])
            s[lca[i]].insert(len[i]);
    for (int i = 1; i <= n; i++)
        if (!s[i].empty())
            t.insert(*s[i].rbegin());
    for (int i = 1, p, x; i <= q; i++)
    {
        cin >> p >> x;
        if (!p)
            destroy(x);
        else
            repair(x);
        cout << (t.empty() ? 0 : *t.rbegin()) << "\n";
    }
    return 0;
}