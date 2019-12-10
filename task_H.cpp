#include <iostream>
#include <vector>

#define LL long long

class FT {
private:
	std::vector<std::vector<LL>> tree;
	int n, m;
	
	LL PrefixSum(int x, int y) {
		LL sum = 0;
		for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
			for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
				sum += tree[i][j];
			}
		}
		return sum;
	} 
	
public:
	FT(int a, int b): n(a), m(b) {
		tree = std::vector<std::vector<LL>>(n, std::vector<LL>(m, 0));
	}
	
	LL get_sum(int x1, int y1, int x2, int y2) {
		return PrefixSum(x2, y2) - PrefixSum(x2, y1 - 1) - 
			PrefixSum(x1 - 1, y2) + PrefixSum(x1 - 1, y1 - 1);
	}
	
	void Add(int x, int y, int val) {
		for (int i = x; i < n; i = i | (i + 1)) {
			for (int j = y; j < m; j = j | (j + 1)) {
				tree[i][j] += val;
			}
		}
	}
	
};

int main() {
	int x, y;
	std::cin >> x >> y;
	int n;
	std::cin >> n;
	FT ft(x, y);
	for (int i = 0; i < n; ++i) {
		int command;
		std::cin >> command;
		if (command == 1) {
			int x, y, val;
			std::cin >> x >> y >> val;
			ft.Add(x - 1, y - 1, val);
		}
		if (command == 2) {
			int x1, y1, x2, y2;
			std::cin >> x1 >> y1 >> x2 >> y2;
			std::cout << ft.get_sum(x1 - 1, y1 - 1, x2 - 1, y2 - 1) << std::endl;
		}
	}
}
