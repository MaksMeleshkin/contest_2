#include <iostream>
#include <vector>

unsigned int a, b; // даны во входных данных 
unsigned int cur = 0; // беззнаковое 32-битное число 
unsigned int nextRand() { 
  cur = cur * a + b; // вычисляется с переполнениями 
  return cur >> 8; // число от 0 до 224-1. 
}



int main() {
	int m, q;
	std::vector<unsigned int> array(1 << 24, 0); 
	unsigned int add, l ,r;
	std::cin >> m >> q;
	std::cin >> a >> b;
	for (int i = 0; i < m; ++i) {
		add = nextRand();
		l = nextRand();
		r = nextRand();
		if (l > r) std::swap(l, r);
		array[l] += add;
		array[r + 1] -= add;
	}
	int curr = 0;
	unsigned int part_sum = 0;
	std::vector<unsigned int> ps_arr(1 << 24, 0);
	for (int i = 0; i < 1 << 24; ++i) {
		curr += array[i];
		part_sum += curr;
		ps_arr[i] = part_sum;
	}
	unsigned int sum = 0;
	for (int i = 0; i < q; ++i) {
		l = nextRand(); 
		r = nextRand(); 
		if (l > r) std::swap(l, r);
		if (l > 0) {
			sum += ps_arr[r] - ps_arr[l - 1];
		} else {
			sum += ps_arr[r];
		}
	}
	std::cout << sum;
}
