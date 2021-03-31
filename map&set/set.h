#pragma once

#include "map.h"

template<typename KeyType>
class set {
private:
	map<KeyType, char> data;

public:
	set() {
		
	}

	~set() {
		data.clear();
	}

	void insert(KeyType key) {
		data.insert(std::make_pair(key, char()));
	}

	void erase(KeyType key) {
		data.erase(key);
	}

	size_t size() {
		return data.size();
	}

	bool empty() {
		return data.empty();
	}

	void clear() {
		data.clear();
	}

	class iterator {
	private:
		map<KeyType, char>* metadata;
		node<KeyType, char>* pointer;

	public:
		iterator() : metadata(nullptr), pointer(0) {};
		iterator(map<KeyType, char>* metadata, node<KeyType, char>* pointer) : 
			metadata(metadata), pointer(pointer) {};

		bool operator ==(const iterator& it) {
			return pointer == it.pointer;
		}

		bool operator !=(const iterator& it) {
			return pointer != it.pointer;
		}

		KeyType operator *() {
			return pointer->data.first;
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

	};

	iterator begin() {
		return iterator(&data, data.begin().getNode());
	}

	iterator end() {
		return iterator(&data, data.end().getNode());
	}

	iterator find(KeyType request) {
		return iterator(&data, data.find(request).getNode());
	}
};