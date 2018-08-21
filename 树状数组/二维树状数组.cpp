/*二维树状数组 单点更新+矩阵求和*/
/*编号为[1..n][1..n]*/
int n;
int v[1030][1030];
int lowbit(int x) {
	return (x&(-x));
}
void upgrade(int x, int y, int z) {
	for (int i = x; i <= n; i += lowbit(i)) {
		for (int j = y; j <= n; j += lowbit(j)) {
			v[i][j] += z;
		}
	}
}
int getsum(int x, int y) {
	//求矩阵(1,1)-(x,y)之和
	if (!x || !y) return 0;
	int ret = 0;
	for (int i = x; i; i -= lowbit(i)) {
		for (int j = y; j; j -= lowbit(j)) {
			ret += v[i][j];
		}
	}
	return ret;
}
int main()
{
	int a, b, c, d, e, f;
	cin >> n;
	mem(v, 0);
	while (1) {
		cin >> a;
		if (a == 1) {
			cin >> b >> c >> d;
			upgrade(b, c, d);//在(b,c)处加d
		}
		else if (a == 2) {
			cin >> b >> c >> d >> e;
			cout << getsum(d, e) - getsum(b - 1, e) - getsum(d, c - 1) + getsum(b - 1, c - 1) << endl;
			//求矩阵(b,c)-(d,e)之和
		}
		else break;
	}
	return 0;
}