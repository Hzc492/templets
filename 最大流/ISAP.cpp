/*最大流 ISAP
 *re为反向边
 *基于分层思想的最大流算法。省去了Dinic每次增广后需要重新构建分层图的麻烦，而是在每次增广完成后自动更新每个点的标号（也就是所
在的层）
 *渐进时间复杂度和dinic相同，但是非二分图的情况下isap更具优势*/
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