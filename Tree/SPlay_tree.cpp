#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i <= _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i >= _##i; --i)
#define mem(f,x) memset(f,x,sizeof(f))
//========================================================================
class splay {
public:
	void visit(int x);
private:
	struct u {
		u() :data(0), lt(nullptr), rt(nullptr) {};
		u(int x) :data(x), lt(nullptr), rt(nullptr) {};
		int data;
		u *lt, *rt;
	};
	void r_link(u* &cur, u* &rtp);
	void l_link(u* &cur, u* &ltp);
	void r_rot(u* &cur);
	void l_rot(u* &cur);
	u * root;
};
void splay::r_link(u* &cur, u* &rtp) {
	rtp->lt = cur;
	rtp = cur;
	cur = cur->lt;
}
void splay::l_link(u* &cur, u* &ltp) {
	ltp->rt = cur;
	ltp = cur;
	cur = cur->rt;
}
void splay::r_rot(u* &cur) {
	u *tmp1 = cur->lt->rt;
	u *tmp2 = cur->lt;
	cur->lt->rt = cur;
	cur->lt = tmp1;
	cur = tmp2;
}
void splay::l_rot(u* &cur) {
	u *tmp1 = cur->rt->lt;
	u *tmp2 = cur->rt;
	cur->rt->lt = cur;
	cur->rt = tmp1;
	cur = tmp2;
}
void splay::visit(int x) {
	u *tmp = new u;
	u *cur = root;
	u* ltp = tmp;
	u* rtp = tmp;
	while (cur && cur->data != x) {
		if (x < cur->data) {
			if (!cur->lt || cur->lt->data == x) r_link(cur, rtp);
			else if (x < cur->lt->data) {
				r_rot(cur);
				r_link(cur, rtp);
			}
			else {
				r_link(cur, rtp);
				l_link(cur, ltp);
			}
		}
		else {
			if (!cur->rt || cur->rt->data == x) l_link(cur, ltp);
			else if (x > cur->rt->data) {
				l_rot(cur);
				l_link(cur, ltp);
			}
			else {
				l_link(cur, ltp);
				r_link(cur, rtp);
			}
		}
	}
	if (!cur) cur = new u(x);
	rtp->lt = cur->rt;
	ltp->rt = cur->lt;
	cur->rt = tmp->lt;
	cur->lt = tmp->rt;
	root = cur;
	delete tmp;
}

splay tree;
int main()
{
	FOR(i, 0, 1000000) {
		tree.visit(i);
		tree.visit(100000000 - i);
	}
	return 0;
}