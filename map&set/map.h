#pragma once

template<typename KeyType, typename ValueType>
struct node {
	std::pair<const KeyType, ValueType> data;
	node* left;
	node* right;
	node* parant;

	node(std::pair<KeyType, ValueType> value) : data(value) {
		left = right = parant = nullptr;
	}

	node(std::pair<KeyType, ValueType> value, node* parant) : data(value), parant(parant) {
		left = right = nullptr;
	}

	~node() {
		delete left;
		delete right;
	}

	KeyType getKey() {
		return data.first;
	}
};

template<typename KeyType, typename ValueType>
class map {
private:
	node<KeyType, ValueType>* root;
	node<KeyType, ValueType>* beginPointer;
	node<KeyType, ValueType>* endPointer;
	size_t mapSize;

public:
	map() {
		root = beginPointer = endPointer = nullptr;
		mapSize = 0;
	}

	~map() {
		clear();
	}

	void insert(std::pair<KeyType, ValueType> newNode) {
		node<KeyType, ValueType>* current = root;
		node<KeyType, ValueType>* previous = nullptr;
		while (current != nullptr) {
			previous = current;
			if (current->getKey() < newNode.first) {
				current = current->right;
			} else if (current->getKey() > newNode.first) {
				current = current->left;
			} else {
				return;
			}
		}
		if (previous == nullptr) {
			root = new node<KeyType, ValueType>(newNode);
			beginPointer = endPointer = root;
		} else if (previous->getKey() < newNode.first) {
			previous->right = new node<KeyType, ValueType>(newNode, previous);
			if (previous == endPointer) {
				endPointer = previous->right;
			}
		} else {
			previous->left = new node<KeyType, ValueType>(newNode, previous);
			if (previous == beginPointer) {
				beginPointer = previous->left;
			}
		}
		++mapSize;
	}

	void erase(KeyType key) {
		node<KeyType, ValueType>* current = root;
		node<KeyType, ValueType>* replacement = nullptr;
		node<KeyType, ValueType>* child = nullptr;
		while (current != nullptr && current->getKey() != key) {
			if (current->getKey() < key) {
				current = current->right;
			} else if (current->getKey() > key) {
				current = current->left;
			}
		}
		if (current == nullptr) {
			return;
		}
		if (current == beginPointer) {
			beginPointer = next(current);
		}
		if (current == endPointer) {
			endPointer = prev(current);
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
			} else if (current == current->parant->left) {
				current->parant->left = replacement;
			} else {
				current->parant->right = replacement;
			}
		}
		current->left = current->right = nullptr;
		delete current;
		current = nullptr;
		--mapSize;
	}
	
	size_t size() {
		return mapSize;
	}
	
	bool empty() {
		return mapSize == 0;
	}
	
	void clear() {
		delete root;
		root = beginPointer = endPointer = nullptr;
		mapSize = 0;
	}

	class iterator {
	private:
		map* metadata;
		node<KeyType, ValueType>* pointer;

	public:
		iterator() : metadata(nullptr), pointer(nullptr) {};
		iterator(map* metadata, node<KeyType, ValueType>* pointer) : metadata(metadata), pointer(pointer) {};
		
		bool operator ==(const iterator& it) {
			return pointer == it.pointer;
		}

		bool operator !=(const iterator& it) {
			return pointer != it.pointer;
		}

		std::pair<const KeyType, ValueType>& operator *() {
			return pointer->data;
		}

		iterator& operator =(const iterator& it) {
			pointer = it.pointer;
			metadata = it.metadata;
			return *this;
		}

		iterator& operator ++() {
			pointer = metadata->next(pointer);
			return *this;
		}

		iterator operator ++(int) {
			iterator temp = *this;
			pointer = metadata->next(pointer);
			return temp;
		}

		iterator& operator --() {
			pointer = metadata->prev(pointer);
			return *this;
		}

		iterator operator --(int) {
			iterator temp = *this;
			pointer = metadata->prev(pointer);
			return temp;
		}

		node<KeyType, ValueType>* getNode() {
			return pointer;
		}
	};

	iterator begin() {
		return iterator(this, beginPointer);
	}

	iterator end() {
		return iterator(this, endPointer);
	}

	iterator find(KeyType key) {
		node<KeyType, ValueType>* current = root;
		node<KeyType, ValueType>* result = endPointer;
		while (current != nullptr) {
			if (current->getKey() < key) {
				current = current->right;
			} else if (current->getKey() > key) {
				current = current->left;
			} else {
				result = current;
				break;
			}
		}
		return iterator(this, result);
	}

	ValueType& operator [](KeyType key) {
		insert(std::make_pair(key, ValueType()));
		node* current = root;
		while (current->getKey() != key) {
			if (current->getKey() < key) {
				current = current->right;
			} else {
				current = current->left;
			}
		}
		return current->data.second;
	}

	node<KeyType, ValueType>* next(node<KeyType, ValueType>* request) {
		node<KeyType, ValueType>* current = root;
		node<KeyType, ValueType>* result = beginPointer;
		while (current != nullptr) {
			if (current->getKey() > request->getKey()) {
				result = current;
				current = current->left;
			}
			else {
				current = current->right;
			}
		}
		return result;
	}

	node<KeyType, ValueType>* prev(node<KeyType, ValueType>* request) {
		node<KeyType, ValueType>* current = root;
		node<KeyType, ValueType>* result = endPointer;
		while (current != nullptr) {
			if (current->getKey() < request->getKey()) {
				result = current;
				current = current->right;
			}
			else {
				current = current->left;
			}
		}
		return result;
	}
};