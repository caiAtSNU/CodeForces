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