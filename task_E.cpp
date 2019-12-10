#include <iostream>
#include <vector>
#include <cmath>

class SegmentTree {
private:
	std::vector<long long> tree;
	std::vector<long long> count;
public:
	SegmentTree(const std::vector<int> &arr) {
		tree = std::vector<long long>(1 << ((long long)log2(arr.size() - 1) + 3), 0);
		count = std::vector<long long>(1 << ((long long)log2(arr.size() - 1) + 3), 0);	
		buildTree(0, 0, arr.size() - 1, arr);
	}
	
	void buildTree(int node, int tl, int tr, const std::vector<int> &arr) {
		if (tr == tl) {
			tree[node] = arr[tl];
			count[node] = 1;
		} else {
			int tm = (tr + tl) / 2;
			buildTree(node * 2 + 1, tl, tm, arr);
			buildTree(node * 2 + 2, tm + 1, tr, arr);
			tree[node] = std::max(tree[node * 2 + 1], tree[node * 2 + 2]);
			if (tree[node * 2 + 1] == tree[node * 2 + 2]) {
				count[node] = count[node * 2 + 1] + count[node * 2 + 2];
			} else {
				if (tree[node * 2 + 1] > tree[node * 2 + 2]) {
					count[node] = count[node * 2 + 1];
				} else {
					count[node] = count[node * 2 + 2];
				}
			}
		}
	}

	std::pair<int, int> query(int node, int tl, int tr, int l, int r) {
		if (r < tl || tr < l) {
			return {0, 0};
		}
		if (tl >= l && tr <= r) {
			return {tree[node], count[node]};
		}
		int tm = (tl + tr) / 2;
		std::pair<int, int> q1 = query(node * 2 + 1, tl, tm, l, r);
		std::pair<int, int> q2 = query(node * 2 + 2, tm + 1, tr, l, r);
		if (q1.first == q2.first) {
			return {q1.first, q1.second + q2.second};
		} else {
			if (q1.first > q2.first) {
				return q1;
			} else {
				return q2;
			}
		}
	} 	
};

int main() {
	int n;
	std::cin >> n;
	std::vector<int> arr;
	for (int i = 0; i < n; ++i) {
		int val;
		std::cin >> val;
		arr.push_back(val);
	} 
	SegmentTree st(arr);
	int k;
	std::cin >> k;
	for (int i = 0; i < k; ++i) {
		int l, r;
		std::cin >> l >> r;
		std::pair<int, int> ans = st.query(0, 0, arr.size() - 1, l - 1, r - 1);
		std::cout << ans.first << " " << ans.second << std::endl;
	}
}
