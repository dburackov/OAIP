#pragma once
#include <initializer_list>

template<class T>
class list {
private:
	struct node {
		node* left;
		node* right;
		T data;
		node(T data, node* left = nullptr, node* right = nullptr) : data(data), left(left), right(right) {}
	};
	node* head = nullptr;
	node* last = nullptr;
	int length = 0;

public:
	list() {}

	list(const std::initializer_list<T>& list) {
		for (auto it : list) {
			push_back(it);
		}
	}

	list(list<T>& list) {
		for (auto it : list) {
			push_back(it);
		}
	}

	~list() {
		while (!empty()) {
			pop_back();
		}
	}

	void push_back(T value) {
		node* temp = new node(value);
		if (length == 0) {
			head = last = temp;
			head->right = last;
			last->left = head;
		} else {
			last->right = temp;
			temp->left = last;
			last = temp;
		}
		length++;
	}

	void pop_back() {
		if (length > 0) {
			if (length == 1) {
				delete last;
				head = last = nullptr;
			} else {
				last = last->left;
				delete last->right;
				last->right = nullptr;
			}
			length--;
		}
	}

	void push_font(T value) {
		node* temp = new node(value);
		if (length == 0) {
			head = last = temp;
			head->right = last;
			last->left = head;
		} else {
			head->left = temp;
			temp->right = head;
			head = temp;
		}
		length++;
	}

	void pop_front() {
		if (length > 0) {
			if (length == 1) {
				delete last;
				head = last = nullptr;
			} else {
				head = head->right;
				delete head->left;
				head->left = nullptr;
			}
			length--;
		}
	}

	int size() {
		return length;
	}

	bool empty() {
		return length == 0;
	}

	list<T>& operator=(list<T>& list) {
		length = 0;
		head = last = nullptr;
		for (auto it : list) {
			push_back(it);
		}
		return *this;
	}

	class iterator {
	private:
		node* ptr = nullptr;
	public:
		iterator() {}

		iterator(node* ptr) : ptr(ptr) {}

		iterator(const iterator& it) : ptr(it.ptr) {}

		~iterator() {}

		iterator& operator=(const iterator& it) {
			ptr = it.ptr;
			return *this;
		}

		bool operator==(const iterator& it) {
			return ptr == it.ptr;
		}

		bool operator!=(const iterator& it) {
			return ptr != it.ptr;
		}

		iterator& operator++() {
			ptr = ptr->right;
			return *this;
		}

		iterator& operator--() {
			ptr = ptr->left;
			return *this;
		}

		iterator operator++(int) {
			iterator temp = *this;
			++(*this);
			return temp;
		}

		iterator operator--(int) {
			iterator temp = *this;
			--(*this);
			return temp;
		}

		T operator*() {
			return ptr->data;
		}

		T* operator->() {
			ptr;
		}
	};

	iterator begin() {
		return iterator(head);
	}

	iterator end() {
		return iterator(last);
	}
};
