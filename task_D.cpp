#include <iostream>
#include <vector>
#include <cmath>

class SegmentTree {
private:
	std::vector<long long> tree;
	std::vector<long long> mod;
public:
	SegmentTree(const std::vector<int> &arr) {
		tree = std::vector<long long>(1 << ((long long)log2(arr.size() - 1) + 3), 0);
		mod = std::vector<long long>(1 << ((long long)log2(arr.size() - 1) + 3), 0);	
		buildTree(0, 0, arr.size() - 1, arr);
	}
	
	void buildTree(int node, int tl, int tr, const std::vector<int> &arr) {
		if (tr == tl) {
			tree[node] = arr[tl];
		} else {
			int tm = (tr + tl) / 2;
			buildTree(node * 2 + 1, tl, tm, arr);
			buildTree(node * 2 + 2, tm + 1, tr, arr);
			tree[node] = tree[node * 2 + 1] + tree[node * 2 + 2];
		}
	}

	void push(int node, int tl, int tr) {
		if (mod[node] != 0) {
			if (tl != tr) {
				mod[node * 2 + 1] += mod[node];
				mod[node * 2 + 2] += mod[node];
			}
			tree[node] += (tr - tl + 1) * mod[node];
			mod[node] = 0;
		}
	}

	void update(int node, int tl, int tr, int l, int r, int val) {
		push(node, tl, tr);
		if ((l < tl && r < tl) || (tl < l && tr < l)) {
			return;
		}
		if (tl >= l && tr <= r) {
			mod[node] += val;
			push(node, tl, tr);
			return;
		}
		int tm  = (tl + tr) / 2;
		update(node * 2 + 1, tl, tm, l, r, val);
		update(node * 2 + 2, tm + 1, tr, l, r, val);
		tree[node] = tree[node * 2 + 1] + tree[node * 2 + 2];
	}

	long long query(int node, int tl, int tr, int l, int r) {
		push(node, tl, tr);
		if (r < tl || tr < l) {
			return 0;
		}
		if (tl >= l && tr <= r) {
			return tree[node];
		}
		long long tm = (tl + tr) / 2;
		return query(node * 2 + 1, tl, tm, l, r) + query(node * 2 + 2, tm + 1, tr, l, r);
	} 
	
	long long get(int node, int tl, int tr, int pos) {
		push(node, tl, tr);
		if (tl == tr) {
			return tree[node];
		}	
		long long tm = (tl + tr) / 2;
		if (pos <= tm) {
			return get(node * 2 + 1, tl, tm, pos);
		} else {
			return get(node * 2 + 2, tm + 1, tr, pos);
		}
	}		
};

int main() {
	std::ios_base::sync_with_stdio(false);
	int n;	
	std::cin >> n;
	std::vector<int> arr;
	for (int i = 0; i < n; ++i) {
		long long val;
		std::cin >> val;
		arr.push_back(val);
	}
	SegmentTree st(arr);
	int m;
	std::cin >> m;
	for (int i = 0; i < m; ++i) {
		char command;
		std::cin >> command;
		if (command == 'g') {
			int num;
			std::cin >> num;
			std::cout << st.get(0, 0, arr.size() - 1, num - 1) << "\n";
		}
		if (command == 'a') {
			int l, r, add;
			std::cin >> l >> r >> add;
			st.update(0, 0, arr.size() - 1, l - 1, r - 1, add);
		}
	}
}
