#include "HashTable.hpp"

HashTable::HashTable() {
	tableSize = 1024;
	for (int i = 0; i < 1024; i++)
		entries.push_back(KeyValuePair("", -1));
}

void HashTable::insert(string key, int offset) {
	unsigned long index = hash(key);

	if (entries[index].key == "") {
		entries[index].key = key;
		entries[index].offset = offset;
	}
	else {
		while (entries[index].key != "")
			index = ((index * index + index) / 2) % tableSize;
		entries[index].key = key;
	}

	if ((++capacityFilled / tableSize) >= 0.7f) {
		for (int i = tableSize; i < tableSize * 2; i++)
			entries.push_back(KeyValuePair("", -1));
		tableSize *= 2;
	}
}

/*
int HashTable::searchOffset(string key) {

}
*/

unsigned int HashTable::hash(string key) {
	unsigned int score = 0, x = 0;
	for (char c : key) {
		score = (score << 4) + c;
		if ((x = score & 0xF0000000) != 0)
			score ^= (x >> 24);
		score &= ~x;
	}
	return score % tableSize;
}