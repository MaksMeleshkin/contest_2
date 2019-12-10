#include <iostream>
#include <vector>
#include <cstring>

std::vector<int> CalculatePrefixFunction(const std::string &str) {
	std::vector<int> prefix(str.size(), 0);
	for (int i = 1; i < str.size(); ++i) {
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

int main() {
	std::string str; 
	std::getline(std::cin, str);
	std::vector<int> prefix = CalculatePrefixFunction(str);
	for (int i: prefix) {
		std::cout << i << " ";
	}
}
