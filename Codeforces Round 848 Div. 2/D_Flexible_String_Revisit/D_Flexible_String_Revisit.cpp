/*
Description
You are given two binary strings a and b of length n.
In each move, the string a is modified in the following way:
    An index 1 <= i <= n is chosen uniformly at random.
    The character a_i will be flipped.
What is the expected number of moves required to make
both strings equal for the first time?

Input
1 <= t <= 1e5
1 <= n <= 1e6
a
b

Output
The expected number modulo 998 244 353
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define mod 998244353
#define N 1000005

template <int MOD>
struct ModInt
{
    unsigned x;
    ModInt() : x(0) {}
    ModInt(signed long long sig) : x(sig % MOD) {}
    int get() const { return (int)x; }
    ModInt pow(ll p)
    {
        ModInt res = 1, a = *this;
        while (p)
        {
            if (p & 1)
                res *= a;
            a *= a;
            p >>= 1;
        }
        return res;
    }
    ModInt &operator+=(ModInt that)
    {
        if ((x += that.x) >= MOD)
            x -= MOD;
        return *this;
    }
    ModInt &operator-=(ModInt that)
    {
        if ((x += MOD - that.x) >= MOD)
            x -= MOD;
        return *this;
    }
    ModInt &operator*=(ModInt that)
    {
        x = (unsigned long long)x * that.x % MOD;
        return *this;
    }
    ModInt &operator/=(ModInt that)
    {
        return (*this) *= that.pow(MOD - 2);
    }

    ModInt operator+(ModInt that) const
    {
        return ModInt(*this) += that;
    }
    ModInt operator-(ModInt that) const
    {
        return ModInt(*this) -= that;
    }
    ModInt operator*(ModInt that) const
    {
        return ModInt(*this) *= that;
    }
    ModInt operator/(ModInt that) const
    {
        return ModInt(*this) /= that;
    }
    bool operator<(ModInt that) const
    {
        return x < that.x;
    }
    friend ostream &operator<<(ostream &os, ModInt a)
    {
        os << a.x;
        return os;
    }
};
typedef ModInt<998244353> mint;

void solve() {
    int n; cin >> n;
    string a, b; cin >> a >> b;
    
    int k = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) k++;
    }

    vector<mint> dp(n+1);
    dp[n] = mint(1);
    for (int i = n-1; i > 0; i--) {
        dp[i] = mint(n) / mint(i) + mint(n-i) / mint(i) * dp[i+1];
    }

    mint val = mint(0);
    for (int i = 1; i <= k; i++) {
        val += dp[i];
    }

    cout << val << "\n";
}

int main() {
       
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}