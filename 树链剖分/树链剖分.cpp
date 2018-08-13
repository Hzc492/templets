#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i <= _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i >= _##i; --i)
#define mem(f,x) memset(f,x,sizeof(f))
//========================================================================
const int MAX = 100000;
int n, m, rot, MOD;
int cnt;
int son[MAX + 5];
int dep[MAX + 5];
int top[MAX + 5];
int siz[MAX + 5];
int fa[MAX + 5];
int id[MAX + 5];
int tmp[MAX + 5];
int w[MAX + 5]; 
int c[MAX << 2];
int laz[MAX << 2];
int l, r, z;
struct u {
	u(int a, u *b) :e(a), nxt(b) {};
	int e;
	u *nxt;
};
u *head[MAX + 5];
void dfs1(int u, int deep) {
	dep[u] = deep;
	int maxson = -1;
	son[u] = -1;
	for (auto p = head[u]; p; p = p->nxt) if (p->e != fa[u]) {
		fa[p->e] = u;
		dfs1(p->e, deep + 1);
		siz[u] += siz[p->e];
		if (siz[p->e] > maxson) {
			son[u] = p->e;
			maxson = siz[p->e];
		}
	}
	siz[u]++;
}
void dfs2(int u, int topf) {
	id[u] = ++cnt;
	top[u] = topf;
	w[cnt] = tmp[u];
	if (son[u] == -1) return;
	dfs2(son[u], topf);
	for (auto p = head[u]; p; p = p->nxt) if (p->e != fa[u] && p->e != son[u]) {
		dfs2(p->e, p->e);
	}
}
void build(int cur, int ll, int rr) {
	if (ll == rr) {
		c[cur] = w[ll] % MOD;
		return;
	}
	int mid = (ll + rr) >> 1;
	build(cur << 1, ll, mid);
	build((cur << 1) | 1, mid + 1, rr);
	c[cur] = ((LL)c[cur << 1] + c[(cur << 1) | 1]) % MOD;
}
int gsum(int cur, int ll, int rr) {
	if (l <= ll && rr <= r) return c[cur];
	LL ret = 0;
	int mid = (ll + rr) >> 1;
	if (laz[cur] && ll != rr) {
		laz[cur << 1] = ((LL)laz[cur << 1] + laz[cur]) % MOD;
		c[cur << 1] = ((LL)c[cur << 1] + (LL)(mid - ll + 1)*laz[cur]) % MOD;
		laz[(cur << 1) | 1] = ((LL)laz[(cur << 1) | 1] + laz[cur]) % MOD;
		c[(cur << 1) | 1] = ((LL)c[(cur << 1) | 1] + (LL)(rr - mid)*laz[cur]) % MOD;
		laz[cur] = 0;
	}
	if (l <= mid) ret = (ret + gsum(cur << 1, ll, mid)) % MOD;
	if (mid < r) ret = (ret + gsum((cur << 1) | 1, mid + 1, rr)) % MOD;
	return ret;
}
void update(int cur, int ll, int rr) {
	if (l <= ll && rr <= r) {
		laz[cur] = ((LL)laz[cur] + z) % MOD;
		c[cur] = (c[cur] + (LL)(rr - ll + 1)*(LL)z) % MOD;
		return;
	}
	c[cur] = ((LL)c[cur] + (LL)(min(rr, r) - max(ll, l) + 1)*(LL)z) % MOD;
	int mid = (ll + rr) >> 1;
	if (l <= mid) update(cur << 1, ll, mid);
	if (mid < r) update((cur << 1) | 1, mid + 1, rr);
}
void uprange(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		l = id[top[x]];
		r = id[x];
		update(1, 1, n);
		x = fa[top[x]];
	}
	if (dep[x] < dep[y]) swap(x, y);
	l = id[y];
	r = id[x];
	update(1, 1, n);
}
int grange(int x, int y) {
	int ret = 0;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		l = id[top[x]];
		r = id[x];
		ret = ((LL)ret + gsum(1, 1, n)) % MOD;
		x = fa[top[x]];
	}
	if (dep[x] < dep[y]) swap(x, y);
	l = id[y];
	r = id[x];
	ret = ((LL)ret + gsum(1, 1, n)) % MOD;
	return ret;
}
int main()
{
	int a, b, op;
	u *p;
	cin >> n >> m >> rot >> MOD;
	FOR(i, 1, n) scanf_s("%d", &tmp[i]);
	mem(head, 0);
	FOR(i, 1, n - 1) {
		scanf_s("%d%d", &a, &b);
		p = new u(a, head[b]);
		head[b] = p;
		p = new u(b, head[a]);
		head[a] = p;
	}
	mem(siz, 0);
	fa[rot] = 0;
	dfs1(rot, 1);
	cnt = 0;
	dfs2(rot, rot);
	build(1, 1, n);
	while (m--) {
		scanf_s("%d", &op);
		if (op == 1) {
			scanf_s("%d%d%d", &a, &b, &z);
			z %= MOD;
			uprange(a, b);
		}
		else if (op == 2) {
			scanf_s("%d%d", &a, &b);
			printf("%d\n", grange(a, b));
		}
		else if (op == 3) {
			scanf_s("%d%d", &a, &z);
			z %= MOD;
			l = id[a];
			r = id[a] + siz[a] - 1;
			update(1, 1, n);
		}
		else {
			scanf_s("%d", &a);
			l = id[a];
			r = id[a] + siz[a] - 1;
			printf("%d\n", gsum(1, 1, n));
		}
	}
	return 0;
}