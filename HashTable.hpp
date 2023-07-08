#pragma once
#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <vector>
#include <string>

using namespace std;

struct KeyValuePair {
	string key;
	int offset;
	KeyValuePair(string key, int offset) : key(key), offset(offset) {}
};

class HashTable {
	int tableSize, capacityFilled = 0;
	vector<KeyValuePair> entries;
	unsigned int hash(string key);

public:
	HashTable();
	void insert(string key, int offset);
	//int searchOffset(string key);
};

#endif