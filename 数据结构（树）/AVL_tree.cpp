#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i <= _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i >= _##i; --i)
#define mem(f,x) memset(f,x,sizeof(f))
//========================================================================
struct u {
	u(int x)
		:n(x), st(0), lt(nullptr), rt(nullptr) {};
	int n;
	int st;
	u *lt, *rt;
};
class avl {
public:
	avl() :root(nullptr), taller(false), shorter(false) {};
	bool search() { search(root); }
	void insert() { insert(root); taller = false; }
	void remove() { remove(root); shorter = false; }
	void pre_order() { if (root) pre_order(root); cout << endl; }
	void middle_order() { if (root) middle_order(root); cout << endl; }
	void post_order() { if (root) post_order(root); cout << endl; }
	int height();
	avl& set_target(int num) { x = num; return *this; }
private:
	bool search(u *y);
	void insert(u* &y);
	void remove(u* &y);
	void pre_order(u *y);
	void middle_order(u *y);
	void post_order(u *y);
	void r_balance(u* &y);
	void l_balance(u* &y);
	void rr_rot(u* &y);
	void rl_rot(u* &y);
	void lr_rot(u* &y);
	void ll_rot(u* &y);
	bool taller, shorter;
	u *root;
	int x;
};
void avl::rl_rot(u* &y) {
	u *tmp1 = y->rt->lt;
	u *tmp2 = y->rt;
	y->rt->lt = y;
	y->rt = tmp1;
	y = tmp2;
}
void avl::rr_rot(u* &y) {
	u *tmp1 = y->lt->rt;
	u *tmp2 = y->lt;
	y->lt->rt = y;
	y->lt = tmp1;
	y = tmp2;
}void avl::lr_rot(u* &y) {
	u *tmp1 = y->lt->rt;
	u *tmp2 = y->lt;
	y->lt->rt = y;
	y->lt = tmp1;
	y = tmp2;
}
void avl::ll_rot(u* &y) {
	u *tmp1 = y->rt->lt;
	u *tmp2 = y->rt;
	y->rt->lt = y;
	y->rt = tmp1;
	y = tmp2;
}
void avl::r_balance(u* &y) {
	if (y->rt->st == 1) {
		rl_rot(y);
		y->st = 0;
		y->lt->st = 0;
	}
	else if (y->rt->st == 0) {
		rl_rot(y);
		y->st = -1;
		y->lt->st = 1;
	}
	else {
		rr_rot(y->rt);
		rl_rot(y);
		if (y->st == 0) {
			y->lt->st = 0; y->rt->st = 0;
		}
		else if (y->st = 1) {
			y->lt->st = -1;
			y->rt->st = 0;
		}
		else {
			y->lt->st = 0;
			y->rt->st = 1;
		}
		y->st = 0;
	}
}
void avl::l_balance(u* &y) {
	if (y->lt->st == -1) {
		lr_rot(y);
		y->st = 0;
		y->rt->st = 0;
	}
	else if (y->lt->st == 0) {
		lr_rot(y);
		y->st = -1;
		y->rt->st = 1;
	}
	else {
		ll_rot(y->lt);
		lr_rot(y);
		if (y->st == 0) {
			y->rt->st = 0; y->lt->st = 0;
		}
		else if (y->st = -1) {
			y->rt->st = -1;
			y->lt->st = 0;
		}
		else {
			y->rt->st = 0;
			y->lt->st = 1;
		}
		y->st = 0;
	}
}
void avl::insert(u* &y) {
	if (!y) {
		y = new u(x);
		taller = true;
		return;
	}
	if (x < y->n) {
		insert(y->lt);
		if (taller) {
			switch (y->st) {
			case -1:
				l_balance(y);
				taller = false;
				break;
			case 0:
				y->st = -1;
				break;
			case 1:
				y->st = 0;
				taller = false;
				break;
			}
		}
	}
	else {
		insert(y->rt);
		if (taller) {
			switch (y->st) {
			case -1:
				y->st = 0;
				taller = false;
				break;
			case 0:
				y->st = 1;
				break;
			case 1:
				r_balance(y);
				taller = false;
				break;
			}
		}
	}
}
void avl::remove(u* &y) {
	if (y->n == x) {
		u *tmp = y;
		if (!y->lt) {
			y = y->rt;
			delete tmp;
			shorter = true;
			return;
		}
		else if (!y->rt) {
			y = y->lt;
			delete tmp;
			shorter = true;
			return;
		}
		else {
			tmp = tmp->lt;
			while (tmp->rt) tmp = tmp->rt;
			x = tmp->n;
			y->n = x;
			remove(y->lt);
		}
	}
	else if (x < y->n) {
		remove(y->lt);
	}
	else {
		remove(y->rt);
	}
	if (shorter) {
		if (x <= y->n) {
			if (y->st == -1) {
				y->st = 0;
			}
			else if (y->st == 0) {
				y->st = 1;
				shorter = false;
			}
			else {
				if (y->rt->st == 0) shorter = false;
				r_balance(y);
			}
		}
		else {
			if (y->st == 1) {
				y->st = 0;
			}
			else if (y->st == 0) {
				y->st = -1;
				shorter = false;
			}
			else {
				if (y->lt->st == 0) shorter = false;
				l_balance(y);
			}
		}
	}
}
bool avl::search(u *y) {
	if (!y) return false;
	if (x == y->n) return true;
	if (x < y->n) return search(y->lt);
	else return search(y->rt);
}
void avl::pre_order(u *y) {
	cout << (char)y->n << " ";
	if (y->lt) pre_order(y->lt);
	if (y->rt) pre_order(y->rt);
}
void avl::middle_order(u *y) {
	if (y->lt) middle_order(y->lt);
	cout << (char)y->n << " ";
	if (y->rt) middle_order(y->rt);
}
void avl::post_order(u *y) {
	if (y->lt) post_order(y->lt);
	if (y->rt) post_order(y->rt);
	cout << (char)y->n << " ";
}
int avl::height() {
	u *p = root;
	int ret = 0;
	while (p) {
		ret++;
		if (p->st == 1) p = p->rt;
		else p = p->lt;
	}
	return ret;
}
avl tree;
int main()
{
	int order;
	char ch;
	while (cin >> order) {
		if (order==3) {
			tree.pre_order();
			tree.middle_order();
			tree.post_order();
		}
		else {
			cin >> ch;
			if (order == 1) tree.set_target(ch).insert();
			else tree.set_target(ch).remove();
		}
	}
	//cout << tree.height() << endl;
	return 0;
}