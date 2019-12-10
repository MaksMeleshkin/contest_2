#include <iostream>
#include <string>
#include <cstdlib>

class Node {
private:
	Node* left;
	Node* right;
	int x, y, size;

	static void update_size(Node* root) {
		root->size = 1;
		if (root->left) {
			root->size += root->left->size;
		}
		if (root->right) {
			root->size += root->right->size;
		}
	}

public:
	Node(int val) {
		x = val;
		y = std::rand();
		size = 1;
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

	static bool exists(Node* root, int key) {
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

	static std::pair<Node*, Node*> split(Node* root, int val) {
		if (root == NULL) {
			return {NULL, NULL};
		}
		if (root->x < val) {
			std::pair<Node*, Node*> res = split(root->right, val);
			root->right = res.first;
			update_size(root);	
			return {root, res.second};
		} else {
			std::pair<Node*, Node*> res = split(root->left, val);
			root->left = res.second;
			update_size(root);
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
			update_size(root_1);	
			return root_1;
		} else {
			root_2->left = merge(root_1, root_2->left);
			update_size(root_2);	
			return root_2;
		}
	}

	static Node* insert(Node* root, int val) {
		if (exists(root, val)) {
			return root;
		}
		std::pair<Node*, Node*> res = split(root, val);
		Node* new_treap = new Node(val);
		return merge(res.first, merge(new_treap, res.second));
	}

	static Node* erase(Node* root, int val) {
		if (!exists(root, val)) {
			return root;
		}
		std::pair<Node*, Node*> res_1 = split(root, val);
		std::pair<Node*, Node*> res_2 = split(res_1.second, val + 1);
		delete res_2.first;
		return merge(res_1.first, res_2.second);
	}
	
 	static void print(Node* root) {
		if (root == NULL) {
			return;
		}
		print(root->left);	
		std::cout << root->x << " " << root->y << " " << root->size << std::endl;
		print(root->right);
	}

	static int get(Node* root, int num) {
		if (!root || num > root->size) {
			throw "none";
		}
		if (!root->left) {
			if (num == 1) {
				return root->x;
			} else {
				get(root->right, num - 1);
			}
		}
		if (num == root->left->size + 1) {
			return root->x;
		}
		if (num > root->left->size + 1) {
			return get(root->right, num - root->left->size - 1);
		} else {
			return get(root->left, num);
		}
	}

	static int next(Node* root, int val) {
		if (!root) {
			throw "none";
		}
		std::pair<Node*, Node*> res = split(root, val + 1);
		if (!res.second) {
			root = merge(res.first, res.second);
			throw "none";
		}
		Node* curr = res.second;
		while(curr->left) {
			curr = curr->left;
		}
		root = merge(res.first, res.second);
		return curr->x;
	}
	
	static int prev(Node* root, int val) {
		if (!root) {
			throw "none";
		}
		std::pair<Node*, Node*> res = split(root, val);
		if (!res.first) {
			root = merge(res.first, res.second);
			throw "none";
		}
		Node* curr = res.first;
		while(curr->right) {
			curr = curr->right;
		}
		root = merge(res.first, res.second);
		return curr->x;
	}
};


class Treap {
private:
	Node* root;
public:
	Treap() {
		root = nullptr;
	}
	
	void insert(int val) {
		root = Node::insert(root, val);
	}
	
	void erase(int val) {
		root = Node::erase(root, val);
	}
	
	bool exists(int val) {
		return Node::exists(root, val);
	}
		
	int next(int val) {
		return Node::next(root, val);
	}
	
	int prev(int val) {
		return Node::prev(root, val);
	}	
	
	int kth(int num) {
		return Node::get(root, num);
	}
};

int main() {
	std::string str;
	int val;
	Treap treap;
	std::getline(std::cin, str);
	while(!str.empty()) {
		std::string command = str.substr(0, str.find(' ', 0));
		val = atoi(str.substr(str.find(' ', 0) + 1, str.size() - 1).c_str());
		if (command == "insert") {
			treap.insert(val);
		}
		if (command == "delete") {
			treap.erase(val);
		}
		if (command == "exists") {
			if (treap.exists(val)) {
				std::cout << "true" << std::endl;
			} else {
				std::cout << "false" << std::endl;
			}
		}
		if (command == "next") {
			try {
				std::cout << treap.next(val) << std::endl;
			} catch (const char* error) {
				std::cout << error << std::endl;
			}
		} 
		if (command == "prev") {
			try {
				std::cout << treap.prev(val) << std::endl;
			} catch (const char* error) {
				std::cout << error << std::endl;
			}
		}
		if (command == "kth") {
			try {
				std::cout << treap.kth(val) << std::endl;
			} catch (const char* error) {
				std::cout << error << std::endl;
			}
		}
		std::getline(std::cin, str);
	}
}
