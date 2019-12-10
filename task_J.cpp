#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <queue>

class Treap {
private:
	Node* root;
	int size = 0;
public:
	Treap() {
		root = nullptr;
	}
		
	void fast_build(std::vector<std::pair<int, int>
	
	void solve_problem() {
		std::queue<Node*> q;
		std::vector<vertex_info> data(size + 1, vertex_info());
		q.push(root);
		while(!q.empty()) {
			Node* v = q.front();
			q.pop();
			if (v->left) {
				q.push(v->left);
				data[v->number].left_son = v->left->number;
				data[v->left->number].parent = v->number;
			}
			if (v->right) {
				q.push(v->right);
				data[v->number].right_son = v->right->number;
				data[v->right->number].parent = v->number;
			}	
		}
		for (int i = 1; i <= size; ++i) {
				std::cout << data[i].parent << " " << data[i].left_son << " " << data[i].right_son << std::endl;
		}
	}
};


int main() {
	std::ios_base::sync_with_stdio(false);
	Treap treap;
	int n;
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		int x, y;
		std::cin >> x >> y;
		treap.insert(x, y, i);
	}
	std::cout << "YES" << std::endl;
	treap.solve_problem();
}
