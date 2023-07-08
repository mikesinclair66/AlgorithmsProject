#ifndef BufferPool_h
#define BufferPool_h

#include <list>
#include <GISRecord.hpp>

class BufferPool {
public:
	BufferPool(int maxSize_);
	void addRecord(GISRecord& record);
	GISRecord *search(string primaryKey);
	GISRecord *search(int offset);
	list<pair<GISRecord, int>>::iterator sortRecord(list<pair<GISRecord, int>>::iterator matchIter);
	string toStr();
private:
	// max size of the buffer
	size_t maxSize;

	// store the record and how often it was used
	// we will keep it sorted so the first element is always
	// the most recently used.
	list<pair<GISRecord, int>> pool;
};

#endif