#pragma once

template<typename Key, typename T>
class BinaryTree {
private:
	struct node {
		std::pair<const Key, T> value;
		node* left;
		node* right;
		node* parant;

		node(std::pair<Key, T> value) : value(value) {
			left = right = parant = nullptr;
		}

		~node() {
			delete left;
			delete right;
		}

		Key key() {
			return value.first;
		}
	};

	node* root;
	T* nullT;
	Key* nullKey;
	size_t binaryTreeSize;

public:
	BinaryTree() {
		root = nullptr;
		nullT = new T;
		nullKey = new Key;
		binaryTreeSize = 0;
	}

	void insert(std::pair<Key, T> newValue) {
		node* current = root;
		node* previous = nullptr;
		while (current != nullptr) {
			previous = current;
			if (current->key() < newValue.first) {
				current = current->right;
			} else if (current->key() > newValue.first) {
				current = current->left;
			} else {
				return;
			}
		}
		if (previous == nullptr) {
			root = new node(newValue);
		} else if (previous->key() < newValue.first) {
			previous->right = new node(newValue);
			previous->right->parant = previous;
		} else {
			previous->left = new node(newValue);
			previous->left->parant = previous;
		}
		++binaryTreeSize;
	}

	T& find(Key requiredKey) {
		node* current = root;
		while (current != nullptr) {
			if (current->key() < requiredKey) {
				current = current->right;
			} else if (current->key() > requiredKey) {
				current = current->left;
			} else {
				return current->value.second;
			}
		}
		return *nullT;
	}

	T& operator [](Key requiredkey) {
		T& result = find(requiredkey);
		if (result == *nullT) {
			insert(std::make_pair(requiredkey, *nullT));
		}
		return result;
	}

	Key& lower_bound(Key requiredKey) {
		node* current = root;
		Key* result = nullKey;
		while (current != nullptr) {
			if (current->key() < requiredKey) {
				*result = current->value.first;
				current = current->right;
			} else {
				current = current->left;
			}
		}
		return *result;
	}

	Key& upper_bound(Key requiredKey) {
		node* current = root;
		Key* result = nullKey;
		while (current != nullptr) {
			if (current->key() > requiredKey) {
				*result = current->value.first;
				current = current->left;
			} else {
				current = current->right;
			}
		}
		return *result;
	}

	void erase(Key requiredKey) {
		node* current = root;
		node* replacement = nullptr;
		node* child = nullptr;
		while (current != nullptr && current->key() != requiredKey) {
			if (current->key() < requiredKey) {
				current = current->right;
			} else if (current->key() > requiredKey) {
				current = current->left;
			}
		}	
		if (current == nullptr) {
			return;
		}
		if (current->left == nullptr || current->right == nullptr) {
			replacement = current;
		} else {
			replacement = current->right;
			while (replacement->left != nullptr) {
				replacement = replacement->left;
			}
		}
		if (replacement->left != nullptr) {
			child = replacement->left;
		} else {
			child = replacement->right;
		}
		if (child != nullptr) {
			child->parant = replacement->parant;
		}
		if (replacement == root) {
			root = child;
		} else if (replacement == replacement->parant->left) {
			replacement->parant->left = child;
		} else {
			replacement->parant->right = child;
		}
		if (replacement != current) {
            replacement->parant = current->parant;
			replacement->left = current->left;
            current->left->parant = replacement;
			replacement->right = current->right;
            if (current->right != nullptr) {
                current->right->parant = replacement;
            }
			if (current == root) {
				root = replacement;
			} else if (current == current->parant->left){
				current->parant->left = replacement;	
			} else {
				current->parant->right = replacement;
			}
			delete current;
		}
        current->left = current->right = nullptr;
        delete current;
        current = nullptr;
		--binaryTreeSize;
	}

	size_t size() {
		return binaryTreeSize;
	}

	bool empty() {
		return binaryTreeSize == 0;
	}

	void clear() {
		delete root;
		root = nullptr;
		binaryTreeSize = 0;
	}
};