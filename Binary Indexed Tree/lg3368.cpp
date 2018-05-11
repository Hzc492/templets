#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i <= _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i >= _##i; --i)
#define mem(f,x) memset(f,x,sizeof(f))
//========================================================================
const int Max = 500000;
int c[Max + 5];
int n;
int lowbit(int x) {
	return (x&(-x));
}
int getsum(int x) {
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
		ans += c[i];
	return ans;
}
void upgrade(int x, int y) {
	for (int i = x; i <= n; i += lowbit(i))
		c[i] += y;
}
int main()
{
	int m;
	cin >> n >> m;
	int a, b, c, d;
	scanf_s("%d", &b);
	upgrade(1, b);
	FOR(i, 2, n) {
		scanf_s("%d", &a);
		upgrade(i, a - b);
		b = a;
	}
	while (m--) {
		scanf_s("%d", &a);
		if (a == 1) {
			scanf_s("%d%d%d", &b, &c, &d);
			upgrade(b, d);
			if (c < n) upgrade(c + 1, -d);
		}
		else {
			scanf_s("%d", &b);
			cout << getsum(b) << endl;
		}
	}
	return 0;
}