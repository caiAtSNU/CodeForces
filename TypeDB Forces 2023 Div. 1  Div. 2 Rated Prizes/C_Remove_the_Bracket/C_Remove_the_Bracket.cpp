/*
Description
RSJ has a sequence a of n integers a_1, a_2, ..., a_n are an integer s.
For each of a_2, a_3, ..., a_n-1, he chose a pair of non-negative integers 
x_i and y_i such that x_i + y_i = a_i and (x_i - s) * (y_i - s) >= 0.
Now he is interested in the value 
    F = a_1 * x_2 + y_2 * x_3 + y_3 * x_4 + ... + y_n-2 * x_n-1 + y_n-1 * a_n.
Please help him find the minimum possible value F he can get by choosing
x_i and y_i optimally.

Input 
1 <= t <= 1e4 
3 <= n <= 2e5, 0 <= s <= 2e5 
a_1, a_2, ..., a_n (0 <= a_i <= 2e5)

Output 
The minimum possible F.
*/

