#ifndef BufferPool_h
#define BufferPool_h

#include <list>
#include "GISRecord.hpp"

class BufferPool {
public:
	BufferPool(int maxSize_);
	void addRecord(GISRecord& record);
	GISRecord *search(string primaryKey);
	GISRecord *search(int offset);
	list<pair<GISRecord, int>>::iterator sortRecord(list<pair<GISRecord, int>>::iterator matchIter);
	string toStr();
private:
	size_t maxSize;
	list<pair<GISRecord, int>> pool;
};

#endif