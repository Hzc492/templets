/*树状数组 单点更新+区间查询*/
/*编号为[1..n][1..n]*/
const int Max = 500000;
int c[Max + 5];
int n;
int lowbit(int x) {
	return (x&(-x));
}
void upgrade(int x, int y) {
	for (int i = x; i <= n; i += lowbit(i)) {
		c[i] += y;
	}
}
int getsum(int x) {
	int ans = 0;
	for (int i = x; i; i -= lowbit(i)) {
		ans += c[i];
	}
	return ans;
}
int main()
{
	int m;
	cin >> n >> m;
	int a, b, c;
	FOR(i, 1, n) {
		cin >> a;
		upgrade(i, a);
	}
	while (m--) {
		cin >> a >> b >> c;
		if (a == 1) {
			upgrade(b, c);
		}
		else {
			cout << getsum(c) - getsum(b - 1) << endl;
		}
	}
	return 0;
}