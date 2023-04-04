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

