#include <iostream>
#include <vector>
#include <cstring>

std::vector<size_t> CalculatePrefixFunction(const std::string &str) {
	std::vector<size_t> prefix(str.size(), 0);
	for (size_t i = 1; i < str.size(); ++i) {
		int k = prefix[i - 1];
		while (str[i] != str[k] && k > 0) {
			k = prefix[k - 1];
		}
		if (str[i] == str[k]) {
			++k;
		}
		prefix[i] = k;
	}
	return prefix;
}

std::vector<size_t> KMP(const std::string &str, const std::string &substr) {
	std::string res_str = substr + '#' + str;
	std::vector<size_t> result;
	std::vector<size_t> prefix = CalculatePrefixFunction(res_str);
	for (size_t i = substr.size(); i < res_str.size(); ++i) {
		if (prefix[i] == substr.size()) {
			result.push_back(i - 2 * substr.size());
		}
	}
	return result;
}

int main() {
	std::string str;
	std::cin >> str;
	for (auto i: CalculatePrefixFunction(str)) {
		std::cout << i << " ";
	}
}
