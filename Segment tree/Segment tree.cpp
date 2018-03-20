#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i <= _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i >= _##i; --i)
#define mem(f,x) memset(f,x,sizeof(f))
//========================================================================
/*
*线段树递归版本
*拥有lazy标记的sum实际上已经加上了更新的数字，lazy是对于其儿子而言的
*/
const long MAX_N = 500005;
class Segment_Tree {
public:
	void initialize();//初始化的时候顺便吧n和数据读入了吧orz（有点怪
	void update(long x, long val) { update(x, val, 1, n, 1); }//(x)点增加
	void update(long l, long r, long val) { update(l, r, val, 1, n, 1); }//[l,r]区间增加
	long query(long l, long r) { return query(l, r, 1, n, 1); }//查询[l,r]
private:
	void build(long ll, long rr, long cur);
	void push_up(long cur);
	void push_down(long ll, long rr, long cur);
	long query(long l, long r, long ll, long rr, long cur);
	void update(long l, long r, long val, long ll, long rr, long cur);
	void update(long x, long val, long ll, long rr, long cur);
	long n;//数的个数
	long sum[MAX_N << 2];
	long lazy[MAX_N << 2];
	long num[MAX_N];//原数据
};
void Segment_Tree::initialize() {
	mem(lazy, 0);
	cin >> n;
	FOR(i, 1, n) cin >> num[i];
	build(1, n, 1);
	return;
}
void Segment_Tree::build(long ll, long rr, long cur) {
	if (ll == rr) {
		sum[cur] = num[ll];
		return;
	}
	long mid = (ll + rr) >> 1;
	build(ll, mid, (cur << 1));
	build(mid + 1, rr, (cur << 1 | 1));//迷之位运算
	push_up(cur);
	return;
}
void Segment_Tree::push_up(long cur) {
	sum[cur] = sum[cur << 1] + sum[cur << 1 | 1];
	return;
}
void Segment_Tree::update(long l, long r, long val, long ll, long rr, long cur) {
	//区间增加
	if (l <= ll && rr <= r) {
		sum[cur] += val * (rr - ll + 1);
		lazy[cur] += val;
		return;
	}
	long mid = (ll + rr) >> 1;
	push_down(ll, rr, cur);
	if (l <= mid) update(l, r, val, ll, mid, cur << 1);
	if (mid < r) update(l, r, val, mid + 1, rr, (cur << 1 | 1));
	push_up(cur);
	return;
}
void Segment_Tree::update(long x, long val, long ll, long rr, long cur) {
	//点增加
	sum[cur] += val;
	if (ll == rr) return;
	long mid = (ll + rr) >> 1;
	if (x <= mid) update(x, val, ll, mid, cur << 1);
	else update(x, val, mid + 1, rr, cur << 1 | 1);
	return;
}
void Segment_Tree::push_down(long ll, long rr, long cur) {
	if (ll == rr) return;//给点节点标记的lazy无意义
	lazy[cur << 1] += lazy[cur];
	lazy[cur << 1 | 1] += lazy[cur];
	long mid = (ll + rr) >> 1;
	sum[cur << 1] += lazy[cur] * (mid - ll + 1);
	sum[cur << 1 | 1] += lazy[cur] * (rr - mid);
	lazy[cur] = 0;
	return;
}
long Segment_Tree::query(long l, long r, long ll, long rr, long cur) {
	if (l <= ll && rr <= r) {
		return sum[cur];
	}
	long mid = (ll + rr) >> 1;
	if (lazy[cur] != 0) {
		push_down(ll, rr, cur);
	}
	long ans = 0;
	if (l <= mid) ans += query(l, r, ll, mid, cur << 1);
	if (mid < r) ans += query(l, r, mid + 1, rr, (cur << 1 | 1));
	return ans;
}
Segment_Tree u;
int main()
{
	
	return 0;
}