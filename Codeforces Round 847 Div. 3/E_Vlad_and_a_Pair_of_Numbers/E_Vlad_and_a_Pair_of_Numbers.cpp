/*
Description
Vald found two possible numbers a and b (a, b > 0).
He discovered that a (+) b = (a + b) / 2,
where (+) means teh bitwise exclusive OR, and division is perfomred
without rounding..
Since it is easy to remember one number than two, Vald remembered only
a (+) b, let's denote this number as x.
Help him find any suitable a and b or tell him that they do not exist.

Input
1 <= t <= 1e4
x

Output
any of a and b
if not exist, -1
*/

#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int x;
    cin >> x;
    int a = 0, b = 0;

    int d = -1;
    int prev = 1;
    while (x > 0)
    {
        int cur = x & 1;
        if (cur == 1 && prev == 1)
        {
            cout << -1 << "\n";
            return;
        }
        if (cur == 1)
        {
            a |= (1 << d);
            a |= (1 << (d + 1));
            b |= (1 << d);
        }
        prev = cur;
        d += 1;
        x >>= 1;
    }
    cout << a << " " << b << "\n";
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}