#include <iostream>
#include <vector>
#include <cmath>

template <class T>
class SegmentTree {
private:
	std::vector<T> tree;
	int N;
	T (*func)(const T &l, const T &r);
public:
	SegmentTree(const std::vector<T> &array, T (*function)(const T &l, const T &r)) {
		tree = std::vector<T>((1 << ((int)log2(array.size() - 1) + 1)) * 2, 0);
		N = array.size();
		func = function;
		treeBuild(array, 0, 0, N);
	}		

	void treeBuild(const std::vector<T> &array, int i, int tl, int tr) {
		if (tl == tr) { // impossible?
			return;
		}
		if (tr - tl == 1) {
			tree[i] = array[tl];
		} else {
			int mid = (tl + tr) / 2;
			treeBuild(array, 2 * i + 1, tl, mid);
			treeBuild(array, 2 * i + 2, mid, tr);
			tree[i] = func(tree[i * 2 + 1], tree[i * 2 + 2]);
		}
	}
	
	T query(int node, int l, int r, int tl, int tr) {
		if (l < tl && r <= tl || tl < l && tr <= l) {
			return 0;
		}
		if (tl >= l && tr <= r) {
			return tree[node];
		}	
		int tm = (tl + tr) / 2;
		return func(query(node * 2 + 1, l, r, tl, tm), query(node * 2 + 2, l, r, tm, tr));
	}
	
	void update(int i, int tl, int tr, int pos, T new_val) {
		if (tr - tl == 1) {
			tree[i] = new_val;	
			return;
		} 
		int mid = (tl + tr) / 2;
		if (pos < mid) {
			update(2 * i + 1, tl, mid, pos, new_val);
		} else {
			update(2 * i + 2, mid, tr, pos, new_val);
		}
		tree[i] = func(tree[2 * i + 1], tree[2 * i + 2]);
	}
	
	void add(int node, int tl, int tr, int l, int r, T val) {
		if (l < tl && r <= tl || tl < l && tr <= l) {
			return;
		}
		if (tl >= l && tr <= r) {
			tree[node] += val;
			return;
		}	
		int tm = (tl + tr) / 2;
		add(node * 2 + 1, tl, tm, l, r, val);
		add(node * 2 + 2, tm, tr, l, r, val);
		tree[node] = tree[node * 2 + 1] + tree[node * 2 + 2];
	} 

};

int gcd(const int &a, const int &b) {
	if (b == 0) {
		return a;
	} else {
		return gcd(b, a % b);
	}
}

int cust_sum(const int &a, const int &b) {
	return a + b;
}
	
int main() {
	int n;
	std::cin >> n;
	std::vector<int> arr;
	for (int i = 0; i < n; ++i) {
		int val;
		std::cin >> val;
		arr.push_back(val);
	}
	SegmentTree<int> st(arr, gcd);
	int k;
	std::cin >> k;
	for (int i = 0; i < k; ++i) {
		int a, b;
		std::cin >> a >> b;
		std::cout << st.query(0, a - 1, b, 0, arr.size()) << std::endl;
	} 
}

