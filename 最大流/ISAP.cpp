#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i <= _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i >= _##i; --i)
#define mem(f,x) memset(f,x,sizeof(f))
//========================================================================
const int inf = 0x7fffffff;
const int MAX = 10005;
struct u {
	u(int a, int b, u *c) :e(a), w(b), nxt(c) {};
	int e, w;
	u *nxt, *re;
};
u *head[MAX], *cur[MAX], *pre[MAX];
int d[MAX], gap[MAX];
deque<int> ls;
int n, m, s, t;
void ini() {
	int a, b, c;
	u *p;
	mem(head, 0);
	cin >> n >> m >> s >> t;
	FOR(i, 1, m) {
		scanf_s("%d%d%d", &a, &b, &c);
		p = new u(b, c, head[a]);
		head[a] = p;
		p = new u(a, 0, head[b]);
		head[b] = p;
		head[a]->re = head[b];
		head[b]->re = head[a];
	}
	FOR(i, 1, n) cur[i] = head[i];
}
void bfs() {
	mem(d, -1);
	mem(gap, 0);
	int u;
	ls.clear();
	ls.push_back(t);
	d[t] = 0;
	gap[0]++;
	while (!ls.empty()) {
		u = ls.front();
		ls.pop_front();
		for (auto p = head[u]; p; p = p->nxt) if (d[p->e] == -1) {
			d[p->e] = d[u] + 1;
			gap[d[p->e]]++;
			ls.push_back(p->e);
		}
	}
}
int augment() {
	int ret = inf;
	for (auto p = pre[t]; p; p = pre[p->re->e]) {
		ret = min(ret, p->w);
	}
	for (auto p = pre[t]; p; p = pre[p->re->e]) {
		p->w -= ret;
		p->re->w += ret;
	}
	return ret;
}
LL isap() {
	LL ret = 0;
	int u = s;
	int tmp;
	bool ok;
	pre[s] = 0;
	while (d[s] < n) {
		if (u == t) {
			ret += augment();
			u = s;
		}
		ok = false;
		for (auto p = cur[u]; p; p = p->nxt) if (p->w && d[u] == d[p->e] + 1) {
			ok = true;
			pre[p->e] = p;
			cur[u] = p;
			u = p->e;
			break;
		}
		if (!ok) {
			tmp = n - 1;
			for (auto p = head[u]; p; p = p->nxt) if (p->w) {
				tmp = min(tmp, d[p->e]);
			}
			gap[d[u]]--;
			if (!gap[d[u]]) break;
			d[u] = tmp + 1;
			gap[d[u]]++;
			cur[u] = head[u];
			if (u != s) {
				u = pre[u]->re->e;
			}
		}
	}
	return ret;
}
int main()
{
	ini();
	bfs();
	cout << isap() << endl;
	return 0;
}