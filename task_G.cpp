#include <iostream>
#include <vector>

#define LL long long

class fenvickTree {
private:
	std::vector<LL> tree;
	int size;
public:
	fenvickTree(const std::vector<int> &arr) {
		size = arr.size();
		tree = std::vector<LL>(size, 0);
		for (int i = 0; i < size; ++i) {
			Add(i, arr[i]);
		}
	}
	
	LL PrefixSum(int i) {
		LL sum = 0;
		while (i >= 0) {
			sum += tree[i];
			i = (i & (i + 1)) - 1;
		}
		return sum;
	}
	
	void set(int num, int val) {
		int current = PrefixSum(num) - PrefixSum(num - 1);
		Add(num, val - current);
	}
	
	void Add(int num, int val) {
		while (num < size) {
			tree[num] += val;
			num = num | (num + 1);
		}
	}
	
	LL get_sum(int l, int r) {
		return PrefixSum(r) - PrefixSum(l - 1);
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
	fenvickTree ft(arr);
	int m;
	std::cin >> m;
	for (int i = 0; i < m; ++i) {
		char command;
		std::cin >> command;
		if (command == 's') {
			int l, r;
			std::cin >> l >> r;
			std::cout << ft.get_sum(l - 1, r - 1) << " "; 
		}
		if (command == 'u') {
			int num, val;
			std::cin >> num >> val;
			ft.set(num - 1, val);
		}
	}
}
