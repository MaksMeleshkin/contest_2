#include <iostream>
#include <string>
#include <cstdlib>

class Node {
private:
	Node* left;
	Node* right;
	long long x, y, size, sum;

	static void update(Node* root) {
		root->size = 1;
		root->sum = root->x;
		if (root->left) {
			root->size += root->left->size;
			root->sum += root->left->sum;
		}
		if (root->right) {
			root->size += root->right->size;
			root->sum += root->right->sum;
		}
	}

public:
	Node(long long val) {
		x = val;
		y = std::rand();
		size = 1;
		sum = val;
		left = NULL;
		right = NULL;
	}
	
	~Node() {
		if (right) {
			delete right;
		}
		if (left) {
			delete left;
		}
	}

	static bool exists(Node* root, long long key) {
		if (root == NULL) {
			return false;
		}
		if (root->x == key) {
			return true;
		}
		if (root->x > key) {
			return exists(root->left, key);
		} 
		return exists(root->right, key);
	}

	static std::pair<Node*, Node*> split(Node* root, long long val) {
		if (root == NULL) {
			return {NULL, NULL};
		}
		if (root->x < val) {
			std::pair<Node*, Node*> res = split(root->right, val);
			root->right = res.first;
			update(root);	
			return {root, res.second};
		} else {
			std::pair<Node*, Node*> res = split(root->left, val);
			root->left = res.second;
			update(root);
			return {res.first, root};
		}
	}

	static Node* merge(Node* root_1, Node* root_2) {
		if (root_1 == NULL) {
			return root_2;
		}
		if (root_2 == NULL) {
			return root_1;
		}
		if (root_1->y <= root_2->y) {
			root_1->right = merge(root_1->right, root_2);
			update(root_1);	
			return root_1;
		} else {
			root_2->left = merge(root_1, root_2->left);
			update(root_2);	
			return root_2;
		}
	}

	static Node* insert(Node* root, long long val) {
		if (exists(root, val)) {
			return root;
		}
		std::pair<Node*, Node*> res = split(root, val);
		Node* new_treap = new Node(val);
		return merge(res.first, merge(new_treap, res.second));
	}

	static long long get_sum(Node* root, int l, int r) {
		std::pair<Node*, Node*> res_1 = split(root, l);
		std::pair<Node*, Node*> res_2 = split(res_1.second, r + 1);
		long long sum;
		if (!res_2.first) {
			sum = 0;
		} else {
			sum = res_2.first->sum;
		}
		root = merge(res_1.first, merge(res_2.first, res_2.second));
		return sum;
	}
};


class Treap {
private:
	Node* root;
public:
	Treap() {
		root = nullptr;
	}
	
	void insert(long long val) {
		root = Node::insert(root, val);
	}
	
	long long get_sum(int l, int r) {
		return Node::get_sum(root, l ,r);
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	Treap treap;
	int n;
	std::cin >> n;
	char last_command = 0;
	long long last_ans = 0;
	for (int i = 0; i < n; ++i) {
		char command;
		std::cin >> command;
		if (command == '+') {
			long long val;
			std::cin >> val;
			if (last_command == '?') {
				treap.insert((val + last_ans) % 1000000000);
			} else {
				treap.insert(val);
			}
		}
		if (command == '?') {
			int l, r;
			std::cin >> l >> r;
			last_ans = treap.get_sum(l, r);
			std::cout << last_ans << std::endl;
		}
		last_command = command;
	}
}
