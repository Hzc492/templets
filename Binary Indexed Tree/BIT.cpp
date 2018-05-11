#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i <= _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i >= _##i; --i)
#define mem(f,x) memset(f,x,sizeof(f))
//========================================================================
const long Max = 500000;
long c[Max + 5];
long n;
long lowbit(long x) {
	return (x&(-x));
}
void upgrade(long x, long y) {
	for (long i = x; i <= n; i += lowbit(i)) {
		c[i] += y;
	}
}
long getsum(long x) {
	long ans = 0;
	for (long i = x; i; i -= lowbit(i)) {
		ans += c[i];
	}
	return ans;
}
int main()
{
	long m;
	cin >> n >> m;
	long a, b, c;
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