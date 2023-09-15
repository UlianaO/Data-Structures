#ifndef DEQUE_H
#define DEQUE_H

#include "DLinkedList.h"
//#include "DLinkedList.cpp"

#include <string>

using namespace std;


class LinkedDeque { // deque as doubly linked list
public:
	LinkedDeque(); // constructor
	int size() const; // number of items in the deque
	bool empty() const; // is the deque empty?
	const string& front() const; // first element
	const string& back() const; // last element

	void insertFront(const string& e); // insert new first element
	void insertBack(const string& e); // insert new last element
	void removeFront(); // remove first element
	void removeBack(); // remove last element

private:
	DLinkedList D; // doubly linked list of elements
	int n; // number of elements
};

#endif