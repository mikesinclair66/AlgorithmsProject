#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "BufferPool.hpp"

BufferPool::BufferPool(int maxSize_) : maxSize(maxSize_) { }

void BufferPool::addRecord(GISRecord& record) {
	if (pool.size() < maxSize) {
		pool.push_back(pair<GISRecord, int>(record, 0));
		return;
	}

	list<pair<GISRecord, int>>::iterator leastUsedIter = pool.end();
	leastUsedIter--;

	leastUsedIter->first = record;
	leastUsedIter->second = 0;
}


GISRecord *BufferPool::search(string key) {
	list<pair<GISRecord, int>>::iterator matchIter = pool.end();

	for (auto it = pool.begin(); it != pool.end(); it++) {
		if (it->first.getPrimaryKey() == key) {
			it->second++;
			matchIter = it;
			break;
		}
	}

	GISRecord *match = nullptr;
	if (matchIter != pool.end()) {
		list<pair<GISRecord, int>>::iterator inserted = sortRecord(matchIter);
		match = &inserted->first; 
	}
	return match;
}

list<pair<GISRecord, int>>::iterator BufferPool::sortRecord(list<pair<GISRecord, int>>::iterator matchIter) {
	list<pair<GISRecord, int>>::iterator insertIter;
	for (auto it = pool.begin(); it != pool.end(); it++) {
		if (it->second < matchIter->second) {
			insertIter = it;
			break;
		}
	}

	auto inserted = pool.insert(insertIter, *matchIter); 
	pool.erase(matchIter); 
	return inserted;
}

GISRecord *BufferPool::search(int offset) {
	list<pair<GISRecord, int>>::iterator matchIter = pool.end();

	// find a matching record
	for (auto it = pool.begin(); it != pool.end(); it++) {
		if (it->first.getOffset() == offset) {
			it->second++;
			matchIter = it;
			break;
		}
	}
	
	GISRecord *match = nullptr;
	if (matchIter != pool.end()) {
		list<pair<GISRecord, int>>::iterator inserted = sortRecord(matchIter);
		match = &inserted->first; 
	return match;
}



string BufferPool::toStr() {
	string str = "MRU\n";
	for (auto it = pool.begin(); it != pool.end(); it++) {
		str += it->first.toStr() + "\n";
	}
	return str + "LRU";
}
