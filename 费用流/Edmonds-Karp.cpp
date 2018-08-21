/*Edmonds-Karp 最小费用最大流 基于SPFA*/
const int inf = 0x7fffffff;
const int MAX = 5005;
struct u {
	u(int a, int b, int cc, u *d) :e(a), w(b), c(cc), nxt(d) {};
	int e, w, c;
	u *nxt, *re;
};
u *head[MAX];
bool v[MAX];
int dis[MAX];
int flo[MAX];
u *pre[MAX];
deque<int> ls;
int n, m, s, t;
void ini() {
	int a, b, c, d;
	u *p;
	mem(head, 0);
	pre[s] = 0;
	cin >> n >> m >> s >> t;
	FOR(i, 1, m) {
		scanf_s("%d%d%d%d", &a, &b, &c, &d);
		p = new u(b, c, d, head[a]);
		head[a] = p;
		p = new u(a, 0, -d, head[b]);
		head[b] = p;
		head[a]->re = head[b];
		head[b]->re = head[a];
	}
}
bool spfa() {
	int u;
	mem(v, 0);
	mem(dis, 0x7f);
	flo[s] = inf;
	flo[t] = 0;
	dis[s] = 0;
	ls.clear();
	ls.push_back(s);
	v[s] = 1;
	while (!ls.empty()) {
		u = ls.front();
		ls.pop_front();
		v[u] = 0;
		for (auto p = head[u]; p; p = p->nxt) if (p->w && dis[p->e] > dis[u] + p->c) {
			dis[p->e] = dis[u] + p->c;
			pre[p->e] = p;
			flo[p->e] = min(flo[u], p->w);
			if (!v[p->e]) {
				ls.push_back(p->e);
				v[p->e] = 1;
			}
		}
	}
	return (flo[t] != 0);
}
void augment() {
	for (auto p = pre[t]; p; p = pre[p->re->e]) {
		p->w -= flo[t];
		p->re->w += flo[t];
	}
}
int main()
{
	LL flow, cost;
	flow = cost = 0;
	ini();
	while (spfa()) {
		flow += flo[t];
		cost += flo[t] * dis[t];
		augment();
	}
	cout << flow << " " << cost << endl;
	return 0;
}