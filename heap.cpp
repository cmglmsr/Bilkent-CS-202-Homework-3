#include "heap.h"
#include <iostream>
using namespace std;

/*
* Title: Heap.cpp
* Author: Mustafa Cem Gülümser
* ID: 22003430
* Section: 2
* Assignment: 3
* Description: Heap class source code file
*/

Heap::Heap() : size(0) {}

bool Heap::heapIsEmpty() const {
	return (size == 0);
}

void Heap::heapInsert( const HeapItemType&newItem) {

	if (size >= MAX_HEAP)
		cout << ("HeapException: Heap full") << endl;

	// Place the new item at the end of the heap
	items[size] = newItem;

	// Trickle new item up to its proper position
	int place = size;
	int parent = (place - 1)/2;
	while ( (place > 0) && (items[place].getKey() > items[parent].getKey()) ) {
		HeapItemType temp = items[parent];
		items[parent] = items[place];
		items[place] = temp;

		place = parent;
		parent = (place - 1)/2;
	}
 	++size;
}

void Heap::heapDelete(HeapItemType&rootItem) {
	if (heapIsEmpty())
		cout << "HeapException: Heap empty" << endl;
	else {
		rootItem = items[0];
		items[0] = items[--size];
		heapRebuild(0);
	}
}

void Heap::heapRebuild(int root) {   
	int child = 2 * root + 1; 	// index of root's left child, if any
	if ( child < size ) {		
		// root is not a leaf so that it has a left child
		int rightChild = child + 1; 	// index of a right child, if any
		// If root has right child, find larger child
		if ( (rightChild < size) &&
		     (items[rightChild].getKey() >items[child].getKey()) )
			child = rightChild; 	// index of larger child

		// If root’s item is smaller than larger child, swap values
		if ( items[root].getKey() < items[child].getKey() ) {
			HeapItemType temp = items[root];
			items[root] = items[child];
			items[child] = temp;

			// transform the new subtree into a heap
			heapRebuild(child);
		}
    }
}
