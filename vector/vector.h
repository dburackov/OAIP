#pragma once
#include <initializer_list>

template <class T>
class vector {
private:
	int length;
	int capacity;
	T* data;
public:
	vector(int length = 0, T value = T()) : length(length) {
		capacity = 1;
		while (capacity < length) {
			capacity = capacity << 1;
		}
		data = new T[capacity];
		for (int i = 0; i < length; i++) {
			data[i] = value;
		}
	}

	vector(const std::initializer_list<T>& list)  {
		length = list.size();
		capacity = 1;
		while (capacity < length) {
			capacity = capacity << 1;
		}
		data = new T[capacity];
		auto it = list.begin();
		for (int i = 0; it != list.end(); i++, it++) {
			data[i] = *it;
		}
	}

	vector(const vector& v) : length(v.length) {
		capacity = v.capacity;
		data = new T[capacity];
		for (int i = 0; i < length; i++) {
			data[i] = v.data[i];
		}
	}

	~vector() {
		delete[] data;
	}

	void pop_back() {
		if (length > 0) {
			length--;
			if (capacity / 2 >= length) {
				capacity = capacity >> 1;
				T* temp = new T[capacity];
				for (int i = 0; i < length; i++) {
					temp[i] = data[i];
				}
				delete[] data;
				data = temp;
			}
		}
	}

	void push_back(T value) {
		length++;
		if (length > capacity) {
			capacity = capacity << 1;
			T* temp = new T[capacity];
			for (int i = 0; i < length - 1; i++) {
				temp[i] = data[i];
			}
			delete[] data;
			data = temp;
		}
		data[length - 1] = value;
	}

	void resize(int newLength) {
		while (newLength > length) {
			push_back(T());
		}
		while (newLength < length) {
			pop_back();
		}
	}

	void clear() {
		capacity = 1;
		length = 0;
		delete[] data;
		data = new T[capacity];
	}

	int size() {
		return length;
	}

	bool empty() {
		return length == 0;
	}

	T& operator[](int index) {
		return data[index];
	}

	vector<T>& operator=(const vector& v) {
		delete[] data;
		length = v.length;
		capacity = v.capacity;
		data = new T[capacity];
		for (int i = 0; i < length; i++) {
			data[i] = v.data[i];
		}
		return *this;
	}

	class iterator {
	private:
		T* ptr;
	public:
		iterator() : ptr(nullptr) {}

		iterator(T* ptr) : ptr(ptr) {} 

		iterator(const iterator& it) : ptr(it.ptr) {} 

		~iterator() {
			delete ptr;
		}

		iterator& operator=(const iterator& it) {
			ptr = it.ptr;
			return *this;
		}

		iterator& operator++() {
			ptr++;
			return *this;
		}

		iterator& operator--() {
			ptr--;
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

		iterator operator+(int val) {
			iterator temp = *this;
			temp.ptr += val;
			return temp;
		}

		friend iterator operator+(int val, iterator& it) {
			iterator temp = it;
			temp.ptr += val;
			return temp;
		}

		iterator operator+=(int val) {
			this->ptr += val;
			return *this;
		}

		iterator operator-(int val) {
			iterator temp = *this;
			temp.ptr -= val;
			return temp;
		}

		iterator operator-=(int val) {
			this->ptr -= val;
			return *this;
		}

		bool operator==(const iterator& it) {
			return ptr == it.ptr;
		}
		bool operator!=(const iterator& it) {
			return ptr != it.ptr;
		}
		T operator*() {
			return *ptr;
		}
		T* operator->() {
			return ptr;
		}
	};

	iterator begin() {
		return iterator(data);
	}
	iterator end() {
		return iterator(data + length);
	}
};
