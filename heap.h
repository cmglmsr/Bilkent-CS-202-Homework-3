#include "request.h"

/*
* Title: Heap.h
* Author: Mustafa Cem Gülümser
* ID: 22003430
* Section: 2
* Assignment: 3
* Description: Heap class header file. Heap is used to store requests.
*/

const int MAX_HEAP = 999;
typedef request HeapItemType;

class Heap {
public:
	Heap();	// default constructor
	// copy constructor and destructor are supplied by the compiler
	bool heapIsEmpty() const;
	void heapInsert(const HeapItemType& newItem);
	void heapDelete(HeapItemType& rootItem);
protected:
	void heapRebuild(int root); // Converts the semiheap rooted at index root into a heap
private:
	HeapItemType items[MAX_HEAP];	// array of heap items
	int size;            	// number of heap items
};
