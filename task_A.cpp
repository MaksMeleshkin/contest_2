#include <iostream>
#include <vector>
#include <cmath>

class sparseTable {
private:
	std::vector<std::vector<int>> table;
	std::vector<int> log_for_st;
public:
	sparseTable(const std::vector<int> &array): table((int)log2(array.size()) + 1, std::vector<int>()) {
		for (int i = 0; i < array.size(); ++i) {
			table[0].push_back(array[i]);
		}
		for (int k = 1; k < table.size(); ++k) {
			for (int i = 0; i < array.size() - (1 << k) + 1; ++i) {
				table[k].push_back(std::min(table[k - 1][i], table[k - 1][i + (1 << k - 1)]));
			}  
		}
		log_for_st = std::vector<int>(array.size() + 1); 
		log_for_st[1] = 0;
		for (int i = 2; i <= array.size(); ++i) {
			log_for_st[i] = log_for_st[i / 2] + 1;
		}
	}	
	
	int RMQ(int i, int j) {
		int k = log_for_st[j - i + 1];
		return std::min(table[k][i], table[k][j - (1 << k) + 1]);
	}
	/*
	void see() {
		for (auto i: table) {
			for (auto j: i) {
				std::cout << j << " ";
			}
			std::cout << std::endl;
		}
	}
	*/
};

int main() {
	std::ios_base::sync_with_stdio(false);
	int n, m, a_1, u_1, v_1;
	std::cin >> n >> m >> a_1;
	std::cin >> u_1 >> v_1;
	std::vector<int> array;
	std::vector<int> u;
	std::vector<int> v;
	array.push_back(a_1);
	u.push_back(u_1);
	v.push_back(v_1);
	for (int i = 1; i < n; ++i) {
		array.push_back((array[i - 1] * 23 + 21563) % 16714589);
	}
	sparseTable st(array);
	std::vector<int> ans;
	ans.push_back(st.RMQ(std::min(u_1 - 1, v_1 - 1), std::max(u_1 - 1, v_1 - 1)));
	for (int i = 1; i < m; ++i) {
		u.push_back((17 * u[i - 1] + 751 + ans[i - 1] + 2 * i) % n + 1);
		v.push_back((13 * v[i - 1] + 593 + ans[i - 1] + 5 * i) % n + 1);
		ans.push_back(st.RMQ(std::min(u[i] - 1, v[i] - 1), std::max(u[i] - 1, v[i] - 1)));
	}
	std::cout << u[m - 1] << " " << v[m - 1] << " " << ans[m - 1];
}
