/*线段树advanced*/
/*
*线段树递归版本
*拥有lazy标记的sum实际上已经加上了更新的数字，lazy是对于其儿子而言的
*set同理
*肯定会有点慢，使用前可以注释掉一些不用的功能
*/
const long MAX_N = 500005;
class Segment_Tree {
public:
	void initialize();//初始化的时候顺便吧n和数据读入了吧orz（有点怪
	void update(long x, long val) { update(x, val, 1, n, 1); }//(x)点增加
	void update(long l, long r, long val) { update(l, r, val, 1, n, 1); }//[l,r]区间增加
	long query(long l, long r) { return query(l, r, 1, n, 1); }//查询[l,r]之和
	long query_max(long l, long r) { return query_max(l, r, 1, n, 1); }//查询区间max
	long query_min(long l, long r) { return query_min(l, r, 1, n, 1); }//查询区间min
	void set(long x, long val) { set(x, val, 1, n, 1); }//点覆盖
	void set(long l, long r, long val) { set(l, r, val, 1, n, 1); }//[l,r]区间覆盖
private:
	void build(long ll, long rr, long cur);
	void push_up(long cur);
	void push_down(long ll, long rr, long cur);
	long query(long l, long r, long ll, long rr, long cur);
	long query_max(long l, long r, long ll, long rr, long cur);
	long query_min(long l, long r, long ll, long rr, long cur);
	void update(long l, long r, long val, long ll, long rr, long cur);
	void update(long x, long val, long ll, long rr, long cur);
	void set(long x, long val, long  ll, long rr, long cur);
	void set(long l, long r, long val, long  ll, long rr, long cur);
	void push_set(long ll, long rr, long cur);
	long n;//数的个数
	long sum[MAX_N << 2];
	long lazy[MAX_N << 2];
	long maxn[MAX_N << 2];
	long minn[MAX_N << 2];
	long setn[MAX_N << 2];
	bool seted[MAX_N << 2];
	long num[MAX_N];//原数据（不过废了
};
void Segment_Tree::initialize() {
	mem(lazy, 0);
	mem(seted, false);
	cin >> n;
	FOR(i, 1, n) cin >> num[i];
	build(1, n, 1);
	return;
}
void Segment_Tree::build(long ll, long rr, long cur) {
	if (ll == rr) {
		sum[cur] = num[ll];
		maxn[cur] = num[ll];
		minn[cur] = num[ll];
		return;
	}
	long mid = (ll + rr) >> 1;
	build(ll, mid, (cur << 1));
	build(mid + 1, rr, (cur << 1 | 1));//迷之位运算
	push_up(cur);
	return;
}
void Segment_Tree::push_up(long cur) {
	maxn[cur] = max(maxn[cur << 1], maxn[cur << 1 | 1]);
	minn[cur] = min(minn[cur << 1], minn[cur << 1 | 1]);
	sum[cur] = sum[cur << 1] + sum[cur << 1 | 1];
	return;
}
void Segment_Tree::update(long l, long r, long val, long ll, long rr, long cur) {
	//区间增加
	if (l <= ll && rr <= r) {
		if (seted[cur]) push_set(ll, rr, cur);
		maxn[cur] += val;
		minn[cur] += val;
		sum[cur] += val * (rr - ll + 1);
		lazy[cur] += val;
		return;
	}
	long mid = (ll + rr) >> 1;
	if (seted[cur]) push_set(ll, rr, cur);
	else if (lazy[cur] != 0) push_down(ll, rr, cur);
	if (l <= mid) update(l, r, val, ll, mid, cur << 1);
	if (mid < r) update(l, r, val, mid + 1, rr, (cur << 1 | 1));
	push_up(cur);
	return;
}
void Segment_Tree::update(long x, long val, long ll, long rr, long cur) {
	//点增加
	sum[cur] += val;
	if (ll == rr) {
		long tmp = cur >> 1;
		while (tmp >= 1 && maxn[tmp] < maxn[cur]) {
			maxn[tmp] = maxn[cur];
			tmp = tmp >> 1;
		}
		tmp = cur >> 1;
		while (tmp >= 1 && minn[tmp] > minn[cur]) {
			minn[tmp] = minn[cur];
			tmp = tmp >> 1;
		}
		return;
	}
	long mid = (ll + rr) >> 1;
	if (seted[cur]) push_set(ll, rr, cur);
	else if (lazy[cur] != 0) push_down(ll, rr, cur);
	if (x <= mid) update(x, val, ll, mid, cur << 1);
	else update(x, val, mid + 1, rr, cur << 1 | 1);
	return;
}
void Segment_Tree::push_down(long ll, long rr, long cur) {
	if (ll == rr) return;//给点节点标记的lazy无意义
	long mid = (ll + rr) >> 1;
	if (seted[cur << 1]) push_set(ll, mid, cur << 1);
	if (seted[cur << 1 | 1]) push_set(mid + 1, rr, cur << 1 | 1);
	lazy[cur << 1] += lazy[cur];
	lazy[cur << 1 | 1] += lazy[cur];
	sum[cur << 1] += lazy[cur] * (mid - ll + 1);
	sum[cur << 1 | 1] += lazy[cur] * (rr - mid);
	maxn[cur << 1] += lazy[cur];
	maxn[cur << 1 | 1] += lazy[cur];
	minn[cur << 1] += lazy[cur];
	minn[cur << 1 | 1] += lazy[cur];
	lazy[cur] = 0;
	return;
}
long Segment_Tree::query(long l, long r, long ll, long rr, long cur) {
	if (l <= ll && rr <= r) {
		return sum[cur];
	}
	long mid = (ll + rr) >> 1;
	if (seted[cur]) push_set(ll, rr, cur);
	else if (lazy[cur] != 0) push_down(ll, rr, cur);
	long ans = 0;
	if (l <= mid) ans += query(l, r, ll, mid, cur << 1);
	if (mid < r) ans += query(l, r, mid + 1, rr, (cur << 1 | 1));
	return ans;
}
long Segment_Tree::query_max(long l, long r, long ll, long rr, long cur) {
	if (l <= ll && rr <= r) {
		return maxn[cur];
	}
	long mid = (ll + rr) >> 1;
	if (seted[cur]) push_set(ll, rr, cur);
	else if (lazy[cur] != 0) push_down(ll, rr, cur);
	long ans = INT32_MIN;
	if (l <= mid) ans = max(ans, query_max(l, r, ll, mid, cur << 1));
	if (mid < r) ans = max(ans, query_max(l, r, mid + 1, rr, (cur << 1 | 1)));
	return ans;
}
long Segment_Tree::query_min(long l, long r, long ll, long rr, long cur) {
	if (l <= ll && rr <= r) {
		return minn[cur];
	}
	long mid = (ll + rr) >> 1;
	if (seted[cur]) push_set(ll, rr, cur);
	else if (lazy[cur] != 0) push_down(ll, rr, cur);
	long ans = INT32_MAX;
	if (l <= mid) ans = min(ans, query_min(l, r, ll, mid, cur << 1));
	if (mid < r) ans = min(ans, query_min(l, r, mid + 1, rr, (cur << 1 | 1)));
	return ans;
}
void Segment_Tree::set(long x, long val, long  ll, long rr, long cur) {
	if (ll == rr) {
		sum[cur] = val;
		maxn[cur] = val;
		minn[cur] = val;
		return;
	}
	long mid = (ll + rr) >> 1;
	if (seted[cur]) push_set(ll, rr, cur);
	else if (lazy[cur] != 0) push_down(ll, rr, cur);
	if (x <= mid) set(x, val, ll, mid, cur << 1);
	else set(x, val, mid + 1, rr, cur << 1 | 1);
	push_up(cur);
	return;
}
void Segment_Tree::set(long l, long r, long val, long  ll, long rr, long cur) {
	if (l <= ll && rr <= r) {
		setn[cur] = val;
		seted[cur] = true;
		sum[cur] = val * (rr - ll + 1);
		lazy[cur] = 0;
		maxn[cur] = val;
		minn[cur] = val;
		return;
	}
	long mid = (ll + rr) >> 1;
	if (seted[cur]) push_set(ll, rr, cur);
	else if (lazy[cur] != 0) push_down(ll, rr, cur);
	if (l <= mid) set(l, r, val, ll, mid, cur << 1);
	if (mid < r) set(l, r, val, mid + 1, rr, (cur << 1 | 1));
	push_up(cur);
	return;
}
void Segment_Tree::push_set(long ll, long rr, long cur) {
	seted[cur] = false;
	if (ll == rr) return;
	long target = cur << 1;
	long mid = (ll + rr) >> 1;
	setn[target] = setn[cur];
	seted[target] = true;
	sum[target] = setn[target] * (mid - ll + 1);
	lazy[target] = 0;
	maxn[target] = setn[target];
	minn[target] = setn[target];
	target = target | 1;
	setn[target] = setn[cur];
	seted[target] = true;
	sum[target] = setn[target] * (rr - mid);
	lazy[target] = 0;
	maxn[target] = setn[target];
	minn[target] = setn[target];
}
Segment_Tree u;
int main()
{
	u.initialize();
	long t;
	cin >> t;
	long a, b, c, d;
	FOR(i, 1, t) {
		cin >> a;
		if (a == 1) {
			cin >> b >> c >> d;
			u.update(b, c, d);
		}
		else if (a == 2) {
			cin >> b >> c >> d;
			u.set(b, c, d);
		}
		else {
			cin >> b >> c;
			cout << u.query(b, c) << " "
				<< u.query_max(b, c) << " " << u.query_min(b, c) << endl;
		}
	}
	return 0;
}