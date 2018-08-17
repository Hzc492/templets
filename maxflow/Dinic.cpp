#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i <= _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i >= _##i; --i)
#define mem(f,x) memset(f,x,sizeof(f))
//========================================================================
const int MAX = 10005;
const int inf = 0x7fffffff;
struct u {
	u(int a, int b, u *c) :e(a), w(b), nxt(c) {};
	int e, w;
	u *nxt, *re;
};
u *head[MAX];
int dep[MAX];
deque<int> ls;
int n, m, s, t;
LL ans;
bool bfs() {
	int u;
	mem(dep, 0);
	ls.clear();
	ls.push_back(s);
	dep[s] = 1;
	while (!ls.empty()) {
		u = ls.front();
		ls.pop_front();
		for (auto p = head[u]; p; p = p->nxt) if (!dep[p->e] && p->w) {
			dep[p->e] = dep[u] + 1;
			ls.push_back(p->e);
		}
	}
	if (dep[t]) return true;
	else return false;
}
int dfs(int u, int flow) {
	if (u == t) return flow;
	int tmp;
	for (auto p = head[u]; p; p = p->nxt) if (p->w && dep[p->e] == dep[u] + 1) {
		tmp = dfs(p->e, min(flow, p->w));
		if (tmp) {
			p->w -= tmp;
			p->re->w += tmp;
			return tmp;
		}
	}
	return 0;
}
int main()
{
	int a, b, c;
	int tmp;
	u *p;
	ans = 0;
	cin >> n >> m >> s >> t;
	mem(head, 0);
	FOR(i, 1, m) {
		scanf_s("%d%d%d", &a, &b, &c);
		p = new u(b, c, head[a]);
		head[a] = p;
		p = new u(a, 0, head[b]);
		head[b] = p;
		head[a]->re = head[b];
		head[b]->re = head[a];
	}
	while (bfs()) {
		while (tmp = dfs(s, inf)) ans += tmp;
	}
	cout << ans << endl;
	return 0;
}