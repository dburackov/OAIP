#pragma once

#include <forward_list>

template<typename KeyType, typename ValueType>
class hash_table {
private:
	int size = 1;
	std::forward_list<std::pair<const KeyType, ValueType>>* data;
	const int MAX_BATCH_SIZE;
	
	int getHash(KeyType key) {
		return std::hash<KeyType>{}(key) % size;
	}

public:
	
	hash_table() : MAX_BATCH_SIZE(14) {
		data = new std::forward_list<std::pair<const KeyType, ValueType>>[size];
	}

	hash_table(int batchSize) : MAX_BATCH_SIZE(batchSize) {
		data = new std::forward_list<std::pair<const KeyType, ValueType>>[size];
	}

	~hash_table() {
		delete[] data;
	}

	void insert(std::pair<KeyType, ValueType> newPair) {
		int position = getHash(newPair.first);
		int batchSize = 0;
		for (auto batch : data[position]) {
			if (batch.first == newPair.first) {
				return;
			}
			++batchSize;
		}
		data[position].push_front(newPair);
		if (batchSize == MAX_BATCH_SIZE) {
			rehash(2 * size);
		}
	}

	void rehash(size_t newSize) {
		if (newSize >= size) {
			auto* temp = data;
			int tempSize = size;
			size = newSize;
			data = new std::forward_list<std::pair<const KeyType, ValueType>>[newSize];
			for (size_t i = 0; i < tempSize; ++i) {
				while (!temp[i].empty()) {
					insert(temp[i].front());
					temp[i].pop_front();
				}
			}
			delete[] temp;
		}
	}

	void erase(KeyType key) {
		int position = getHash(key);
		for (auto it = data[position].before_begin(); it != data[position].end() && std::next(it) != data[position].end(); ++it) {
			if (std::next(it)->first == key) {
				data[position].erase_after(it);
			}
		}
	}

	bool contains(KeyType key) {
		int position = getHash(key);
		bool result = false;
		for (auto batch : data[position]) {
			if (batch.first == key) {
				result = true;
				break;
			}
		}
		return result;
	}

	ValueType& operator[](KeyType key) {
		insert(std::make_pair(key, ValueType()));
		int position = getHash(key);
		for (auto& batch : data[position]) {
			if (batch.first == key) {
				return batch.second;
			}
		}
	}

	ValueType operator[](KeyType key) const {
		int position = getHash(key);
		for (auto batch : data[position]) {
			if (batch.first == key) {
				return batch.second;
			}
		}
		return ValueType();
	}

	hash_table& operator =(const hash_table& hashTable) {
		size = hashTable.size;
		delete[] data;
		data = new std::forward_list<std::pair<const KeyType, ValueType>>[size];
		for (int i = 0; i < size; ++i) {
			for (auto batch : data[i]) {
				insert(batch);
			}
		}
		return *this;
	}

	void clear() {
		size = 1;
		delete[] data;
		data = new std::forward_list<std::pair<const KeyType, ValueType>>[size];
	}
};
