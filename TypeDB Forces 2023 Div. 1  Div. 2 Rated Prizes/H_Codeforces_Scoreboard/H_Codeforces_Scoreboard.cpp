/*
Description
You are participating in a Codeforces Round with n problems.
You spend exactly one minute to solve each problem, the time it takes to submit 
a problem can be ignored. You can only solve at most one problem at any time.
The contest starts at time 0, so you can make your first submission 
at any time t >= 1 nimutes. Whenever you submit a problem, it is always accepted.
The scoring of the i-th problem can be represented by three integers k_i, b_i, and a_i.
If you solve it at time t minutes, you get max(b_i-k_i*t, a_i) points.
Your task is to choose an order to solve all these n problems to get the maximum possible
score. You can assume the contest is long enough to solve all problems.

Input
1 <= t <= 1e4 
1 <= n <= 2e5 
1 <= k_i, b_i, a_i <= 1e9; a_i < b_i

Output 
The maximum score you can get
*/

//By ko_osaga

#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1000005;
const int MAXT = 2100000;
const lint inf = 4e18;
const int mod = 1e9 + 7;

struct line {
	lint A, B;
	int idx;
	lint eval(lint x) { return A * x + B; }
	// returns the x-intercept of intersection "strictly" larger than T
	lint cross_after(line &x, lint T) {
		if (x.A == A) {
			return inf;
		}
		lint up = x.B - B;
		lint dn = A - x.A;
		if (dn < 0) {
			dn *= -1;
			up *= -1;
		}
		lint incep = (up <= 0 ? -((-up) / dn) : (up + dn - 1) / dn);
		if (incep > T)
			return incep;
		return inf;
	}
};

struct kst { // min kinetic segment tree
	line tree[MAXT];
	lint melt[MAXT], T;
	pi lazy[MAXT];
	int n;
	bool cmp(line &a, line &b) {
		lint l = a.eval(T), r = b.eval(T);
		if (l != r)
			return l > r;
		return a.A > b.A;
	}
	void pull(int p) {
		tree[p] = cmp(tree[2 * p], tree[2 * p + 1]) ? tree[2 * p + 1] : tree[2 * p];
		melt[p] = min({melt[2 * p], melt[2 * p + 1], tree[2 * p].cross_after(tree[2 * p + 1], 0)});
	}
	void init(int s, int e, int p, vector<line> &l) {
		if (s == e) {
			tree[p] = l[s];
			melt[p] = inf;
			lazy[p] = {0, 0};
			return;
		}
		lazy[p] = {0, 0};
		int m = (s + e) / 2;
		init(s, m, 2 * p, l);
		init(m + 1, e, 2 * p + 1, l);
		pull(p);
	}
	void lazydown(int p) {
		for (int i = 2 * p; i < 2 * p + 2; i++) {
			lazy[i][0] += lazy[p][0];
			lazy[i][1] += lazy[p][1];
			tree[i].B += lazy[p][0] * tree[i].A + lazy[p][1];
			melt[i] -= lazy[p][0];
		}
		lazy[p][0] = lazy[p][1] = 0;
	}
	void propagate(int p) {
		if (melt[p] > 0)
			return;
		lazydown(p);
		propagate(2 * p);
		propagate(2 * p + 1);
		pull(p);
	}
	lint query(int s, int e, int ps, int pe, int p = 1) {
		if (e < ps || pe < s)
			return inf;
		if (s <= ps && pe <= e)
			return tree[p].eval(0);
		int pm = (ps + pe) / 2;
		lazydown(p);
		return min(query(s, e, ps, pm, 2 * p), query(s, e, pm + 1, pe, 2 * p + 1));
	}
	void heaten(int s, int e, int ps, int pe, int p, lint v) {
		if (e < ps || pe < s)
			return;
		if (s <= ps && pe <= e) {
			lazy[p][0] += v;
			tree[p].B += v * tree[p].A;
			melt[p] -= v;
			propagate(p);
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		heaten(s, e, ps, pm, 2 * p, v);
		heaten(s, e, pm + 1, pe, 2 * p + 1, v);
		pull(p);
	}
	void add(int s, int e, int ps, int pe, int p, lint v) {
		if (e < ps || pe < s)
			return;
		if (s <= ps && pe <= e) {
			lazy[p][1] += v;
			tree[p].B += v;
			return;
		}
		lazydown(p);
		int pm = (ps + pe) / 2;
		add(s, e, ps, pm, 2 * p, v);
		add(s, e, pm + 1, pe, 2 * p + 1, v);
		pull(p);
	}

	void init(vector<line> &l, lint _T) {
		n = sz(l);
		T = _T;
		init(0, n - 1, 1, l);
	}
} kst;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		lint sum = 0;
		vector<int> k(n), b(n), a(n);
		for (int i = 0; i < n; i++) {
			cin >> k[i] >> b[i] >> a[i];
			b[i] -= a[i];
			sum += a[i];
		}
		vector<line> seg(n);
		for (int i = 0; i < n; i++) {
			seg[i].A = k[i];
			seg[i].B = k[i] - b[i];
		}
		sort(all(seg), [&](const line &a, const line &b) { return pi{a.A, a.B} > pi{b.A, b.B}; });
		for (int i = 0; i < n; i++) {
			seg[i].idx = i;
		}
		kst.init(seg, 0);
		lint ret = sum;
		for (int i = 0; i < n; i++) {
			auto val = kst.tree[1].idx;
			sum -= kst.tree[1].eval(0);
			ret = max(ret, sum);
			kst.heaten(val+1, n - 1, 0, n - 1, 1, 1);
			kst.add(0, val - 1, 0, n - 1, 1, seg[val].A);
			kst.add(val, val, 0, n - 1, 1, lint(1e18));
		}
		cout << ret << "\n";
	}
}