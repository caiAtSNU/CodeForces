/*
Description
You are given a rooted tree consisting of n vertices numbered from 1 to n.
Vertex 1 is the root of the tree. Each vertex has an integer value.
The value of i-th vertex is a_i. You can do the following operation at most k times.
    Choose a vertex v that has not been chosen before and an integer x such that
    x is a common divisor of the values of all vertices of the subtree of v.
    Multiply by x the value of each vertex in the subtree v.
What is the maximum possible value of the root node 1 after at most k operations?
Formally, you have to maximize the value of a_1.

Input
1 <= t <= 50000
2 <= n <= 1e5, 0 <= k <= n
a_1, a_2, ..., a_n (1 <= a_i <= 1000)
u_i, v_i (n-1 edges)

Output
The maximum value of the root after performing at most k operations
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 100005;
const int mod = 998244353;

int val[N];
vector<int> g[N];
vector<int> divisor[N];
int subtree_gcd[N], par[N];

int dp[N][1003];
int gcdd[1003][1003];

inline long long
___gcd(long long a, long long b)
{
    if (gcdd[a][b])
        return gcdd[a][b];

    return gcdd[a][b] = __gcd(a, b);
}

inline long long lcm(long long a, long long b)
{
    return (a / ___gcd(a, b)) * b;
}

void dfs(int u, int p)
{
    par[u] = p;
    subtree_gcd[u] = val[u];
    for (int v : g[u])
    {
        if (v == p)
            continue;
        dfs(v, u);
        subtree_gcd[u] = ___gcd(subtree_gcd[u], subtree_gcd[v]);
    }
}

int solve(int u, int d, int p)
{
    if (subtree_gcd[u] % d == 0)
        return 0;
    if ((val[u] * val[u]) % d)
        return (1 << 30);

    if (dp[u][d] != -1)
        return dp[u][d];

    long long req = d / ___gcd(d, subtree_gcd[u]);

    long long res = (1 << 30);
    for (int div : divisor[val[u]])
    {
        if ((val[u] * div) % d == 0 && d % div == 0)
        {
            long long r = 1;
            for (int v : g[u])
            {
                if (v == p)
                    continue;
                r += solve(v, lcm(d / div, div), u);
            }
            res = min(res, r);
        }
    }

    return dp[u][d] = min(res, (1LL << 30));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 2; i < 1001; i++)
    {
        for (int j = i; j < 1001; j += i)
        {
            divisor[j].push_back(i);
        }
    }

    int t;
    cin >> t;

    while (t--)
    {
        int n, k;
        cin >> n >> k;

        for (int i = 0; i <= n; i++)
        {
            g[i].clear();
        }

        for (int i = 1; i <= n; i++)
        {
            cin >> val[i];
        }

        for (int i = 0; i <= n; i++)
        {
            for (int d : divisor[val[1]])
            {
                dp[i][d] = -1;
            }
        }

        for (int i = 0; i < n - 1; i++)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        dfs(1, 0);

        int ans = val[1];

        for (int d : divisor[val[1]])
        {
            int req = 0;
            int f = 1;
            for (int v : g[1])
            {
                int x = solve(v, d, par[v]);
                if (x > n)
                    f = 0;
                req += x;
            }

            if (!f)
                continue;

            req++;
            if (req <= k)
            {
                ans = max(ans, val[1] * d);
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
