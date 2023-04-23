/*
Description
The Mountain Amusement Park has opened a brand-new simulated roller coaster.
The simulated track consisted of n rails attached end-to-end with the beginning of
the first rail fixed at elevation 0. Byteman, the operator, can reconfigure the track
at will by adjusting the elevation change over a number of consecutive rails.
The elevation change over other rails is not affected. Each time rails are adjusted,
the following track is raised or lowered as necessary to connect the track
while maintaining the start at elevation 0.
Each ride is initiated by launching the car with sufficient energy to reach
height h. That is, the car will continue to travel as long as the
elevation of the track does not exceed h, and as long as 
the end of the track is not reached.
Given the record for all the day's rides and track configuration changes,
compute for each ride the number of rails traversed by the car
before it stops.

Input
1 <= n <= 1e9
queries:
    I a b D: the rails from a-th to b-th inclusive after 
    the execution of the request have an elevation equal to D.
    Q h: start the ride. it is required to find the number of rails that 
    the trolley will pass.
    E: end of input.

Output
For each Q print the number of rails that the trolley will pass.
*/

//Runtime error! may be index out of bound???

#include <bits/stdc++.h>
using namespace std;

int INF = 1e9 + 7;

struct node {
    int e;
    int delta;
    int mx;

    node() {
        e = 0;
        delta = 0;
        mx = 0;
    }
};

struct segtree {
    int size;
    vector<node> arr;

    segtree(int n) {
        size = 1;
        while(size < n) size*=2;
        arr.assign(2*size+1, node());
    }

    void push(int v, int pl, int pr, int ti){
        arr[ti].e = v;
        arr[ti].delta = (pr-pl+1)*v;
        arr[ti].mx = arr[ti].delta;
    }

    void configure(int l, int r, int v, int pl, int pr, int ti) {
        if (pr < l || pl > r) return;
        
        int mid = (pl+pr)/2;

        if (arr[ti].e != -INF && pl != pr) {
            push(arr[ti].e, pl, mid, 2*ti+1);
            push(arr[ti].e, mid+1, pr, 2*ti+2);
            arr[ti].e = -INF;
        }

        if (l <= pl && pr <= r) {
            arr[ti].e = v;
            arr[ti].delta = (pr-pl+1)*v;
            arr[ti].mx = arr[ti].delta;
            return;
        }

        configure(l, r, v, pl, mid, 2*ti+1);
        configure(l, r, v, mid+1, pr, 2*ti+2);

        arr[ti].delta = arr[2*ti+1].delta + arr[2*ti+2].delta;
        arr[ti].mx = max(arr[2*ti+1].mx, arr[2*ti+1].delta + arr[2*ti+2].mx);
    }

    int query(int h, int d, int n, int pl, int pr, int ti) {
        if (pl == pr) {
            if (d+arr[ti].mx > h) return pl-1;
            else return pl;
        }

        int mid = (pl+pr)/2;

        if (arr[ti].e != -INF && pl != pr) {
            push(arr[ti].e, pl, mid, 2*ti+1);
            push(arr[ti].e, mid+1, pr, 2*ti+2);
            arr[ti].e = -INF;
        }


        if (d+arr[2*ti+1].mx > h) return query(h, d, n, pl, mid, 2*ti+1);
        return query(h, d+arr[2*ti+1].delta,  n, mid+1, pr, 2*ti+2);
    }
};

int main() {
    int n; cin >> n;

    segtree seg(n);

    char q; int a, b, D; int h;
    while (true) {
        cin >> q;
        if (q == 'E') break;

        if (q == 'I') {
            cin >> a >> b >> D;
            seg.configure(a, b, D, 1, n, 0);
        }

        if (q == 'Q') {
            cin >> h;
            cout << seg.query(h, 0, n, 1, n, 0) << "\n";
        }
    }

    return 0;
}