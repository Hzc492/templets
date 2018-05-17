#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i <= _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i >= _##i; --i)
#define mem(f,x) memset(f,x,sizeof(f))
//========================================================================
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
	n++;
	mem(v, 0);
	while (1) {
		cin >> a;
		if (a == 1) {
			cin >> b >> c >> d;
			b++; c++;
			upgrade(b, c, d);
		}
		else if (a == 2) {
			cin >> b >> c >> d >> e;
			b++; c++; d++; e++;
			cout << getsum(d, e) - getsum(b - 1, e) - getsum(d, c - 1) + getsum(b - 1, c - 1) << endl;
		}
		else break;
	}
	return 0;
}